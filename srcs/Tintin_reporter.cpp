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

// [11/01/2016-14:34:58] [ INFO ] - Matt_daemon: Started.
// [11/01/2016-14:34:58] [ INFO ] - Matt_daemon: Creating server.
// [11/01/2016-14:34:58] [ INFO ] - Matt_daemon: Server created.
// [11/01/2016-14:34:58] [ INFO ] - Matt_daemon: Entering Daemon mode.
// [11/01/2016-14:34:58] [ INFO ] - Matt_daemon: started. PID: 6498.
// [11/01/2016-14:35:24] [ INFO ] - Matt_daemon: Signal handler.
// [11/01/2016-14:35:24] [ INFO ] - Matt_daemon: Quitting.

// [11/01/2016-15:00:25] [ INFO ] - Matt_daemon: Started.
// [11/01/2016-15:00:25] [ INFO ] - Matt_daemon: Creating server.
// [11/01/2016-15:00:25] [ INFO ] - Matt_daemon: Server created.
// [11/01/2016-15:00:25] [ INFO ] - Matt_daemon: Entering Daemon mode.
// [11/01/2016-15:00:25] [ INFO ] - Matt_daemon: started. PID: 8062.
// [11/01/2016-15:00:26] [ INFO ] - Matt_daemon: Started.
// [11/01/2016-15:00:26] [ ERROR ] - Matt_daemon: Error file locked.
// [11/01/2016-15:00:26] [ INFO ] - Matt_daemon: Quitting.

// [17/01/2016-16:36:07] [ INFO ] - Matt_daemon: Started.
// [17/01/2016-16:36:07] [ INFO ] - Matt_daemon: Creating server.
// [17/01/2016-16:36:07] [ INFO ] - Matt_daemon: Server created.
// [17/01/2016-16:36:07] [ INFO ] - Matt_daemon: Entering Daemon mode.
// [17/01/2016-16:36:07] [ INFO ] - Matt_daemon: started. PID: 3328.
// [17/01/2016-16:36:43] [ LOG ] - Matt_daemon: User input: Salut
// [17/01/2016-16:36:44] [ LOG ] - Matt_daemon: User input: xd
// [17/01/2016-16:36:47] [ INFO ] - Matt_daemon: Request quit.
// [17/01/2016-16:36:47] [ INFO ] - Matt_daemon: Quitting.

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
    printf("formatted : |%s|\n", formatted.c_str());
    if (this->ofs.is_open() == false) {
        printf("not opened\n\n");
        this->ofs.open("./var/log/matt_daemon/matt_daemon.log", std::ios::out | std::ios::app);
    }
    if (this->ofs.is_open() == true) {
        printf("write to ofs\n\n");
        this->ofs << formatted << std::endl;
    }
}

