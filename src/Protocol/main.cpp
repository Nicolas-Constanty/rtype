//
// Created by victor on 21/11/16.
//

#include <iostream>
#include <Protocol/RTypeProtocolGameManager.hpp>
#include <Protocol/GamePackageFactory.hpp>
#include "Protocol/IProtocolGameHandler.hpp"

class test : public IProtocolGameHandler {
public:
    virtual void onGetPINGPackage(PINGPackageGame const &) {
        std::cout << "onGetPINGPackage" << std::endl;
    }

    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &) {
        std::cout << "onGetAUTHENTICATEPackage" << std::endl;
    }

    virtual void onGetCREATEPackage(CREATEPackageGame const &) {
        std::cout << "onGetCREATEPackage" << std::endl;
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
};

int main() {
    test test;
    char *toto = "toto";

    RTypeProtocolGameManager protocol(test);

    protocol.handleProtocol(toto);

    GamePackageFactory factory;

    BEAMPackageGame *BEAM = factory.create<BEAMPackageGame>(1, 1);
    std::cout << BEAM->length << std::endl;

    return (0);
}