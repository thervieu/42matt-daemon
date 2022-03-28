#include "../incs/Daemon.hpp"

static void removeFile() {
    flock(Daemon::getInstance()->getLock(), LOCK_UN); // unlock lock file
    close(Daemon::getInstance()->getLock());
    std::remove("/var/lock/matt-daemon.lock");
}

static void signalHandler(int signum) {
    Daemon::getInstance()->getReporter().log("SIG", "Caught signal |" + std::string(strsignal(signum)) + "|.");
    Daemon::getInstance()->getReporter().log("INFO", "Quitting.");
    removeFile();
    exit(0);
}

Daemon::Daemon(void) {
    this->logger.log("INFO", "Started.");

    this->clients = std::vector<int>(CLIENT_NB, 0);
    this->lock_fd = open("/var/lock/matt-daemon.lock", O_CREAT, 0666);
    if (flock(this->lock_fd, LOCK_EX | LOCK_NB)) { // lock file
        close(this->lock_fd);
        this->logger.log("ERROR", "File locked.");
        this->logger.log("INFO", "Quitting.");
        exit(1);
    }

    /******         socket          ******/
    struct sockaddr_in servaddr;
    uint16_t port = 4242;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); // 127.0.0.1
	servaddr.sin_port = htons(port);

    this->logger.log("INFO", "Creating server.");
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        close(this->lock_fd);
        this->logger.log("ERROR", "Could not create socket.");
        this->logger.log("INFO", "Quitting.");
        removeFile();
        exit(1);
    }
    if (bind(sock_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        close(this->lock_fd);
        this->logger.log("ERROR", "Could not bind socket to server.");
        this->logger.log("INFO", "Quitting.");
        removeFile();
        exit(1);
    }
    if (listen(sock_fd, CLIENT_NB) < 0) {
        close(this->lock_fd);
        this->logger.log("ERROR", "Socket could not listen to port 4242.");
        this->logger.log("INFO", "Quitting.");
        removeFile();
        exit(1);
    }

    for (int i = 1; i < 32; i++)
        signal(i, signalHandler); // SIGTERM handler
}

Daemon::Daemon(const Daemon &rhs) {
    *this = rhs;
}

Daemon &Daemon::operator=(const Daemon &rhs) {
        this->nfds = rhs.nfds;
        this->sock_fd = rhs.sock_fd;
        this->lock_fd = rhs.lock_fd;
        this->readfds = rhs.readfds;
        this->logger = rhs.logger;
        return *this;
}

Daemon::~Daemon(void) {
    this->logger.log("INFO", "Quitting.");
    for (int i = 0; i < CLIENT_NB; i++) {
        if (this->clients[i] != 0)
            close(this->clients[i]);
    }
    close(this->lock_fd);
    close(this->sock_fd);
    if (instance)
        delete instance;
}

void    Daemon::acceptClient(void) {
    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);
    int client_fd;

    if ((client_fd = accept(sock_fd, (struct sockaddr *)&clientaddr, &len)) < 0) {
        this->logger.log("ERROR", "Connection refused.");
        return ;
    }
    int i;
    for (i = 0; i < CLIENT_NB; i++) {
        if (this->clients[i] == 0) {
            this->clients[i] = client_fd;
            break ;
        }
    }
    if (i != CLIENT_NB) {
        if (client_fd > this->nfds)
            this->nfds = client_fd;
    }
    else {
        this->logger.log("ERROR", "Maximum number of connections reached.");
        close(client_fd);
        return ;
    }
    std::ostringstream convert;
    convert << client_fd;
    this->logger.log("INFO", "Connection " + convert.str() + " accepted.");
    FD_SET(client_fd, &this->readfds);
}

void    Daemon::handleClients(void) {
    char buffer[4096];
    for (int i = 0; i < CLIENT_NB; i++) {
        if (this->clients[i] != 0 && FD_ISSET(this->clients[i], &this->readfds)) {
            int size_read;
            memset(buffer, 0, 4096);
            if ((size_read = recv(this->clients[i], buffer, 4095, 0)) <= 0) {
                close(this->clients[i]);
                std::ostringstream convert;
                convert << this->clients[i];
                this->logger.log("INFO", "Connection " + convert.str() + " lost.");
                this->clients[i] = 0;
                break ;
            }
            else {
                if (strcmp(buffer, "quit") == 0 || strcmp(buffer, "quit\n") == 0) {
                    this->logger.log("INFO", "Request quit.");
                    this->logger.log("INFO", "Quitting.");
                    close(this->lock_fd);
                    std::remove("/var/lock/matt-daemon.lock");
                    for (int j = 0; j < CLIENT_NB; j++)
                        if (this->clients[j] != 0)
                            close(this->clients[j]);
                    removeFile();
                    exit(0);
                }
                else {
                    buffer[strlen(buffer) - 1] = '\0';
                    std::ostringstream convert;
                    convert << this->clients[i];
                    this->logger.log("LOG", "client " + convert.str() + ": " + buffer);
                    break ;
                }
            }
        }
    }
}

void    Daemon::initServer(void) {
    FD_ZERO(&this->readfds);
    FD_SET(this->sock_fd, &this->readfds);
    for (int i = 0; i < CLIENT_NB; i++)
        if (this->clients[i] != 0)
            FD_SET(this->clients[i], &this->readfds);
}

void    Daemon::serverLoop(void) {
    // log
    this->logger.log("INFO", "Server created.");
    this->logger.log("INFO", "Entering Daemon mode.");
    pid_t pid = getpid();
    std::ostringstream convert;
    convert << pid;
    this->logger.log("INFO", std::string("Server started. PID: ") + convert.str() + std::string("."));

    // server
    this->nfds = this->sock_fd;
    FD_ZERO(&this->readfds);
    FD_SET(this->sock_fd, &this->readfds);
    while (4242) {
        initServer();
        if (select(this->nfds + 1, &this->readfds, NULL, NULL, NULL)) {
            if (FD_ISSET(this->sock_fd, &this->readfds))
                acceptClient();
            handleClients();
        }
        else { // select fails
            this->logger.log("ERROR", "Socket could not select.");
            break ;
        }
    }
}
