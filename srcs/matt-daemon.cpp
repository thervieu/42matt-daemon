#include "../incs/Daemon.hpp"

void usage() {
    printf("Just launch the exec as root w/o args.\n./Matt-Daemon\n\n");
    printf("If already launched once before, you will receive an error. This is normal behaviour\n");
}

Daemon *Daemon::instance = 0;

// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
// Daemon Class should be singleton just to make things nice
// just do it don't think
int main(int ac, char **av) {
    (void)av;
    // check no args
    if (ac != 1) {
        usage();
        exit(2);
    }

    // check uid and euid is root
    int uid = getuid();
    int euid = geteuid();
    if (uid != 0 || euid != 0) {
        printf("Please come back as root, young padawan.\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) exit(1);
    if (pid > 0) exit(0);
    if (chdir("/") < 0) exit(1);

    Daemon::getInstance()->serverLoop();
    return (0);
}
