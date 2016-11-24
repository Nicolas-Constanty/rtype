//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_PROTOCOLPRINTROOMPACKAGE_HPP
#define RTYPE_PROTOCOLPRINTROOMPACKAGE_HPP

#include <iostream>
#include "Protocol/Room/ProtocolRoomPackage.hpp"

std::ostream &operator<<(std::ostream &ostream, PackageRoomHeader const &packageRoomHeader) {
    ostream << "verleft=" << packageRoomHeader.headerRoomInfo.verLeft << std::endl;
    ostream << "middleleft=" << packageRoomHeader.headerRoomInfo.verMiddle << std::endl;
    ostream << "verRight=" << packageRoomHeader.headerRoomInfo.verRight << std::endl;
    ostream << "reservedLeftOne=" << packageRoomHeader.headerRoomInfo.reservedLeftOne << std::endl;
    ostream << "reservedLeftZero=" << packageRoomHeader.headerRoomInfo.reservedLeftZero << std::endl;
    ostream << "reservedMiddleOne=" << packageRoomHeader.headerRoomInfo.reservedMiddleOne << std::endl;
    ostream << "reservedRightZero=" << packageRoomHeader.headerRoomInfo.reservedRightZero << std::endl;
    ostream << "reservedRightOne=" << packageRoomHeader.headerRoomInfo.reservedRightOne << std::endl;
    ostream << "length=" << packageRoomHeader.length << std::endl;
    ostream << "purpose=" << packageRoomHeader.purpose << std::endl;
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, CREATEPackageRoom const &createPackageRoom) {
    ostream << "CREATEPackageRoom = {" << std::endl;

    PackageRoomHeader const *header = dynamic_cast<PackageRoomHeader const *>(&createPackageRoom);
    if (header) {
        ostream << *header;
    }
    ostream << "roomPlayer=" << createPackageRoom.roomPlayer << std::endl;
    ostream << "roomPlayerMax=" << createPackageRoom.roomPlayerMax << std::endl;
    ostream << "name=" << createPackageRoom.name << std::endl;
    ostream << "roomID=" << createPackageRoom.roomID << std::endl;
    ostream << "mapID=" << createPackageRoom.mapID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, JOINPackageRoom const &joinPackageRoom) {
    ostream << "JOINPackageRoom = {" << std::endl;

    PackageRoomHeader const *header = dynamic_cast<PackageRoomHeader const *>(&joinPackageRoom);
    if (header) {
        ostream << *header;
    }
    ostream << "roomID=" << joinPackageRoom.roomID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, QUITPackageRoom const &quitPackageRoom) {
    ostream << "QUITPackageRoom = {" << std::endl;

    PackageRoomHeader const *header = dynamic_cast<PackageRoomHeader const *>(&quitPackageRoom);
    if (header) {
        ostream << *header;
    }
    ostream << "roomID=" << quitPackageRoom.roomID << std::endl;
    ostream << "userID=" << quitPackageRoom.userID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, AUTHENTICATEPackageRoom const &authenticatePackageRoom) {
    ostream << "AUTHENTICATEPackageRoom = {" << std::endl;

    PackageRoomHeader const *header = dynamic_cast<PackageRoomHeader const *>(&authenticatePackageRoom);
    if (header) {
        ostream << *header;
    }
    ostream << "name=" << authenticatePackageRoom.name << std::endl;
    ostream << "userID=" << authenticatePackageRoom.userID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, PLUGGEDPackageRoom const &pluggedPackageRoom) {
    ostream << "PLUGGEDPackageRoom = {" << std::endl;

    PackageRoomHeader const *header = dynamic_cast<PackageRoomHeader const *>(&pluggedPackageRoom);
    if (header) {
        ostream << *header;
    }
    ostream << "name=" << pluggedPackageRoom.name << std::endl;
    ostream << "userID=" << pluggedPackageRoom.userID << std::endl;
    ostream << "roomID=" << pluggedPackageRoom.roomID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, SWAPPackageRoom const &swapPackageRoom) {
    ostream << "SWAPPackageRoom = {" << std::endl;

    PackageRoomHeader const *header = dynamic_cast<PackageRoomHeader const *>(&swapPackageRoom);
    if (header) {
        ostream << *header;
    }
    ostream << "addrIP=" << swapPackageRoom.addrIP << std::endl;
    ostream << "userID=" << swapPackageRoom.port << std::endl;
    ostream << "secret=" << swapPackageRoom.secret << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, GETPackageRoom const &getPackageRoom) {
    ostream << "GETPackageRoom = {" << std::endl;

    PackageRoomHeader const *header = dynamic_cast<PackageRoomHeader const *>(&getPackageRoom);
    if (header) {
        ostream << *header;
    }
    ostream << "roomPlayer=" << getPackageRoom.roomPlayer << std::endl;
    ostream << "roomPlayerMax=" << getPackageRoom.roomPlayerMax << std::endl;
    ostream << "name=" << getPackageRoom.name << std::endl;
    ostream << "roomID=" << getPackageRoom.roomID << std::endl;
    ostream << "mapID" << getPackageRoom.mapID << std::endl;
    ostream << "}";
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, FAILUREPackageRoom const &failurePackageRoom) {
    ostream << "FAILUREPackageRoom = {" << std::endl;

    PackageRoomHeader const *header = dynamic_cast<PackageRoomHeader const *>(&failurePackageRoom);
    if (header) {
        ostream << *header;
    }
    ostream << "purposeFAILED=" << failurePackageRoom.purposeFailed << std::endl;
    ostream << "msg=" << failurePackageRoom.msg << std::endl;
    ostream << "}";
    return (ostream);
}


#endif //RTYPE_PROTOCOLPRINTROOMPACKAGE_HPP
