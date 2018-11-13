#include "base_handler.h"

// ----------------------------------------------------------------------

BaseHandler::BaseHandler(NeosFunGame *pGame) {
    m_pGame = pGame;
    std::cout << "BaseHandler created " << std::endl;
}

// ----------------------------------------------------------------------

std::string BaseHandler::command() {
    return "base";
}

// ----------------------------------------------------------------------

std::string BaseHandler::usage() {
    return "<arg1> <arg2> <arg3> ... <argN>";
}

// ----------------------------------------------------------------------

std::string BaseHandler::description() {
    return "it's just base handler";
}

// ----------------------------------------------------------------------

std::string BaseHandler::handle(std::vector<std::string> &vArgs) {
    std::string sResult = "Do nothing, your arguments:\r\n";
    for (unsigned int i = 0; i < vArgs.size(); i++) {
        sResult += "\t * Arg" + std::to_string(i) + ": " + vArgs[i] + "\r\n";
    }
    return sResult;
}

// ----------------------------------------------------------------------

NeosFunGame *BaseHandler::game() {
    return m_pGame; 
}