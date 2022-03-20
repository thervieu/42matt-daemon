#include "../incs/Daemon.hpp"

static void signalGHandler(int signal) {
    this->logger.log("SIG", "Caught signal [ " + std::string(strsignal(signal)) + "].");
    logger.log("INFO", "Quitting.");
    flock(this->lockfd, LOCK_UN); // unlock lock file
    fclose(this->lockfd);
    std::remove("/var/lock/matt-daemon.lock");
    exit(0);
}

Daemon::Daemon(void) {
    this->logger.log("INFO", "Started.");
    this->logger.log("INFO", "Creating server.");

    /******         socket          ******/
    struct sockaddr_in servaddr;
    uint16_t port = 4242;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); // 127.0.0.1
	servaddr.sin_port = htons(port);

    this->lockfd = open("/var/lock/matt-daemon.lock", O_CREAT, 666);
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        close(this->lockfd);
    }
    if (bind(sock_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {

    }
    if (listen(sock_fd, 5) < 0) {

    }

}

Daemon::Daemon(const Daemon &rhs) {
    *this = rhs;
}

Daemon &Daemon::operator=(const Daemon &rhs) {

}

Daemon::~Daemon(void) {
}





void    Daemon::acceptClient(void) {

}

void    Daemon::handleInput(void) {

}

void    Daemon::serverLoop(void *p) {
    // signals



    logger.log("Server created.");
    logger.log("Entering Daemon mode.");
    pid_t pid = getpid();
    logger.log(logFormat("INFO", std::string("started. PID: ") + std::string(static_cast<char>(pid)) + std::string(".")));
    while (4242) {
        select(); // not sure if needed
        for fds {
            if (fd == server)
                add_new_client_reader();
            else {
                while loop on read_this_fd {
                    read(buffer + strlen(buffer))
                }
                logger.log(logFormat(std::string("LOG"), std::string(buffer)));
            }
        }
    }
}
