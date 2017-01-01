//
// Created by victor on 06/12/16.
//

#ifndef RTYPE_ROOMWAIT_HPP
#define RTYPE_ROOMWAIT_HPP

#include "Thread/IMutex.hpp"
#include "Process/IProcess.hpp"
#include "ServerGame/CreateRoomGameServer/ILobbyHandler.hpp"
#include "Thread/StdMutex.hpp"

class Lobby {
public:
    Lobby(IMutex &mutex, ILobbyHandler &lobbyHandler);
    ~Lobby();

public:
    void waitingRoom();

public:
    void Launch(unsigned short port, unsigned int maxNbrClient, unsigned int secret, unsigned short mapID);

private:
    void CreateServerGame();

public:
    class LobbyInfo {
    public:
        LobbyInfo(unsigned short port, unsigned int maxNbrClient, unsigned int secret, unsigned short mapID) {
            this->port = port;
            this->maxNbrClient = maxNbrClient;
            this->secret = secret;
            this->mapID = mapID;
        }

        unsigned short GetPort() const {
            return port;
        }

        unsigned int GetMaxNbrClient() const {
            return maxNbrClient;
        }

        unsigned int GetSecret() const {
            return secret;
        }

        unsigned short GetMapID() const {
            return mapID;
        }

    private:
        unsigned short port;
        unsigned int maxNbrClient;
        unsigned int secret;
        unsigned short mapID;

    };

public:
    bool        IsLaunch() const;
	bool		IsRunning() const;
	void		SetRunning(bool run = false);

private:
    IMutex      &mutex;
    bool        launch;
	bool		running;
	mutable StdMutex	runMutex;
    LobbyInfo   *lobbyInfo;
    ILobbyHandler   &lobbyHandler;
};

std::ostream &operator<<(std::ostream &ostream, Lobby::LobbyInfo const &lobbyInfo);

#endif //RTYPE_ROOMWAIT_HPP
