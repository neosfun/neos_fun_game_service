#include "game_handler.h"

// ----------------------------------------------------------------------

GameHandler::GameHandler(NeosFunGame *pGame) : BaseHandler(pGame) {
    std::cout << "GameHandler created " << std::endl;
}

// ----------------------------------------------------------------------

std::string GameHandler::command() {
    return "game";
}

// ----------------------------------------------------------------------

std::string GameHandler::usage() {
    return "";
}

// ----------------------------------------------------------------------

std::string GameHandler::description() {
    return "print game fields";
}

// ----------------------------------------------------------------------

std::string GameHandler::handle(std::vector<std::string> &vArgs) {
    return game()->playingField();
}

// ----------------------------------------------------------------------