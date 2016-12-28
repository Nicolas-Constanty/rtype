//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_ROOMPACKAGESERIALIZE_HPP
#define RTYPE_ROOMPACKAGESERIALIZE_HPP

#include <cstring>
#include <iostream>
#include "Common/DLLexport.hpp"

class PREF_EXPORT PackageSerialize {
public:
    template <typename T>
    static void print(T const &obj) {
        unsigned char const *data;

        data = (unsigned char const *)&obj;
        write(1, data, sizeof(obj));
    }
};

#endif //RTYPE_ROOMPACKAGESERIALIZE_HPP
