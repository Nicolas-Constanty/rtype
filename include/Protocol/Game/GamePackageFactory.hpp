//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_GAMEPACKAGEFACTORY_HPP
#define RTYPE_GAMEPACKAGEFACTORY_HPP

#include <list>
#include <climits>
#include <bits/unique_ptr.h>
#include "ProtocolGamePackage.hpp"

class GamePackageFactory {
public:
    ~GamePackageFactory() {

    }

    GamePackageFactory() {
        idx = 0;
    }

    template <typename T, class ...Args>
    T *create(Args ...args) {
        T *package = new T(idx, args...);

        _vec.emplace_back(package);
        if (idx == USHRT_MAX) {
            idx = 0;
        } else {
            ++idx;
        }
        return (package);
    }

private:
    unsigned short idx;
    std::list<std::unique_ptr<PackageGameHeader>> _vec;
};

#endif //RTYPE_GAMEPACKAGEFACTORY_HPP
