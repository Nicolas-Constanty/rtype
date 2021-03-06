//
// Created by gaspar_q on 11/28/16.
//

#ifndef RTYPE_BASETCP_HPP
#define RTYPE_BASETCP_HPP

#include <iostream>
#include <Network/TCP/ATCPServer.hpp>
#include <Network/TCP/ATCPClient.hpp>
#include <Protocol/Room/RoomPackageFactory.hpp>
#include <stdlib.h>
#include "Protocol/Room/ProtocolPrintRoomPackage.hpp"

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
    virtual bool OnDataReceived(unsigned int len)
    {
        std::cout << "Réception nouveau client: " << buff << std::endl;
        return (true);
    }

    virtual bool OnDataSent(unsigned int len)
    {
        std::cout << len << " bytes sent" << std::endl;
        return (true);
    }
};

#include "Protocol/Room/RoomPackageFactory.hpp"
#include "Protocol/Room/IProtocolRoomHandler.hpp"
#include "Protocol/Room/RTypeProtocolRoomManager.hpp"

class ClientGameRooms : public Network::TCP::ATCPClient, public IProtocolRoomHandler
{
public:
    ClientGameRooms(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Network::TCP::ATCPClient(dispatcher), protocolRoomManager(*this)
    {

    }

    ClientGameRooms(Network::Core::BasicConnection &ref) :
            Network::TCP::ATCPClient(ref.Dispatcher()), protocolRoomManager(*this)
    {

    }

    virtual ~ClientGameRooms()
    {
        std::cout << "\e[31mDestructor called\e[0m" << std::endl;
    }

private:
    RTypeProtocolRoomManager protocolRoomManager;

public:
    virtual bool OnDataReceived(unsigned int len)
    {
        std::cout << "Receiving " << buff << std::endl;
        while (protocolRoomManager.handleProtocol(buff.buff(), buff.getLength())) {
            std::cout << "unknown cmd" << std::endl;
        }
        return true;
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

    virtual bool OnDataSent(unsigned int len)
    {
        std::cout << "Number of bytes sent: " << len << std::endl;
        return (true);
    }

    virtual bool OnStart() {
        this->SendData(*(factory.create<AUTHENTICATEPackageRoom>("toto", 0)));
        return (true);
    }

public:
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &obj) {
        std::cout << obj << std::endl;
//        this->SendData(*(factory.create<CREATEPackageRoom>(0, 2, "koalas", 0, 1)));
        buff += sizeof(obj);
//        this->SendData(*(factory.create<JOINPackageRoom>(1)));
    }

    virtual void onGetCREATEPackage(CREATEPackageRoom const &obj) {
        std::cout << obj << std::endl;
        buff += sizeof(obj);
    }
    virtual void onGetJOINPackage(JOINPackageRoom const &obj) {
        std::cout << obj << std::endl;
        roomID = obj.roomID;
        buff += sizeof(obj);
    }
    virtual void onGetQUITPackage(QUITPackageRoom const &obj) {
        std::cout << obj << std::endl;
        buff += sizeof(obj);
    }
    virtual void onGetPLUGGEDPackage(PLUGGEDPackageRoom const &obj) {
        std::cout << obj << std::endl;
        buff += sizeof(obj);
    }
    virtual void onGetSWAPPackage(SWAPPackageRoom const &obj) {
        std::cout << obj << std::endl;
        buff += sizeof(obj);
    }
    virtual void onGetGETPackage(GETPackageRoom const &obj) {
        std::cout << obj << std::endl;
        buff += sizeof(obj);
    }
    virtual void onGetFAILUREPackage(FAILUREPackageRoom const &obj) {
        std::cout << obj << std::endl;
        buff += sizeof(obj);
//        exit(0);
    }
    virtual void onGetLAUNCHPackage(LAUNCHPackageRoom const &obj) {
        std::cout << obj << std::endl;
        buff += sizeof(obj);
    }

    virtual void onGetDELETEPackage(DELETEPackageRoom const &obj) {
        std::cout << obj << std::endl;
        buff += sizeof(obj);
//        if (obj.roomID == roomID) {
//            exit(0);
//        }
    }

    virtual void onGetCHATPackage(CHATPackageRoom const &obj) {
        std::cout << obj << std::endl;
        buff += sizeof(obj);
    }

public:
    unsigned short roomID = 0;

private:
    RoomPackageFactory factory;
};

class BasicTCPServ : public Network::TCP::ATCPServer<ClientGameRooms>
{
public:
    BasicTCPServ(Network::Core::NativeSocketIOOperationDispatcher &dispatcher, unsigned short port) :
            Network::TCP::ATCPServer<ClientGameRooms>(dispatcher)
    {
        Start(port);
    }

    virtual ~BasicTCPServ()
    {
        Stop();
    }

public:
    virtual bool OnDataReceived(unsigned int)
    {
        std::cout << "New client accepted" << std::endl;
        return (true);
    }

    virtual bool OnDataSent(unsigned int len)
    {
        std::cout << "Number of bytes sent: " << len << std::endl;
        return (true);
    }
};

#endif //RTYPE_BASETCP_HPP
