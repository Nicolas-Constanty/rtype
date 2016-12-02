//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_PROTOCOLPRINTROOMPACKAGE_HPP
#define RTYPE_PROTOCOLPRINTROOMPACKAGE_HPP

#include <iostream>
#include "Protocol/Room/ProtocolRoomPackage.hpp"

std::ostream &operator<<(std::ostream &ostream, PackageRoomHeader const &packageRoomHeader);
std::ostream &operator<<(std::ostream &ostream, CREATEPackageRoom const &createPackageRoom);
std::ostream &operator<<(std::ostream &ostream, JOINPackageRoom const &joinPackageRoom);
std::ostream &operator<<(std::ostream &ostream, QUITPackageRoom const &quitPackageRoom);
std::ostream &operator<<(std::ostream &ostream, AUTHENTICATEPackageRoom const &authenticatePackageRoom);
std::ostream &operator<<(std::ostream &ostream, PLUGGEDPackageRoom const &pluggedPackageRoom);
std::ostream &operator<<(std::ostream &ostream, SWAPPackageRoom const &swapPackageRoom);
std::ostream &operator<<(std::ostream &ostream, GETPackageRoom const &getPackageRoom);
std::ostream &operator<<(std::ostream &ostream, FAILUREPackageRoom const &failurePackageRoom);
std::ostream &operator<<(std::ostream &ostream, LAUNCHPackageRoom const &launchPackageRoom);
std::ostream &operator<<(std::ostream &ostream, DELETEPackageRoom const &deletePackageRoom);
std::ostream &operator<<(std::ostream &ostream, CHATPackageRoom const &chatPackageRoom);

#endif //RTYPE_PROTOCOLPRINTROOMPACKAGE_HPP
