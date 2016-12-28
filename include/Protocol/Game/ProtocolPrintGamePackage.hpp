//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_PROTOCOLPRINTGAMEPACKAGE_HPP
#define RTYPE_PROTOCOLPRINTGAMEPACKAGE_HPP

#include <iostream>
#include "Protocol/Game/ProtocolGamePackage.hpp"

PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, PackageGameHeader const &packageGameHeader);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, PINGPackageGame const &pingPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, AUTHENTICATEPackageGame const &authenticatePackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, CREATEPackageGame const &createPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, STATUSPackageGame const &statusPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, MOVEPackageGame const &movePackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, BEAMPackageGame const &beamPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, SHOTPackageGame const &shotPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, DIEPackageGame const &diePackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, TAKEPackageGame const &takePackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, CALLPackageGame const &dropPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, LAUNCHPackageGame const &launchPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, REBORNPackageGame const &rebornPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, FAILUREPackageGame const &failurePackageGame);
//std::ostream &operator<<(std::ostream &ostream, INPUTPackageGame const &inputPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, DISCONNECTPackageGame const &disconnectPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, ENEMYSHOTPackageGame const &enemyshotPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, UPGRADEPackageGame const &upgradePackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, MATEPackageGame const &matePackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, GAMEOVERPackageGame const &gameoverPackageGame);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, DEATHPackage const &disablePackage);
PREF_EXPORT std::ostream &operator<<(std::ostream &ostream, RECONNECTPackageGame const &reconnectPackageGame);

#endif //RTYPE_PROTOCOLPRINTGAMEPACKAGE_HPP
