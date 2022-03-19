#include "../incs/Tintin_reporter.hpp"

Tintin_reporter::Tintin_reporter(void) {
    this->file_log_fd = fopen("/var/log/matt_daemon/matt-daemon.log", "a");
}

Tintin_reporter::Tintin_reporter(FILE * fd) {
    this->file_log_fd = fd;
}

Tintin_reporter::Tintin_reporter(const Tintin_reporter &rhs) {
    this->file_log_fd = rhs.file_log_fd;
}

Tintin_reporter::~Tintin_reporter(void) {
   fclose(this->file_log_fd);
}

void Tintin_reporter::newLog(void) {
    fclose("/var/log/matt_daemon/matt-daemon.log");
    this->file_log_fd = fopen("/var/log/matt_daemon/matt-daemon.log", "w");
}

FILE *Tintin_reporter::getFd(void) {
    return this->file_log_fd;
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

// [ DD / MM / YYYY - HH : MM : SS])
std::string     logFormat(std::string type, std::string str) {
    std::string str("");

    time_t t ;
    struct tm *time_struct ;
    char MY_TIME[50];
    time(&t);
    time_struct = localtime(&t);
     
    // using strftime to display time
    std::string timeFormat = std::string(strftime(MY_TIME, sizeof(MY_TIME), "[%d/%m/%Y - %H:%M:%S] ", tmp));
    std::string typeFormat = std::string("[ " + type + " ] - Matt_daemon: " + (type == "LOG" ? "User input: " : ""));
    printf("Formatted date, time and type: %s\n", MY_TIME);
    return (timeFormat + typeFormat + str));
}

void    Tintin_reporter::log(std::string type, std::string s) {
    fputs(formatStr, this->file_log_fd);
}

