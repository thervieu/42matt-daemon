#include "../incs/matt-daemon.hpp"

Tintin_reporter logger = Tintin_reporter();

void signal(int sig) {
    logger.log("Signal handler.");
    logger.log("Quitting.");
    int fd = fopen("matt-daemon.lock", "w");
    flock(fd, LOCK_UN);
    std::remove("matt-daemon.lock");
}

void daemon_loop(void *p) {
    std::vector<int> connected_fds;
    logger.fopen();

    // signals
    logger.log("Started.");
    logger.log("Creating server.");
    // socket stuff
    logger.log("Server created.");
    logger.log("Entering Daemon mode.");
    pid_t pid = getpid();
    logger.log("started. PID: " + std::string(static_cast<int>(pid)));
    while (4242) {
        select();
        for fds {
            if fd == server
                add_new_client_reader();
            else {

                while loop on read_this_fd {
                    read(buffer + strlen(buffer))
                }
                logger.log("got" + buffer);
            }
        }
    }
}

void create_and_lock_file(void) {
    int fd = fopen("matt-daemon.lock", "w");
    flock(fd, LOCK_EX);
}

void locked() {
    printf("Can't open :/var/lock/matt_daemon.lock\n");
}

void usage() {
    printf("Just launch the exec w/o args.\n./Matt-Daemon\n\n");
    printf("If already launched once before, you will receive an error.\n");
}

int main(int ac, char **av) {
    // check exec_user is root
    if (ac != 1) {
        usage();
        exit(1);
    }

    if (lock_file_exists()) {
        locked();
        FILE * fd = fopen("matt-daemon.log", "a");
        fputs(stringFormat("ERROR", "Error file locked."));
        exit(1);
    }
    else {
        create_and_lock_file();
        pid_t id = fork();
        if (id == 0) {
            daemon_loop();
            chdir("/");
        }
    }
    return (0);
}
