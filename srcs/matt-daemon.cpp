#include "../incs/matt-daemon.hpp"

Tintin_reporter logger = Tintin_reporter();

void signal(int sig) {
    logger.log("INFO", "Signal handler.");
    logger.log("INFO", "Quitting.");
    FILE * fd = fopen("/var/lock/matt-daemon.lock", "a");
    flock(fd, LOCK_UN); // unlock lock file
    fclose(fd);
    std::remove("/var/lock/matt-daemon.lock");
}

void daemon_loop(void *p) {
    std::vector<int> connected_fds;

    // signals

    /***  socket creation ***/
    logger.log("Creating server.");
    struct sockaddr_in servaddr;
    uint16_t port = 4242;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port);
    int sock_fd;
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        fatal();
    if (bind(sock_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        fatal();
    if (listen(sock_fd, 0) < 0)
        fatal();
    /***    socker done   ***/


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

void usage() {
    printf("Just launch the exec as root w/o args.\n./Matt-Daemon\n\n");
    printf("If already launched once before, you will receive an error. This is normal behaviour\n");
}

// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
// Daemon Class should be singleton just to make things nice
// just do it don't think
int main(int ac, char **av) {
    // check no args
    if (ac != 1) {
        usage();
        exit(1);
    }

    // check uid and euid is root
    int uid = getuid();
    int euid = geteuid();
    if (uid != 0 || euid != 0) {
        printf("Please come back as root, padawan.\n");
        exit(1);
    }

    chdir("/");

    logger.log("INFO", "Started.");

    FILE *file;
    file = fopen("/var/lock/matt-daemon.lock", "r"));
    if (file) { // if file already exists, antoher Matt-daemon is already running
        fclose(file);
        printf("Can't open :/var/lock/matt_daemon.lock\n");

        logger.log(logFormat("ERROR", "Error file locked."));
        logger.log(logFormat("INFO", "Quitting."));

        exit(1);
    }
    else { // if file doesn't exist, create and lock it
        FILE * fd = fopen("/var/lock/matt-daemon.lock", "w");
        logger.newLog();
        logger.log("INFO", "Started.");
        flock(fd, LOCK_EX); // lock the file
        fclose(fd);
        pid_t id = fork(); 
        if (id == 0) { // child is the daemon
            daemon_loop(); // server loop
        }
    }
    return (0);
}
