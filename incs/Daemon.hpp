#pragma once

#include "Tintin_reporter.hpp"
#include <string.h>
#include <sys/file.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sstream>

#define CLIENT_NB 3

class Daemon {
    private:
        int                 nfds;
        int                 sock_fd;
        int                 lock_fd;
        std::vector<int>    clients;
        fd_set              readfds;
        Tintin_reporter     logger;
        static Daemon*      instance;

    public:
        Daemon(void);
        Daemon(const Daemon &rhs);
        Daemon &operator=(const Daemon &rhs);
        ~Daemon(void);

        Tintin_reporter     getReporter()   { return logger; }
        int                 getLock()       { return lock_fd; }
        static Daemon       *getInstance(void) {
            instance = !instance ? new Daemon : instance;
            return (instance);
        }

        void                acceptClient(void);
        void                serverLoop(void);
        void                handleClients(void);

};
