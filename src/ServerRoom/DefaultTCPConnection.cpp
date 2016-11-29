//
// Created by victor on 29/11/16.
//

#include "ServerRoom/DefaultTCPConnection.hpp"

DefaultTCPConnection::DefaultTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher)
        : Network::TCP::ATCPClient(dispatcher)
{

}

DefaultTCPConnection::DefaultTCPConnection(Network::Core::BasicConnection &ref) : Network::TCP::ATCPClient(ref.Dispatcher())
{

}

DefaultTCPConnection::~DefaultTCPConnection()
{
    std::cout << "\e[31mDestructor called\e[0m" << std::endl;
}

void DefaultTCPConnection::OnDataReceived(unsigned int len)
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

void DefaultTCPConnection::OnDataSent(unsigned int len)
{
    std::cout << "Number of bytes sent: " << len << std::endl;
}
