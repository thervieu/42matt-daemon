#pragma once

#include <stdio>
#include <string>
#include <vector>
#include <map>

#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fstream.h>

class Tintin_reporter {
    private:
        std::ofstream ofs;

    public:
        Tintin_reporter(void);
        Tintin_reporter(const Tintin_reporter &rhs);
        Tintin_reporter &operator=(const Tintin_reporter &rhs);
        ~Tintin_reporter(void);

        void    log(std::string);
};
