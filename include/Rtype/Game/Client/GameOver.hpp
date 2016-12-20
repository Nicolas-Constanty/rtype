//
// Created by gouet_v on 12/18/16.
//

#ifndef RTYPE_GAMEOVER_HPP
#define RTYPE_GAMEOVER_HPP

enum GAMEOVER : unsigned char {
    DEFEAT = 0,
    VICTORY = 1
};

class GameManager;

class GameOver {
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
