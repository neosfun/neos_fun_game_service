#include "time_handler.h"

#include <sys/stat.h>
#include <sys/time.h>
#include <stdio.h>
#include <math.h>

// ----------------------------------------------------------------------

TimeHandler::TimeHandler(NeosFunGame *pGame) : BaseHandler(pGame) {
    std::cout << "TimeHandler created " << std::endl;
}

// ----------------------------------------------------------------------

std::string TimeHandler::command() {
    return "time";
}

// ----------------------------------------------------------------------

std::string TimeHandler::usage() {
    return "";
}

// ----------------------------------------------------------------------

std::string TimeHandler::description() {
    return "printed time";
}

// ----------------------------------------------------------------------

std::string TimeHandler::handle(std::vector<std::string> &vArgs) {
    return this->currentTime();
}

// ----------------------------------------------------------------------

std::string TimeHandler::currentTime(){
    // milleseconds
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
    if (millisec>=1000) { // Allow for rounding up to nearest second
        millisec -=1000;
        tv.tv_sec++;
    }

    // datetime
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d %X.", &tstruct);
    return std::string(buf) + std::to_string(millisec);
}