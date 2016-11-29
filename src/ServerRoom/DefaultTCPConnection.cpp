//
// Created by victor on 29/11/16.
//

#include "ServerRoom/DefaultTCPConnection.hpp"
#include "Protocol/Room/ProtocolPrintRoomPackage.hpp"
#include "Protocol/Server/ProtocolPrintServerPackage.hpp"

DefaultTCPConnection::DefaultTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher)
        : Network::TCP::ATCPClient(dispatcher), protocolRoomManager(*this), protocolServerManager(*this)
{
    std::cout << "CALLED DefaultTCPCOnnection constructor" << std::endl;
}

DefaultTCPConnection::DefaultTCPConnection(Network::Core::BasicConnection &ref)
        : Network::TCP::ATCPClient(ref.Dispatcher()), protocolRoomManager(*this), protocolServerManager(*this)
{
    std::cout << "CALLED DefaultTCPCOnnection constructor copy" << std::endl;
}

DefaultTCPConnection::~DefaultTCPConnection()
{
    std::cout << "\e[31mDestructor called\e[0m" << std::endl;
}

void DefaultTCPConnection::OnDataReceived(unsigned int)
{
    std::cout << "Receiving " << buff << std::endl;
    if ((!protocolServerManager.handleProtocol(buff.buff(), buff.getLength()))) {
        if ((!protocolRoomManager.handleProtocol(buff.buff(), buff.getLength()))) {
            std::cout << "unknown command" << std::endl;
        }
    }
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

void DefaultTCPConnection::onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &authenticatePackageRoom) {
    std::cout << authenticatePackageRoom << std::endl;
}

void DefaultTCPConnection::onGetFAILUREPackage(FAILUREPackageRoom const &failurePackageRoom) {
    std::cout << failurePackageRoom << std::endl;
}

void DefaultTCPConnection::onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &authenticatePackageServer) {
    std::cout << authenticatePackageServer << std::endl;
}

void DefaultTCPConnection::OnStart() {
//    this->SendData("salut !");
}
