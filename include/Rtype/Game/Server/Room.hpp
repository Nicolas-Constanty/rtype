//
// Created by gaspar_q on 11/30/16.
//

#ifndef RTYPE_ROOM_HPP
#define RTYPE_ROOM_HPP

#include "RtypeGameServer.hpp"
#include "GameServerObject.hpp"

namespace Rtype
{
    namespace Game
    {
        namespace Server
        {
            class Room
            {
            public:
                Room();
                ~Room();

            public:
                void Start(const uint16_t port = 4242, const unsigned int max = 4, const uint32_t secret = 0);
                void Run();

            private:
                GameServerObject *server;
            };
        }
    }
}

#endif //RTYPE_ROOM_HPP