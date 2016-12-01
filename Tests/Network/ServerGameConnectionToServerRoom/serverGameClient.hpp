//
// Created by victor on 30/11/16.
//

#ifndef RTYPE_SERVERGAMECLIENT_HPP
#define RTYPE_SERVERGAMECLIENT_HPP


#include <iostream>
#include <Network/TCP/ATCPServer.hpp>
#include <Network/TCP/ATCPClient.hpp>
#include <Protocol/Server/ServerPackageFactory.hpp>
#include "Protocol/Server/ProtocolPrintServerPackage.hpp"

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

#include "Protocol/Server/ServerPackageFactory.hpp"
#include "Protocol/Server/IProtocolServerHandler.hpp"
#include "Protocol/Server/RTypeProtocolServerManager.hpp"

class BasicClient : public Network::TCP::ATCPClient, public IProtocolServerHandler
{
public:
    BasicClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Network::TCP::ATCPClient(dispatcher), protocolServerManager(*this)
    {

    }

    BasicClient(Network::Core::BasicConnection &ref) :
            Network::TCP::ATCPClient(ref.Dispatcher()), protocolServerManager(*this)
    {

    }

    virtual ~BasicClient()
    {
        std::cout << "\e[31mDestructor called\e[0m" << std::endl;
    }

private:
    RTypeProtocolServerManager protocolServerManager;

public:
    virtual void OnDataReceived(unsigned int len)
    {
        std::cout << "Receiving " << buff << std::endl;
        if (!protocolServerManager.handleProtocol(buff.buff(), buff.getLength())) {
            std::cout << "unknown cmd" << std::endl;
        }
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << "Number of bytes sent: " << len << std::endl;
    }

    virtual void OnStart() {
        this->SendData(*(factory.create<AUTHENTICATEPackageServer>(0, 3)));
    }

public:

    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &obj) {
        std::cout << obj << std::endl;
    }

    virtual void onGetLAUNCHPackage(LAUNCHPackageServer const &obj) {
        std::cout << obj << std::endl;
        this->SendData<LAUNCHPackageServer>(*factory.create<LAUNCHPackageServer>(obj.roomPlayer, obj.mapID, obj.secret));
    }

    virtual void onGetSTATUSPackage(STATUSPackageServer const &obj) {
        std::cout << obj << std::endl;
    }

private:
    ServerPackageFactory factory;
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


#endif //RTYPE_SERVERGAMECLIENT_HPP
