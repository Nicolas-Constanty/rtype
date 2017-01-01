//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_ROOMPACKAGEFACTORY_HPP
#define RTYPE_ROOMPACKAGEFACTORY_HPP

#include <list>
#include <memory>
#include "ProtocolRoomPackage.hpp"

class RoomPackageFactory {
public:
    ~RoomPackageFactory() {
		for (PackageRoomHeader *curr : _vec)
		{
			delete curr;
		}
    }

    template <typename T, class ...Args>
    T *create(Args ...args) {
        T *package = new T(args...);

        _vec.emplace_back(package);
        return (package);
    }

private:
    std::list<PackageRoomHeader *> _vec;
};

#endif //RTYPE_ROOMPACKAGEFACTORY_HPP
