//
// Created by victor on 21/11/16.
//

#include <iostream>
#include <unistd.h>
#include <Protocol/Game/ProtocolGamePackage.hpp>
#include <Protocol/Room/RTypeProtocolRoomManager.hpp>
#include "Protocol/Server/RTypeProtocolServerManager.hpp"
#include "Protocol/Server/ServerPackageFactory.hpp"
#include "Protocol/Server/IProtocolServerHandler.hpp"
#include "Protocol/Server/ProtocolPrintServerPackage.hpp"
#include "Protocol/PackageSerialize.hpp"
#include "Protocol/Room/IProtocolRoomHandler.hpp"
#include "Protocol/Room/ProtocolPrintRoomPackage.hpp"

class test : public IProtocolRoomHandler, public IProtocolServerHandler {
public:
    virtual  ~test() {

    }

public:
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &obj) {
        std::cout << obj << std::endl;
    }
    virtual void onGetLAUNCHPackage(LAUNCHPackageServer const &obj) {
        std::cout << obj << std::endl;
    }
    virtual void onGetSTATUSPackage(STATUSPackageServer const &obj) {
        std::cout << obj << std::endl;
    }


    // ROOM PROTOCOL

    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &obj) {
        std::cout << obj << std::endl;
//        obj.
    }

    virtual void onGetCREATEPackage(CREATEPackageRoom const &obj) {
        std::cout << obj << std::endl;
    }

    virtual void onGetJOINPackage(JOINPackageRoom const &obj) {
        std::cout << obj << std::endl;
    }

    virtual void onGetQUITPackage(QUITPackageRoom const &obj) {
        std::cout << obj << std::endl;
    }

    virtual void onGetPLUGGEDPackage(PLUGGEDPackageRoom const &obj) {
        std::cout << obj << std::endl;
    }

    virtual void onGetSWAPPackage(SWAPPackageRoom const &obj) {
        std::cout << obj << std::endl;
    }

    virtual void onGetGETPackage(GETPackageRoom const &obj) {
        std::cout << obj << std::endl;
    }

    virtual void onGetFAILUREPackage(FAILUREPackageRoom const &obj) {
        std::cout << obj << std::endl;
    }
};

typedef  AUTHENTICATEPackageServer  TYPE;

int main() {
    test test;
//
    RTypeProtocolServerManager protocol(test);
    RTypeProtocolRoomManager protocolRoomManager(test);
//
//    ServerPackageFactory factory;

    // print
//    TYPE *PING = factory.create<TYPE>(456789);

//    PackageSerialize::print<TYPE>(*PING);
//    return (0);

    // verification
    unsigned char lol[1024];
    int re = (int) read(0, &lol, sizeof(lol));

    if (!protocol.handleProtocol((unsigned char *)lol, (size_t)re)) {
        if (!protocolRoomManager.handleProtocol((unsigned char *)lol, (size_t)re)) {
            std::cout << "FAILED" << std::endl;
        }
    }

    return (0);
}