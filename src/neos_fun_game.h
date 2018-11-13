#ifndef NEOS_FUN_GAME_H
#define NEOS_FUN_GAME_H

#include <string.h>
#include <iostream>
#include <vector>

class NeosFunGame {
    public:
        NeosFunGame();
        std::string playingField();
        int width();
        int height();
        void setValue(int nX, int nY, std::string sColor, std::string sCharacter);
    private:
        std::string m_sBGRed;
        std::string m_sBGBlue;
        std::string m_sBGReset;
        int m_nWidth;
        int m_nHeight;
        std::vector<std::string> m_vFields;
};

#endif // NEOS_FUN_GAME_H