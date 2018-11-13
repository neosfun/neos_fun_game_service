#include "set_handler.h"

// ----------------------------------------------------------------------

SetHandler::SetHandler(NeosFunGame *pGame) : BaseHandler(pGame) {
    std::cout << "SetHandler created " << std::endl;
}

// ----------------------------------------------------------------------

std::string SetHandler::command() {
    return "set";
}

// ----------------------------------------------------------------------

std::string SetHandler::usage() {
    return "<x> <y> <color> <char>";
}

// ----------------------------------------------------------------------

std::string SetHandler::description() {
    return
        "x: [0-" + std::to_string(game()->width()) + "], "
        "y: [0-" + std::to_string(game()->height()) + "], "
        "color: [red|green|blue], "
        "char: [any]"
    ;
}

// ----------------------------------------------------------------------

std::string SetHandler::handle(std::vector<std::string> &vArgs) {
    if (vArgs.size() != 5) {
        return "Wrong command arguments";
    }

    int nX = std::stoi(vArgs[1]);
    if (nX < 0 || nX > game()->width()) {
        return "wrong x";
    }
    int nY = std::stoi(vArgs[2]);
    if (nY < 0 || nY > game()->width()) {
        return "wrong y";
    }

    std::string sColor = vArgs[3];
    if (sColor == "red") {
        sColor = "\033[41m";
    } else if (sColor == "green") {
        sColor = "\033[42m";
    } else if (sColor == "blue") {
        sColor = "\033[44m";
    } else {
        return "wrong color";
    }

    std::string sChar = vArgs[4];
    if (sChar.length() > 1) {
        return "wrong char (expected one simbol)";
    }
    game()->setValue(nX, nY, sColor, sChar);

    return game()->playingField();
}

// ----------------------------------------------------------------------