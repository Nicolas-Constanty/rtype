//
// Created by victor on 29/11/16.
//

#include "Protocol/Game/ProtocolPrintGamePackage.hpp"
#include <string>

std::ostream &operator<<(std::ostream &ostream, PackageGameHeader const &packageGameHeader) {
    ostream << "verleft=" << packageGameHeader.headerGameInfo.verLeft << std::endl;
    ostream << "verRight=" << packageGameHeader.headerGameInfo.verRight << std::endl;
    ostream << "reservedLeftOne=" << packageGameHeader.headerGameInfo.reservedLeftOne << std::endl;
    ostream << "reservedLeftZero=" << packageGameHeader.headerGameInfo.reservedLeftZero << std::endl;
    ostream << "reservedMiddleOne=" << packageGameHeader.headerGameInfo.reservedMiddleOne << std::endl;
    ostream << "reservedRightZero=" << packageGameHeader.headerGameInfo.reservedRightZero << std::endl;
    ostream << "reservedRightOne=" << packageGameHeader.headerGameInfo.reservedRightOne << std::endl;
    ostream << "reliable=" << packageGameHeader.headerGameInfo.reliable << std::endl;
    ostream << "length=" << packageGameHeader.length << std::endl;
    ostream << "sequenceID=" << packageGameHeader.sequenceID << std::endl;
    ostream << "purpose=" << static_cast<unsigned int>(packageGameHeader.purpose) << std::endl;
    ostream << "transactionID=" << packageGameHeader.transactionID << std::endl;
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, PINGPackageGame const &pingPackageGame) {
    ostream << "PINGPackageGame = {" << std::endl;

    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&pingPackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "secret=" << pingPackageGame.secret << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, AUTHENTICATEPackageGame const &authenticatePackageGame) {
    ostream << "AUTHENTICATEPackageGame = {" << std::endl;

    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&authenticatePackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "secret=" << authenticatePackageGame.secret << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, CREATEPackageGame const &createPackageGame) {
    ostream << "CREATEPackageGame = {" << std::endl;

    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&createPackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "objectID=" << createPackageGame.objectID << std::endl;
    ostream << "posX=" << createPackageGame.posX << std::endl;
    ostream << "posY=" << createPackageGame.posY << std::endl;
    ostream << "ID=" << createPackageGame.ID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, STATUSPackageGame const &statusPackageGame) {
    ostream << "STATUSPackageGame = {" << std::endl;

    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&statusPackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "objectID=" << statusPackageGame.objectID << std::endl;
    ostream << "highScore=" << statusPackageGame.highScore << std::endl;
    ostream << "run=" << statusPackageGame.run << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, MOVEPackageGame const &movePackageGame) {
    ostream << "MOVEPackageGame = {" << std::endl;

    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&movePackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "objectID=" << movePackageGame.objectID << std::endl;
    ostream << "posX=" << movePackageGame.posX << std::endl;
    ostream << "posY=" << movePackageGame.posY << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, BEAMPackageGame const &beamPackageGame) {
    ostream << "BEAMPackageGame = {" << std::endl;

    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&beamPackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "objectID=" << beamPackageGame.objectID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, SHOTPackageGame const &shotPackageGame) {
    ostream << "SHOTPackageGame = {" << std::endl;

    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&shotPackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "objectID=" << shotPackageGame.objectID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, DIEPackageGame const &diePackageGame) {
    ostream << "DIEPackageGame = {" << std::endl;

    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&diePackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "objectID=" << diePackageGame.objectID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, TAKEPackageGame const &takePackageGame) {
    ostream << "TAKEPackageGame = {" << std::endl;

    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&takePackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "objectID=" << takePackageGame.objectID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, DROPPackageGame const &dropPackageGame) {
    ostream << "DROPPackageGame = {" << std::endl;

    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&dropPackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "objectID=" << dropPackageGame.objectID << std::endl;
    ostream << "}";
    return (ostream);
}


std::ostream &operator<<(std::ostream &ostream, LAUNCHPackageGame const &launchPackageGame) {
    ostream << "LAUNCHPackageGame = {" << std::endl;

    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&launchPackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "objectID=" << launchPackageGame.objectID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, REBORNPackageGame const &rebornPackageGame)
{
    ostream << "REBORNPackageGame = {" << std::endl;
    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&rebornPackageGame);
    if (header)
    {
        ostream << *header;
    }
    ostream << "objectID=" << rebornPackageGame.objectID << std::endl << "}";
    return ostream;
}

std::ostream &operator<<(std::ostream &ostream, FAILUREPackageGame const &failurePackageGame)
{
    ostream << "FAILUREPackageGame = {" << std::endl;
    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&failurePackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "failPurpose=" << failurePackageGame.failPurpose << std::endl;
    ostream << "failSequence=" << failurePackageGame.failSequence << std::endl;
    ostream << "}" << std::endl;
    return ostream;
}

std::ostream &operator<<(std::ostream &ostream, INPUTPackageGame const &inputPackageGame)
{
    ostream << "INPUTPackageGame = {" << std::endl;
    PackageGameHeader const *header = dynamic_cast<PackageGameHeader const *>(&inputPackageGame);
    if (header) {
        ostream << *header;
    }
    ostream << "axes=" << std::string(inputPackageGame.axes) << std::endl;
    ostream << "value=" << inputPackageGame.value << std::endl;
    ostream << "}" << std::endl;
    return ostream;
}

std::ostream    &operator<<(std::ostream &output, DISCONNECTPackageGame const &disconnectPackageGame)
{
    output << "DISCONNECTPackageGame = {" << std::endl;
    output << dynamic_cast<PackageGameHeader const &>(disconnectPackageGame);
    output << "playerID=" << disconnectPackageGame.playerID << std::endl;
    output << "}" << std::endl;
    return output;
}