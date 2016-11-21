//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_GAMEPACKAGEFACTORY_HPP
#define RTYPE_GAMEPACKAGEFACTORY_HPP

#include <vector>
#include "ProtocolGamePackage.hpp"

class GamePackageFactory {
public:
    ~GamePackageFactory() {

    }

    template <typename T, class ...Args>
    T *create(Args ...args) {
        T *package = new T(args...);

        _vec.push_back(package);
        return (package);
    }

private:
    std::vector<PackageGameHeader *> _vec;
};

#endif //RTYPE_GAMEPACKAGEFACTORY_HPP
