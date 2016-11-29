//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_SERVERPACKAGEFACTORY_HPP
#define RTYPE_SERVERPACKAGEFACTORY_HPP

#include <list>
#include "ProtocolServerPackage.hpp"

class ServerPackageFactory {
public:
    ~ServerPackageFactory() {

    }

    template <typename T, class ...Args>
    T *create(Args ...args) {
        T *package = new T(args...);

        _vec.emplace_back(package);
        return (package);
    }

private:
    std::list<std::unique_ptr<PackageServerHeader>> _vec;
};

#endif //RTYPE_ServerPACKAGEFACTORY_HPP
