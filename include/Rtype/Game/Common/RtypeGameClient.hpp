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
#if _WIN32
#undef NOERROR
#endif

class GameManager;

namespace Rtype
{
    namespace Game
    {
        namespace Common
        {
            class PREF_EXPORT RtypeGameClient : public Network::UDP::AUDPClient, public IProtocolGameHandler
            {
            public:
                enum class DisconnectionCode : unsigned int
                {
                    NOERROR = 0,
                    ROOMFULL = 1,
                    TIMEOUT = 2
                };

            public:
                static const std::chrono::milliseconds    timeout;

            public:
                RtypeGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
                RtypeGameClient(RtypeGameClient const &ref);
                virtual ~RtypeGameClient();

            public:
                virtual bool OnDataReceived(unsigned int len);
                virtual bool OnDataSent(unsigned int len);
                virtual void OnDisconnect();

            public:
                virtual void onGetDISCONNECTPackage(DISCONNECTPackageGame const &);

            public:
                void setManager(GameManager *manager1);

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

            public:
                template <typename Package, typename SendFunc, typename ... Args>
                void SendPackage(SendFunc func, Args ... args)
                {
                    (this->*func)(*factory.create<Package>(args...));
                }

                template <typename Package, typename SendFunc, typename ... Args>
                void BroadCastPackage(SendFunc func, Args ... args)
                {
                    if (!clients)
                        return;
                    for (Network::Socket::ISockStreamHandler *curr : clients->Streams())
                    {
                        RtypeGameClient *client = dynamic_cast<RtypeGameClient *>(curr);

                        if (client)
                            client->SendPackage<Package>(func, args...);
                    }
                }

            public:
                template <typename T>
                void SendToServerNow(T const &ref)
                {
                    Network::Core::NetBuffer    tosend(ref);

                    if (serverStream)
                        serverStream->giveSocket().SendTo(tosend, giveSocket());
                    else
                        sock.SendTo(tosend, sock);
                }

                template <typename T>
                void SendToServerReliablyNow(T const &ref)
                {
                    for (size_t i = 0; i < reliability; ++i)
                    {
                        SendToServerNow(ref);
                    }
                }

            public:
                void setErrorCode(DisconnectionCode code)
                {
                    errcode = code;
                }

            private:
                RTypeProtocolGameManager    manager;
                GamePackageFactory          factory;

            private:
                Network::UDP::ReceptionStatus<uint16_t, uint32_t>   recvstatus;
                Network::UDP::ReceptionStatus<uint16_t, uint32_t>   sendstatus;

            protected:
                bool reply;
                bool connected;

            protected:
                unsigned char playerID;
                DisconnectionCode errcode;

            protected:
                bool getDisconnected;

            protected:
                GameManager     *gameManager;
            };
        }
    }
}

#endif //RTYPE_RTYPEGAMECLIENT_HPP
