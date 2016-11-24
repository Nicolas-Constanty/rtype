//
// Created by victor on 21/11/16.
//

#include <iostream>
#include <unistd.h>
#include "Protocol/Game/RTypeProtocolGameManager.hpp"
#include "Protocol/Game/GamePackageFactory.hpp"
#include "Protocol/Game/IProtocolGameHandler.hpp"
#include "Protocol/Game/ProtocolPrintGamePackage.hpp"

class test : public IProtocolGameHandler {
public:
    virtual  ~test() {

    }

public:
    virtual void onGetPINGPackage(PINGPackageGame const &pingPackageGame) {
        std::cout << "onGetPINGPackage" << std::endl;
        std::cout << pingPackageGame << std::endl;
    }

    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &authenticatePackageGame) {
        std::cout << "onGetAUTHENTICATEPackage" << std::endl;
        std::cout << authenticatePackageGame << std::endl;
    }

    virtual void onGetCREATEPackage(CREATEPackageGame const &createPackageGame) {
        std::cout << "onGetCREATEPackage" << std::endl;
        std::cout << createPackageGame << std::endl;
    }
    virtual void onGetBEAMPackage(BEAMPackageGame const &beamPackageGame) {
        std::cout << "onGetBEAMPackage" << std::endl;
        std::cout << beamPackageGame << std::endl;
    }

    virtual void onGetSHOTPackage(SHOTPackageGame const &shotPackageGame) {
        std::cout << "onGetSHOTPackage" << std::endl;
        std::cout << shotPackageGame << std::endl;
    }

    virtual void onGetDIEPackage(DIEPackageGame const &diePackageGame) {
        std::cout << "onGetDIEPackage" << std::endl;
        std::cout << diePackageGame << std::endl;
    }

    virtual void onGetTAKEPackage(TAKEPackageGame const &takePackageGame) {
        std::cout << "onGetTAKEPackage" << std::endl;
        std::cout << takePackageGame << std::endl;
    }

    virtual void onGetDROPPackage(DROPPackageGame const &dropPackageGame) {
        std::cout << "onGetDROPPackage" << std::endl;
        std::cout << dropPackageGame << std::endl;
    }

    virtual void onGetMOVEPackage(MOVEPackageGame const &movePackageGame) {
        std::cout << "onGetMOVEPackage" << std::endl;
        std::cout << movePackageGame << std::endl;
    }

    virtual void onGetLAUNCHPackage(LAUNCHPackageGame const &launchPackageGame) {
        std::cout << "LAUNCHPackageGame" << std::endl;
        std::cout << launchPackageGame << std::endl;
    }
    virtual void onGetSTATUSPackage(STATUSPackageGame const &statusPackageGame) {
        std::cout << "onGetSTATUSPackage" << std::endl;
        std::cout << statusPackageGame << std::endl;
    }

};

typedef  AUTHENTICATEPackageGame TYPE;

int main() {
    test test;
//
    RTypeProtocolGameManager protocol(test);
//
//    GamePackageFactory factory;

    // print
//    TYPE *PING = factory.create<TYPE>(345678, 123, 111);

//    std::cout << *PING << std::endl;
//    GamePackageSerialize::print<TYPE>(*PING);

    // verification
    unsigned char lol[1024];
    int re = (int) read(0, &lol, sizeof(lol));

    if (!protocol.handleProtocol((unsigned char *)lol, (size_t)re)) {
        std::cout << "FAILED" << std::endl;
    }

    return (0);
}