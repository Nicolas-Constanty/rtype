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
        manager->BroadCastPackage<GAMEOVERPackageGame>(&Network::UDP::AUDPConnection::SendReliable<GAMEOVERPackageGame>,
                                                       static_cast<unsigned char>(status));
    }
}

bool GameOver::IsOver() const {
    return over;
}
