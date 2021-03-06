//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_GAMEPACKAGEFACTORY_HPP
#define RTYPE_GAMEPACKAGEFACTORY_HPP

#include <stack>
#include <climits>
#include <memory>
#include "ProtocolGamePackage.hpp"
#if _WIN32
#pragma warning( disable : 4244 )
#endif

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

        if (_vec.size() > 100) {
            while (!_vec.empty())
                _vec.pop();
        }
        _vec.emplace(package);
        if (idx == USHRT_MAX) {
            idx = 0;
        } else {
            ++idx;
        }
        return (package);
    }

private:
    unsigned short idx;
    std::stack<std::unique_ptr<PackageGameHeader>> _vec;
};

#endif //RTYPE_GAMEPACKAGEFACTORY_HPP
