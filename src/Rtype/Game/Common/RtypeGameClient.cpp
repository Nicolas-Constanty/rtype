//
// Created by gaspar_q on 11/28/16.
//

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include <Rtype/Game/Common/RtypeGameClient.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
#include <Rtype/Game/Server/RtypeGameServer.hpp>

const std::chrono::milliseconds    Rtype::Game::Common::RtypeGameClient::timeout = std::chrono::milliseconds(5000);

Rtype::Game::Common::RtypeGameClient::RtypeGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
        Network::UDP::AUDPClient::AUDPClient(dispatcher),
        manager(*this),
        recvstatus(),
        sendstatus(),
        reply(false),
        connected(false)
{

}

Rtype::Game::Common::RtypeGameClient::RtypeGameClient(const RtypeGameClient &ref) :
    Network::UDP::AUDPClient(ref),
    manager(*this),
    recvstatus(),
    sendstatus(),
    reply(false),
    connected(false)
{

}

Rtype::Game::Common::RtypeGameClient::~RtypeGameClient()
{

}

bool Rtype::Game::Common::RtypeGameClient::OnDataReceived(unsigned int)
{
    while (buff.getLength() >= sizeof(PackageGameHeader))
    {
        PackageGameHeader *head = buff.buff<PackageGameHeader>();

        std::cout << "Buff: " << buff << std::endl << "\e[34mReceived\e[0m: " << *head << " with reply: " << std::boolalpha << reply << std::endl;
        if (head->transactionID != 0)
        {
            //here you can check packet send by server which are lost
            sendstatus.Receiving(head->sequenceID);
            buff += head->length;
            std::cout << "\e[31mAcknoledge\e[0m" << std::endl;
        }
        else if (!recvstatus.IsSet(head->sequenceID))
        {
            reply = recvstatus.Receiving(head->sequenceID);
            std::cout << "\e[32mReceive status\e[0m: " << recvstatus << ", sliced at " << head->sequenceID << ": " << recvstatus.sliceAt(head->sequenceID) << " => " << recvstatus.sliceAt(head->sequenceID).getStatus() << std::endl;
            std::cout << "\e[33mIs set\e[0m: " << std::boolalpha << recvstatus.IsSet(head->sequenceID) << std::endl;
            if (reply)
            {
                head->transactionID = recvstatus.sliceAt(head->sequenceID).getStatus();
            }
            if (!manager.handleProtocol(buff.buff(), buff.getLength()))
                break;
            if (!connected)
            {
                std::cout << "Disconnected while reading" << std::endl;
                Disconnect();
                std::cout << "\e[31m ON A QUITTÉ LA FONCTION DATA RECEIVED \e[0m" << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << "buff: " << buff << std::endl;
            std::cout << "\e[31mReset\e[0m" << std::endl;
            buff += head->length;
//            return true;
        }
    }
    buff.consume();
    std::cout << "\e[31m ON A QUITTÉ LA FONCTION DATA RECEIVED \e[0m" << std::endl;
    return true;
}

bool Rtype::Game::Common::RtypeGameClient::OnDataSent(unsigned int len)
{
    std::cout << "Sent: " << len << std::endl;
    return true;
}