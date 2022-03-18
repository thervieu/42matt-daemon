#pragma once

// usual libs
#include <stdio>
#include <vector>
#include <map>

// clone libs
#include <linux/sched.h>    /* Definition of struct clone_args */
#include <sched.h>          /* Definition of CLONE_* constants */
#include <sys/syscall.h>    /* Definition of SYS_* constants */
#include <unistd.h>
#include <fstream.h>


// my classes
#include "Tintin_reporter.hpp"

std::string     formatString(std::string type, std::string str);
