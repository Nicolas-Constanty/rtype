//
// Created by gaspar_q on 11/28/16.
//

#ifndef RTYPE_RTYPEGAMESERVER_HPP
#define RTYPE_RTYPEGAMESERVER_HPP

#include <Network/UDP/AUDPServer.hpp>
#include <SaltyEngine/SaltyBehaviour.hpp>
#include "RtypeGameClient.hpp"

class RtypeGameServer : public Network::UDP::AUDPServer<RtypeGameClient>, public SaltyEngine::SaltyBehaviour
{
public:
    RtypeGameServer(SaltyEngine::GameObject *obj);
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
};

#endif //RTYPE_RTYPEGAMESERVER_HPP
