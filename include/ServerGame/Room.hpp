//
// Created by gaspar_q on 11/30/16.
//

#ifndef RTYPE_ROOM_HPP
#define RTYPE_ROOM_HPP

#include "RtypeGameServer.hpp"

namespace Rtype
{
    class Room
    {
    public:
        Room();
        ~Room();

    public:
        void Start(const uint16_t port = 4242);
        void Run();
        void Stop();

    public:
        void setSecure(bool security = true);
        void setSecret(uint32_t secret);

    private:
        RtypeGameServer *server;
        Network::Core::NativeSocketIOOperationDispatcher dispatcher;
    };
}

#endif //RTYPE_ROOM_HPP
