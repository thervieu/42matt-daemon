#pragma once

#include <stdio.h>
#include <string>

class Tintin_reporter {
    private:
        FILE *file_log_fd;

    public:
        Tintin_reporter(void);
        Tintin_reporter(FILE * fd);
        Tintin_reporter(const Tintin_reporter &rhs);
        ~Tintin_reporter(void);

        void newLog(void);
        FILE *getFd(void);

        void    log(std::string);
};
