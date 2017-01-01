//
// Created by gouet_v on 12/18/16.
//

#ifndef RTYPE_GAMEOVER_HPP
#define RTYPE_GAMEOVER_HPP

#include "Common/DLLexport.hpp"

enum GAMEOVER : unsigned char {
    DEFEAT = 0,
    VICTORY = 1
};

class GameManager;

class PREF_EXPORT GameOver {
public:
    GameOver(GameManager *manager);
    virtual ~GameOver();

public:
    void    OverAction(GAMEOVER status);

public:
    bool    IsOver() const;

private:
    GameManager *manager;
    bool        over;
};

#endif //RTYPE_GAMEOVER_HPP
