//
// Created by victor on 21/11/16.
//

#include <iostream>
#include <unistd.h>
#include "Protocol/RTypeProtocolGameManager.hpp"
#include "Protocol/GamePackageFactory.hpp"
#include "Protocol/GamePackageSerialize.hpp"
#include "Protocol/IProtocolGameHandler.hpp"
#include "Protocol/ProtocolPrintGamePackage.hpp"

class test : public IProtocolGameHandler {
public:
    virtual  ~test() {

    }

public:
    virtual void onGetPINGPackage(PINGPackageGame const &) {
        std::cout << "onGetPINGPackage" << std::endl;
    }

    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &) {
        std::cout << "onGetAUTHENTICATEPackage" << std::endl;
    }

    virtual void onGetCREATEPackage(CREATEPackageGame const &createPackageGame) {
        std::cout << "onGetCREATEPackage" << std::endl;
        std::cout << createPackageGame << std::endl;
    }
    virtual void onGetBEAMPackage(BEAMPackageGame const &) {
        std::cout << "onGetBEAMPackage" << std::endl;
    }

    virtual void onGetSHOTPackage(SHOTPackageGame const &) {
        std::cout << "onGetSHOTPackage" << std::endl;
    }

    virtual void onGetDIEPackage(DIEPackageGame const &) {
        std::cout << "onGetDIEPackage" << std::endl;
    }

    virtual void onGetTAKEPackage(TAKEPackageGame const &) {
        std::cout << "onGetTAKEPackage" << std::endl;
    }

    virtual void onGetDROPPackage(DROPPackageGame const &) {
        std::cout << "onGetDROPPackage" << std::endl;
    }

    virtual void onGetMOVEPackage(MOVEPackageGame const &) {
        std::cout << "onGetMOVEPackage" << std::endl;
    }

    virtual void onGetLAUNCHPackage(LAUNCHPackageGame const &) {
        std::cout << "LAUNCHPackageGame" << std::endl;
    }
    virtual void onGetSTATUSPackage(STATUSPackageGame const &) {
        std::cout << "onGetSTATUSPackage" << std::endl;
    }

};

int main() {
    test test;
//    char *toto = "toto";

    RTypeProtocolGameManager protocol(test);

//    protocol.handleProtocol((unsigned char *)toto, 12);

//    GamePackageFactory factory;

    //std::cout << sizeof(HeaderGameInfo) << std::endl;
//    CREATEPackageGame *PING = factory.create<CREATEPackageGame>(1, 3, 7, 1, 2, 3);

//    std::cout << *PING << std::endl;

    unsigned char lol[1024];
    int re = (int) read(0, &lol, sizeof(lol));

//    std::cout << re << std::endl;
//    std::cout << sizeof(CREATEPackageGame) << std::endl;
    if (!protocol.handleProtocol((unsigned char *)lol, (size_t)re)) {
        std::cout << "FAILED" << std::endl;
    }
//    std::cout << lol << std::endl;
    //GamePackageSerialize::print<CREATEPackageGame>(*PING);

//
//    BEAMPackageGame *BEAM = factory.create<BEAMPackageGame>(1, 1);

    return (0);
}