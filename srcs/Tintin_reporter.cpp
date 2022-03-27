#include "../incs/Tintin_reporter.hpp"

Tintin_reporter::Tintin_reporter(void) {
    this->ofs.open("./var/log/matt_daemon/matt_daemon.log", std::ios::out | std::ios::app);
}

Tintin_reporter::Tintin_reporter(const Tintin_reporter &rhs) {
    *this = rhs;
}

Tintin_reporter &Tintin_reporter::operator=(const Tintin_reporter &rhs) {
    this->ofs.copyfmt(rhs.ofs);
    return *this;
}

Tintin_reporter::~Tintin_reporter(void) {
   this->ofs.close();
}

std::string     logFormat(std::string type, std::string str) {
    time_t t ;
    struct tm *pTime ;
    char MY_TIME[80];
    time(&t);
    pTime = localtime(&t);
     
    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "[%d/%m/%Y - %H:%M:%S] ", pTime);
    std::string timeFormat(MY_TIME);
    std::string typeFormat = std::string("[ " + type + " ] - Matt_daemon: " + (type == "LOG" ? "User input: " : ""));
    return (timeFormat + typeFormat + str);
}

void    Tintin_reporter::log(std::string type, std::string str) {
    std::string formatted = logFormat(type, str);
    if (this->ofs.is_open() == false) {
        this->ofs.open("./var/log/matt_daemon/matt_daemon.log", std::ios::out | std::ios::app);
    }
    if (this->ofs.is_open() == true) {
        this->ofs << formatted << std::endl;
    }
}

