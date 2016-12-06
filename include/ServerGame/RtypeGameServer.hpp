//
// Created by gaspar_q on 11/28/16.
//

#ifndef RTYPE_RTYPEGAMESERVER_HPP
#define RTYPE_RTYPEGAMESERVER_HPP

#include <Network/UDP/AUDPServer.hpp>
#include <SaltyEngine/SaltyBehaviour.hpp>
//#include "RtypeGameClient.hpp"
#include "RtypeServerGameClient.hpp"

namespace Rtype
{
    class RtypeGameServer : public Network::UDP::AUDPServer<Rtype::RtypeServerGameClient>, public SaltyEngine::SaltyBehaviour
    {
    public:
        RtypeGameServer(SaltyEngine::GameObject *obj, const uint16_t port = 4242, const int maxSize = 4);
        RtypeGameServer(RtypeGameServer const &ref) = delete;
        virtual ~RtypeGameServer();

    public:
        virtual bool OnDataReceived(unsigned int len);
        virtual bool OnDataSent(unsigned int len);

    public:
        virtual void OnReadCheck();

    public:
        void Start();
        void Update();

    public:
        void setSecret(uint32_t secret);
        bool Authenticate(uint32_t secret);

    public:
        void setSecure(bool security = true);

    private:
        Network::Core::NativeSocketIOOperationDispatcher dispatcher;
        GamePackageFactory factory;
        const uint16_t port;
        const int maxSize;
        uint32_t  secret;
        bool secure;
    };
}

#endif //RTYPE_RTYPEGAMESERVER_HPP
