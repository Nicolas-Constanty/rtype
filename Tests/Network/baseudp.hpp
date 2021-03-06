//
// Created by gaspar_q on 11/28/16.
//

#ifndef RTYPE_BASEUDP_HPP
#define RTYPE_BASEUDP_HPP

#include <iostream>
#include <Network/UDP/AUDPServer.hpp>
#include <Network/UDP/AUDPClient.hpp>

class BasicUDPClient : public Network::UDP::AUDPClient
{
public:
    BasicUDPClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            AUDPClient(dispatcher)
    {

    }

    BasicUDPClient(BasicUDPClient const &ref) :
            Network::UDP::AUDPClient(ref)
    {

    }

public:
    virtual void OnDataReceived(unsigned int len)
    {
        std::cout << "Data received: " << getBuffer() << " from " << sock << std::endl;
        SendData("je reçoit des choses\n");
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << "Sent " << len << " bytes" << std::endl;
    }
};

class BasicUDPServ : public Network::UDP::AUDPServer<BasicUDPClient>
{
public:
    BasicUDPServ(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Network::UDP::AUDPServer<BasicUDPClient>(dispatcher)
    {
        sock.Open();
        sock.Listen(4242);
    }

    ~BasicUDPServ()
    {
        sock.Close();
    }

public:
    virtual void OnDataReceived(unsigned int len)
    {
        std::cout << "Server reception" << std::endl;
        WantSend();
        newclient->SendData("hello\n");
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << "Data server sent" << std::endl;
    }
};

#endif //RTYPE_BASEUDP_HPP
