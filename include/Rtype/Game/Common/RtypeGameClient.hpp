//
// Created by gaspar_q on 11/28/16.
//

#ifndef RTYPE_RTYPEGAMECLIENT_HPP
#define RTYPE_RTYPEGAMECLIENT_HPP

#include <chrono>
#include <iostream>
#include <string>
#include <Protocol/Game/ProtocolPrintGamePackage.hpp>
#include <Network/UDP/AUDPClient.hpp>
#include <Protocol/Game/RTypeProtocolGameManager.hpp>
#include <Protocol/Game/GamePackageFactory.hpp>
#include <Network/UDP/ReceptionStatus.hpp>


namespace Rtype
{
    namespace Game
    {
        namespace Common
        {
            class RtypeGameClient : public Network::UDP::AUDPClient, public IProtocolGameHandler
            {
            public:
                static const std::chrono::milliseconds    timeout;

            public:
                RtypeGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
                RtypeGameClient(RtypeGameClient const &ref);
                virtual ~RtypeGameClient();

            public:
                virtual bool OnDataReceived(unsigned int len);
                virtual bool OnDataSent(unsigned int len);

            protected:
                template <typename Pack>
                void OnDiscoveringPackage(Pack const &pack)
                {
//                    std::cout << "\e[32mDicovering\e[0m: " << pack << std::endl;
                    if (reply)
                    {
                        SendData(pack);
                        if (serverStream)
                            serverStream->WantSend();
                    }
                    buff += sizeof(Pack);
                }

            private:
                RTypeProtocolGameManager    manager;

            private:
                Network::UDP::ReceptionStatus<uint16_t, uint32_t>   recvstatus;
                Network::UDP::ReceptionStatus<uint16_t, uint32_t>   sendstatus;

            protected:
                bool reply;
                bool connected;
            };
        }
    }
}

#endif //RTYPE_RTYPEGAMECLIENT_HPP
