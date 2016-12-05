//
// Created by gaspar_q on 11/28/16.
//

#ifndef RTYPE_RTYPEGAMESERVER_HPP
#define RTYPE_RTYPEGAMESERVER_HPP

#include <Network/UDP/AUDPServer.hpp>
#include <SaltyEngine/SaltyBehaviour.hpp>
#include "RtypeGameClient.hpp"

namespace Rtype
{
    class RtypeGameServer : public Network::UDP::AUDPServer<RtypeGameClient>, public SaltyEngine::SaltyBehaviour
    {
    public:
        RtypeGameServer(SaltyEngine::GameObject *obj, const uint16_t port = 4242, const int maxSize = 4);
        RtypeGameServer(RtypeGameServer const &ref) = delete;
        virtual ~RtypeGameServer();

    public:
        virtual void OnDataReceived(unsigned int len);
        virtual void OnDataSent(unsigned int len);

    public:
        void Start();
        void Update();

    private:
        Network::Core::NativeSocketIOOperationDispatcher dispatcher;
        GamePackageFactory factory;
        const uint16_t port;
        const int maxSize;
    };
}

#endif //RTYPE_RTYPEGAMESERVER_HPP
