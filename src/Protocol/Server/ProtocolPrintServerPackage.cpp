//
// Created by victor on 29/11/16.
//

#include "Protocol/Server/ProtocolPrintServerPackage.hpp"

std::ostream &operator<<(std::ostream &ostream, PackageServerHeader const &packageServerHeader) {
    ostream << "verleft=" << packageServerHeader.headerServerInfo.verLeft << std::endl;
    ostream << "middleleft=" << packageServerHeader.headerServerInfo.verMiddle << std::endl;
    ostream << "verRight=" << packageServerHeader.headerServerInfo.verRight << std::endl;
    ostream << "reservedLeftOne=" << packageServerHeader.headerServerInfo.reservedLeftOne << std::endl;
    ostream << "reservedLeftZero=" << packageServerHeader.headerServerInfo.reservedLeftZero << std::endl;
    ostream << "reservedMiddleOne=" << packageServerHeader.headerServerInfo.reservedMiddleOne << std::endl;
    ostream << "reservedRightZero=" << packageServerHeader.headerServerInfo.reservedRightZero << std::endl;
    ostream << "reservedRightOne=" << packageServerHeader.headerServerInfo.reservedRightOne << std::endl;
    ostream << "length=" << packageServerHeader.length << std::endl;
    ostream << "purpose=" << packageServerHeader.purpose << std::endl;
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, AUTHENTICATEPackageServer const &authenticatePackageServer) {
    ostream << "AUTHENTICATEPackageServer = {" << std::endl;

    PackageServerHeader const *header = dynamic_cast<PackageServerHeader const *>(&authenticatePackageServer);
    if (header) {
        ostream << *header;
    }
    ostream << "userID=" << authenticatePackageServer.userID << std::endl;
    ostream << "roomNumber=" << authenticatePackageServer.roomNumber << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, LAUNCHPackageServer const &launchPackageServer) {
    ostream << "LAUNCHPackageServer = {" << std::endl;

    PackageServerHeader const *header = dynamic_cast<PackageServerHeader const *>(&launchPackageServer);
    if (header) {
        ostream << *header;
    }
    ostream << "secret=" << launchPackageServer.secret << std::endl;
    ostream << "mapID=" << launchPackageServer.mapID << std::endl;
    ostream << "roomPlayer=" << launchPackageServer.roomPlayer << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, STATUSPackageServer const &statusPackageServer) {
    ostream << "STATUSPackageServer = {" << std::endl;

    PackageServerHeader const *header = dynamic_cast<PackageServerHeader const *>(&statusPackageServer);
    if (header) {
        ostream << *header;
    }
    ostream << "secret=" << statusPackageServer.secret << std::endl;
    ostream << "information=" << statusPackageServer.information << std::endl;
    ostream << "}";
    return (ostream);
}
