//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_PROTOCOLPRINTGAMEPACKAGE_HPP
#define RTYPE_PROTOCOLPRINTGAMEPACKAGE_HPP

#include <iostream>
#include "Protocol/Game/ProtocolGamePackage.hpp"

std::ostream &operator<<(std::ostream &ostream, PackageGameHeader const &packageGameHeader);
std::ostream &operator<<(std::ostream &ostream, PINGPackageGame const &pingPackageGame);
std::ostream &operator<<(std::ostream &ostream, AUTHENTICATEPackageGame const &authenticatePackageGame);
std::ostream &operator<<(std::ostream &ostream, CREATEPackageGame const &createPackageGame);
std::ostream &operator<<(std::ostream &ostream, STATUSPackageGame const &statusPackageGame);
std::ostream &operator<<(std::ostream &ostream, MOVEPackageGame const &movePackageGame);
std::ostream &operator<<(std::ostream &ostream, BEAMPackageGame const &beamPackageGame);
std::ostream &operator<<(std::ostream &ostream, SHOTPackageGame const &shotPackageGame);
std::ostream &operator<<(std::ostream &ostream, DIEPackageGame const &diePackageGame);
std::ostream &operator<<(std::ostream &ostream, TAKEPackageGame const &takePackageGame);
std::ostream &operator<<(std::ostream &ostream, CALLPackageGame const &dropPackageGame);
std::ostream &operator<<(std::ostream &ostream, LAUNCHPackageGame const &launchPackageGame);
std::ostream &operator<<(std::ostream &ostream, REBORNPackageGame const &rebornPackageGame);
std::ostream &operator<<(std::ostream &ostream, FAILUREPackageGame const &failurePackageGame);
//std::ostream &operator<<(std::ostream &ostream, INPUTPackageGame const &inputPackageGame);
std::ostream &operator<<(std::ostream &ostream, DISCONNECTPackageGame const &disconnectPackageGame);
std::ostream &operator<<(std::ostream &ostream, ENEMYSHOTPackageGame const &enemyshotPackageGame);
std::ostream &operator<<(std::ostream &ostream, UPGRADEPackageGame const &upgradePackageGame);
std::ostream &operator<<(std::ostream &ostream, MATEPackageGame const &matePackageGame);
std::ostream &operator<<(std::ostream &ostream, GAMEOVERPackageGame const &gameoverPackageGame);
std::ostream &operator<<(std::ostream &ostream, DEATHPackage const &disablePackage);
std::ostream &operator<<(std::ostream &ostream, RECONNECTPackageGame const &reconnectPackageGame);

#endif //RTYPE_PROTOCOLPRINTGAMEPACKAGE_HPP
