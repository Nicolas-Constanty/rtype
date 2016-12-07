//
// Created by victor on 06/12/16.
//

#include "Thread/StdMutex.hpp"
#include "ServerGame/CreateRoomGameServer/ClientGameRooms.hpp"

ClientGameRooms::ClientGameRooms(Network::Core::NativeSocketIOOperationDispatcher &dispatcher,
                                 std::string const &ip, size_t threadNbr)
        : Network::TCP::ATCPClient(dispatcher), protocolServerManager(*this), factory(), threadNbr(threadNbr), pool(), ip(0), lobbies()
{
    __mutex = new StdMutex();
    mutex = new StdMutex();
    if ((this->ip = Network::Socket::ASocket::getIPFromString(ip)) == 0) {
        std::cout << "FAILED" << std::endl;
    }
    size_t idx = 0;
    while (idx < threadNbr) {
        Lobby *lobby = new Lobby(*mutex, *this);
        pool.AddThread(std::bind(&Lobby::waitingRoom, std::ref(*lobby)));
        lobbies.emplace_back(lobby);
        ++idx;
    }
}

ClientGameRooms::~ClientGameRooms()
{
    std::cout << "\e[31mDestructor called\e[0m" << std::endl;
}

void ClientGameRooms::OnDataReceived(unsigned int len)
{
    std::cout << "Receiving " << buff << std::endl;
    while (protocolServerManager.handleProtocol(buff.buff(), buff.getLength())) {
        std::cout << "unknown cmd" << std::endl;
    }
}

void ClientGameRooms::onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &obj) {
    __mutex->lock();
    std::cout << obj << std::endl;
    buff += sizeof(obj);
    __mutex->unlock();
}

//TODO
// Ne pas utiliser la fonction SEND
// A Stocker dans une queue et à pop dans une fonction utilisé dans le main thread pour send
void ClientGameRooms::OnProcessBegin(void *data) {
    __mutex->lock();

    std::cout << "The Server Game is Launched" << std::endl;

    Lobby::LobbyInfo *lobbyInfo = (Lobby::LobbyInfo *)data;

    PackageServerHeader *launchPackageServer = factory.create<LAUNCHPackageServer>(lobbyInfo->GetMaxNbrClient(), lobbyInfo->GetMapID(),
                                                                            lobbyInfo->GetSecret(), this->ip, lobbyInfo->GetPort());

    _packageToSend.push(launchPackageServer);

    //TODO A ENLEVER
    this->SendData(*launchPackageServer);

    __mutex->unlock();
}

void ClientGameRooms::onGetLAUNCHPackage(LAUNCHPackageServer const &obj) {
    __mutex->lock();
    std::cout << obj << std::endl;
    unsigned short port = Network::Socket::OSSocket::GetAvailablePort();

    for (std::unique_ptr<Lobby> &lobby : lobbies) {
        mutex->lock();
        if (!lobby->IsLaunch()) {
            lobby->Launch(port, obj.roomPlayer, obj.secret, obj.mapID);
            mutex->unlock();
            break;
        }
        mutex->unlock();
    }

    buff += sizeof(obj);
    __mutex->unlock();
}

void ClientGameRooms::onGetSTATUSPackage(STATUSPackageServer const &obj) {
    __mutex->lock();
    std::cout << obj << std::endl;
    buff += sizeof(obj);
    __mutex->unlock();
}

void ClientGameRooms::OnDataSent(unsigned int len) {
    std::cout << "Number of bytes sent: " << len << std::endl;
}

void ClientGameRooms::OnStart() {
    __mutex->lock();
    std::cout << "connected" << std::endl;
    this->SendData(*(factory.create<AUTHENTICATEPackageServer>(0, 3)));
    __mutex->unlock();
}

//TODO
// Ne pas utiliser la fonction SEND
// A Stocker dans une queue et à pop dans une fonction utilisée dans le main thread pour send
void ClientGameRooms::OnProcessEnd(int status, void *data) {
    __mutex->lock();

    unsigned int *secret = (unsigned int *)data;

    (void)status;
    PackageServerHeader *statusPackageServer = factory.create<STATUSPackageServer>(*secret, ServerInformation::SERVEROVER);

    _packageToSend.push(statusPackageServer);

    //TODO A ENLEVER
    this->SendData(*statusPackageServer);

    std::cout << "The Server Game is over" << std::endl;
    __mutex->unlock();
}
