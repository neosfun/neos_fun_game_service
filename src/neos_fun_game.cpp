#include "neos_fun_game.h"

// ----------------------------------------------------------------------

NeosFunGame::NeosFunGame() {

    m_nWidth = 50;
    m_nHeight = 20;
    m_sBGRed = "\033[41m";
    m_sBGBlue = "\033[44m";
    m_sBGReset = "\033[49m";

    for (int y = 0; y < m_nHeight; y++) {
        for (int x = 0; x < m_nWidth; x++) {
            if (x == 0 || x == m_nWidth-1 || y == 0 || y == m_nHeight-1) {
                m_vFields.push_back(m_sBGRed + "*" + m_sBGReset);
            } else {
                m_vFields.push_back(m_sBGBlue + " " + m_sBGReset);
            }
        }
    }
}

// ----------------------------------------------------------------------

int NeosFunGame::width() {
    return m_nWidth;
}

// ----------------------------------------------------------------------

int NeosFunGame::height() {
    return m_nHeight;
}

// ----------------------------------------------------------------------

void NeosFunGame::setValue(int nX, int nY, std::string sColor, std::string sCharacter) {
    int nPos = nY*m_nWidth + nX;
    m_vFields[nPos] = sColor + sCharacter + m_sBGReset;
}

// ----------------------------------------------------------------------

std::string NeosFunGame::playingField() {
    std::string sFields = "";

    for (unsigned int i = 0; i < m_vFields.size(); i++) {
        if (i % m_nWidth == 0) {
            sFields += "\r\n";
        }
        sFields += m_vFields[i];
    }
    return sFields;
}