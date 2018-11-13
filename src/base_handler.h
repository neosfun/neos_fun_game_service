#ifndef BASE_HADNLER_H
#define BASE_HADNLER_H

#include <string.h>
#include <iostream>
#include <vector>
#include "neos_fun_game.h"

class BaseHandler {
    public:
        BaseHandler(NeosFunGame *pGame); // constructor
        virtual std::string command(); // name of command
        virtual std::string usage(); // usage
        virtual std::string description(); // description
        virtual std::string handle(std::vector<std::string> &vArgs); // execute (handle) this command
        NeosFunGame *game();
    private:
        NeosFunGame *m_pGame;
};

#endif // BASE_HADNLER_H