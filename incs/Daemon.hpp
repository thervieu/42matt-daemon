#pragma once

#include "Tintin_reporter.hpp"

class Daemon {
    private:
        int     sock_fd;
        int     max_fd;
        int     clients[10];
        fd_set  readfds;
        Tintin_reporter logger;
        static Daemon* instance;

    public:
        Daemon(void);
        Daemon(const Daemon &rhs);
        Daemon &operator=(const Daemon &rhs);
        ~Daemon(void);

        Daemon &getInstance(void) {
            return (!instance ? new Daemon() : instance);
        }

        void    acceptClient(void);
        void    serverLoop(void);
        void    handleInput(void);
        void    getReporter() { return logger; }

};
