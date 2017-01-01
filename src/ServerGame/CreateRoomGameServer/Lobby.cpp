//
// Created by victor on 06/12/16.
//

#ifdef _WIN32

#else
#include <unistd.h>
#endif

#include <string>
#include <iostream>
#include <Process/Process.hpp>
#include "ServerGame/CreateRoomGameServer/Lobby.hpp"

Lobby::Lobby(IMutex &mutex, ILobbyHandler &lobbyHandler) : mutex(mutex), lobbyHandler(lobbyHandler) {
    lobbyInfo = NULL;
    launch = false;
	running = false;
}

Lobby::~Lobby() {

}

void Lobby::waitingRoom() {
	SetRunning(true);
    for (;IsRunning();) {
        if (mutex.tryLock() > 0) {
            if (launch && lobbyInfo) {
                CreateServerGame();
            } else {
                mutex.unlock();
            }
        }
#ifdef _WIN32
		Sleep(5000);
#else
		usleep(5000);
#endif // _WIN32
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

bool		Lobby::IsRunning() const
{
	bool toret;

	runMutex.lock();
	toret = running;
	runMutex.unlock();
	return toret;
}

void		Lobby::SetRunning(bool run)
{
	runMutex.lock();
	running = run;
	runMutex.unlock();
}

void Lobby::CreateServerGame() {
    OSProcess    process;

    ///TODO changer le sleep 10 par le binaire du server Game
    mutex.unlock();
	std::string binary;
	
#ifdef _WIN32
	binary = "./GameServer.exe -l scene" + std::to_string(lobbyInfo->GetMapID()) + "Server"
		+ " -m " + std::to_string(lobbyInfo->GetMaxNbrClient())
		+ " -p " + std::to_string(lobbyInfo->GetPort())
		+ " -s " + std::to_string(lobbyInfo->GetSecret());
#else
	binary = "./GameServer -l scene" + std::to_string(lobbyInfo->GetMapID()) + "Server"
                         + " -m " + std::to_string(lobbyInfo->GetMaxNbrClient())
                         + " -p " + std::to_string(lobbyInfo->GetPort())
                         + " -s " + std::to_string(lobbyInfo->GetSecret());
#endif
    process.Launch(binary);
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