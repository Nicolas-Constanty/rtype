//
// Created by gaspar_q on 11/25/16.
//

#ifndef RTYPE_AUDPCONNECTION_HPP
#define RTYPE_AUDPCONNECTION_HPP

#ifdef __linux__
 #include <queue>
#include <Network/Socket/UnixSocket.hpp>
#elif _WIN32
 #include <c++/queue>
 #include <Network/Socket/WinSocket.hpp>
#endif

#include <Network/Socket/ISockStreamHandler.hpp>
#include <Network/Core/BasicConnection.hpp>

namespace Network
{
    namespace UDP
    {
        /**
         * @brief Abstraction of an UDP connection
         */
        class AUDPConnection : public Core::BasicConnection
        {
        public:
            AUDPConnection(Core::NativeSocketIOOperationDispatcher &dispatcher);
            AUDPConnection(AUDPConnection const &);
            virtual ~AUDPConnection();

            //Socket::ISockStreamHandlers
        public:
            virtual Socket::ISocket &giveSocket();
            virtual Socket::ISocket const &getSocket() const;

        public:
            /**
             * @brief Send a package reliably. With 30 packets, we are pretty sure that the packet is received
             * @tparam T The type of the data to send
             * @param ref The data to send
             */
            template <typename T>
            void SendReliable(T const &ref)
            {
                for (size_t i = 0; i < 30; ++i)//todo reset to 30 loops
                    SendData(ref);
            }

            /**
             * @brief Broadcast a package reliably. With 30 packets, we are pretty sure that the packet is received
             * @tparam T The type of the data to send
             * @param ref The data to send
             */
            template <typename T>
            void BroadcastReliable(T const &ref)
            {
                for (size_t i = 0; i < 30; ++i)//todo reset to 30 loops
                    Broadcast(ref);
            }

            /**
             * @brief Broadcast now and reliably. With 30 pakcet, we are pretty sure that the packet is received
             * @tparam T The type of the data to send
             * @param ref The data to send
             */
            template <typename T>
            void BroadcastNowReliable(T const &ref)
            {
                for (size_t i = 0; i < 30; ++i)//todo reset to 30 loops
                    BroadcastNow(ref);
            }

        public:
            virtual bool OnStart();

        protected:
            Socket::OSSocket sock;
        };
    }
}

#endif //RTYPE_AUDPCONNECTION_HPP
