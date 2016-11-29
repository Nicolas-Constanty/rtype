//
// Created by victor on 29/11/16.
//

#ifndef RTYPE_DEFAULTTCPCONNECTION_HPP
#define RTYPE_DEFAULTTCPCONNECTION_HPP

#include <Network/TCP/ATCPClient.hpp>

class DefaultTCPConnection : public Network::TCP::ATCPClient
{
public:
    DefaultTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Network::TCP::ATCPClient(dispatcher)
    {

    }

    DefaultTCPConnection(Network::Core::BasicConnection &ref) :
            Network::TCP::ATCPClient(ref.Dispatcher())
    {

    }

    virtual ~DefaultTCPConnection()
    {
        std::cout << "\e[31mDestructor called\e[0m" << std::endl;
    }

public:
    virtual void OnDataReceived(unsigned int len)
    {
        std::cout << "Receiving " << buff << std::endl;
//        if (buff.toString() == "change\n")
//        {
//            std::cout << "Changing client to Testswap client" << std::endl;
//            TestSwapClient  *newc = new TestSwapClient(*this);
//            std::cout << "TestSwap instantiated" << std::endl;
//            clients->Move(this, newc);
//            std::cout << "Client moved" << std::endl;
//            newc->SendData("on est bon\n");
//            newc->WantReceive();
//            std::cout << "Pending data sent" << std::endl;
//        }
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << "Number of bytes sent: " << len << std::endl;
    }
};

#endif //RTYPE_DEFAULTTCPCONNECTION_HPP
