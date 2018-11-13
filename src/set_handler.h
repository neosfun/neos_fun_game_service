#ifndef SET_HADNLER_H
#define SET_HADNLER_H

#include "base_handler.h"

class SetHandler : public BaseHandler {
    public:
        SetHandler(NeosFunGame *pGame); // constructor
        virtual std::string command(); // name of command
        virtual std::string usage(); // usage
        virtual std::string description(); // description
        virtual std::string handle(std::vector<std::string> &vArgs); // execute (handle) this command
};

#endif // SET_HADNLER_H