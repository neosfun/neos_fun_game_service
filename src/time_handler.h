#ifndef TIME_HADNLER_H
#define TIME_HADNLER_H

#include "base_handler.h"

class TimeHandler : public BaseHandler {
    public:
        TimeHandler(NeosFunGame *pGame); // constructor
        virtual std::string command(); // name of command
        virtual std::string usage(); // usage
        virtual std::string description(); // description
        virtual std::string handle(std::vector<std::string> &vArgs); // execute (handle) this command
    private:
        std::string currentTime();
};

#endif // TIME_HADNLER_H