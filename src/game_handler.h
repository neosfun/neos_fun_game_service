#ifndef GAME_HADNLER_H
#define GAME_HADNLER_H

#include "base_handler.h"

class GameHandler : public BaseHandler {
    public:
        GameHandler(NeosFunGame *pGame); // constructor
        virtual std::string command(); // name of command
        virtual std::string usage(); // usage
        virtual std::string description(); // description
        virtual std::string handle(std::vector<std::string> &vArgs); // execute (handle) this command
};

#endif // GAME_HADNLER_H