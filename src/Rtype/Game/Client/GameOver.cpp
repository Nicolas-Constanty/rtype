//
// Created by gouet_v on 12/18/16.
//

#include "Rtype/Game/Client/GameOver.hpp"
#include "Rtype/Game/Client/GameManager.hpp"

GameOver::GameOver(GameManager *manager) : manager(manager), over(false) {

}

GameOver::~GameOver() {

}

void GameOver::OverAction(GAMEOVER status) {
//
    over = true;
    if (manager->isServerSide()) {
        std::cout << "OVER lol" << std::endl;
        manager->BroadCastPackage<GAMEOVERPackageGame>(&Network::UDP::AUDPConnection::SendReliable<GAMEOVERPackageGame>,
                                                       static_cast<unsigned char>(status));
    } else {
        std::cout << "c'est la fin ! salut !" << std::endl;
    }
}

bool GameOver::IsOver() const {
    return over;
}
