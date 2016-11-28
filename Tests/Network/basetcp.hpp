//
// Created by gaspar_q on 11/28/16.
//

#ifndef RTYPE_BASETCP_HPP
#define RTYPE_BASETCP_HPP

#include <iostream>
#include <Network/TCP/ATCPServer.hpp>
#include <Network/TCP/ATCPClient.hpp>

class TestSwapClient : public Network::TCP::ATCPClient
{
public:
    TestSwapClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Network::TCP::ATCPClient(dispatcher)
    {

    }

    TestSwapClient(Network::TCP::ATCPClient const &ref) :
            Network::TCP::ATCPClient(ref)
    {

    }

    virtual ~TestSwapClient()
    {

    }

public:
    virtual void OnDataReceived(unsigned int len)
    {
        std::cout << "Réception nouveau client: " << buff << std::endl;
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << len << " bytes sent" << std::endl;
    }
};

class BasicClient : public Network::TCP::ATCPClient
{
public:
    BasicClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Network::TCP::ATCPClient(dispatcher)
    {

    }

    BasicClient(Network::Core::BasicConnection &ref) :
            Network::TCP::ATCPClient(ref.Dispatcher())
    {

    }

    virtual ~BasicClient()
    {
        std::cout << "\e[31mDestructor called\e[0m" << std::endl;
    }

public:
    virtual void OnDataReceived(unsigned int len)
    {
        std::cout << "Receiving " << buff << std::endl;
        if (buff.toString() == "change\n")
        {
            std::cout << "Changing client to Testswap client" << std::endl;
            TestSwapClient  *newc = new TestSwapClient(*this);
            std::cout << "TestSwap instantiated" << std::endl;
            clients->Move(this, newc);
            std::cout << "Client moved" << std::endl;
            newc->SendData("on est bon\n");
            newc->WantReceive();
            std::cout << "Pending data sent" << std::endl;
        }
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << "Number of bytes sent: " << len << std::endl;
    }
};

class BasicTCPServ : public Network::TCP::ATCPServer<BasicClient>
{
public:
    BasicTCPServ(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Network::TCP::ATCPServer<BasicClient>(dispatcher)
    {
        Start(4242);
    }

    virtual ~BasicTCPServ()
    {
        Stop();
    }

public:
    virtual void OnDataReceived(unsigned int)
    {
        std::cout << "New client accepted" << std::endl;
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << "Number of bytes sent: " << len << std::endl;
    }
};

#endif //RTYPE_BASETCP_HPP
