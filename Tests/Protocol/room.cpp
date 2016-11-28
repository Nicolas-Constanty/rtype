//
// Created by victor on 21/11/16.
//

#include <iostream>
#include <unistd.h>
#include <Protocol/Game/ProtocolGamePackage.hpp>
#include "Protocol/Room/RTypeProtocolRoomManager.hpp"
#include "Protocol/Room/RoomPackageFactory.hpp"
#include "Protocol/Room/IProtocolRoomHandler.hpp"
#include "Protocol/Room/ProtocolPrintRoomPackage.hpp"
#include "Protocol/PackageSerialize.hpp"

class test : public IProtocolRoomHandler {
public:
    virtual  ~test() {

    }

public:
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

typedef  SWAPPackageRoom TYPE;

int main() {
    test test;
//
    RTypeProtocolRoomManager protocol(test);
//
    RoomPackageFactory factory;

    // print
//    TYPE *PING = factory.create<TYPE>(124, 32, 22);

//    PackageSerialize::print<TYPE>(*PING);
//    return (0);

    // verification
    unsigned char lol[1024];
    int re = (int) read(0, &lol, sizeof(lol));

    if (!protocol.handleProtocol((unsigned char *)lol, (size_t)re)) {
        std::cout << "FAILED" << std::endl;
    }

    return (0);
}