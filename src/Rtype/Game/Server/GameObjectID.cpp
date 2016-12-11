//
// Created by gouet_v on 12/11/16.
//

#include <Rtype/Game/Server/GameObjectID.hpp>

unsigned short GameObjectID::NewID() {
    static unsigned short id = 1;
    return id++;
}
