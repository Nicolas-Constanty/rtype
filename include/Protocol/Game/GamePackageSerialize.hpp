//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_GAMEPACKAGESERIALIZE_HPP
#define RTYPE_GAMEPACKAGESERIALIZE_HPP

#include <cstring>
#include <iostream>

class GamePackageSerialize {
public:
    template <typename T>
    static void print(T const &obj) {
        size_t i = 0;
        unsigned char const *data;

        data = (unsigned char const *)&obj;
        while (i < sizeof(obj)) {
            std::cout << data[i];
            ++i;
        }
    }
};

#endif //RTYPE_GAMEPACKAGESERIALIZE_HPP
