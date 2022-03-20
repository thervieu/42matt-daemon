#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <stdlib.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <filesystem>

/* According to POSIX.1-2001 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

class Tintin_reporter {
    private:
        std::ofstream ofs;

    public:
        Tintin_reporter(void);
        Tintin_reporter(const Tintin_reporter &rhs);
        Tintin_reporter &operator=(const Tintin_reporter &rhs);
        ~Tintin_reporter(void);

        void    log(std::string type, std::string str);
};
