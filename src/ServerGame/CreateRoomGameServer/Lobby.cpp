//
// Created by victor on 06/12/16.
//

#include <string>
#include <iostream>
#include <unistd.h>
#include "ServerGame/CreateRoomGameServer/Lobby.hpp"
#include "Process/UnixProcess.hpp"

Lobby::Lobby(IMutex &mutex, ILobbyHandler &lobbyHandler) : mutex(mutex), lobbyHandler(lobbyHandler) {
    lobbyInfo = NULL;
    launch = false;
}

Lobby::~Lobby() {

}

void Lobby::waitingRoom() {
    for (;;) {
        if (mutex.tryLock() > 0) {
            if (launch && lobbyInfo) {
                CreateServerGame();
            } else {
                mutex.unlock();
            }
        }
        usleep(5000);
    }
}

void Lobby::Launch(unsigned short port, unsigned int maxNbrClient, unsigned int secret, unsigned short mapID) {
    if (lobbyInfo == NULL) {
        delete lobbyInfo;
    }
    lobbyInfo = new LobbyInfo(port, maxNbrClient, secret, mapID);
    launch = true;
}

bool Lobby::IsLaunch() const {
    return launch;
}

void Lobby::CreateServerGame() {
    UnixProcess    process;

    ///TODO changer le sleep 10 par le binaire du server Game
    mutex.unlock();
    process.Launch("./GameServer -l " + std::to_string(lobbyInfo->GetMapID())
                   + " -m " + std::to_string(lobbyInfo->GetMaxNbrClient())
                   + " -p " + std::to_string(lobbyInfo->GetPort())
                   + " -s " + std::to_string(lobbyInfo->GetSecret()));
    if (!process.IsChild()) {
        lobbyHandler.OnProcessBegin(lobbyInfo);
    }

    int status = process.WaitSon();

    ///TODO checker le status
    mutex.lock();
    unsigned int secret = lobbyInfo->GetSecret();

    mutex.unlock();
    lobbyHandler.OnProcessEnd(status, &secret);
    mutex.lock();
    if (lobbyInfo)
        delete lobbyInfo;
    lobbyInfo = NULL;
    launch = false;
    mutex.unlock();
}

std::ostream &operator<<(std::ostream &ostream, Lobby::LobbyInfo const &lobbyInfo) {
    ostream << lobbyInfo.GetMaxNbrClient() << std::endl;
    ostream << lobbyInfo.GetPort() << std::endl;
    ostream << lobbyInfo.GetSecret() << std::endl;
    return ostream;
}