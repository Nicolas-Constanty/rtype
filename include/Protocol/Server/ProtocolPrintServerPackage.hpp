//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_PROTOCOLPRINTSERVERPACKAGE_HPP
#define RTYPE_PROTOCOLPRINTSERVERPACKAGE_HPP

#include <iostream>
#include "Protocol/Server/ProtocolServerPackage.hpp"

std::ostream &operator<<(std::ostream &ostream, PackageServerHeader const &packageServerHeader);
std::ostream &operator<<(std::ostream &ostream, AUTHENTICATEPackageServer const &authenticatePackageServer);
std::ostream &operator<<(std::ostream &ostream, LAUNCHPackageServer const &launchPackageServer);
std::ostream &operator<<(std::ostream &ostream, STATUSPackageServer const &statusPackageServer);


#endif //RTYPE_PROTOCOLPRINTServerPACKAGE_HPP
