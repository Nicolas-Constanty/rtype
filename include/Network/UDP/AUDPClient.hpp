//
// Created by gaspar_q on 11/25/16.
//

#ifndef RTYPE_AUDPCLIENT_HPP
#define RTYPE_AUDPCLIENT_HPP

#include <Network/Core/INetBufferContainer.hpp>
#include <bits/unique_ptr.h>
#include "AUDPConnection.hpp"

namespace Network
{
    namespace UDP
    {
        /**
         * @brief Abstraction of an UDP client
         */
        class AUDPClient : public AUDPConnection, public Core::INetBufferContainer
        {
        public:
            /**
             * @brief Basic construtor
             * @tparam ClientType The type of the client model
             */
            template <typename ClientType>
            AUDPClient(ClientType * const model, Core::NativeSocketIOOperationDispatcher &dispatcher) :
                    AUDPConnection(dispatcher),
                    buff(),
                    model(new ClientType(*model)),
                    server(Socket::UDP)
            {

            }

            /**
             * @brief Basic copy constructor
             * @param ref The reference to copy
             */
            AUDPClient(AUDPClient const &ref);

            virtual ~AUDPClient();

            //AUDPConnection
        public:
            virtual void OnAllowedToRead();
            virtual void OnAllowedToWrite();

            //Core::INetBufferContainer
        public:
            virtual Core::NetBuffer const &getBuffer() const;
            virtual Core::NetBuffer &giveBuffer();
            virtual void setBuffer(Core::NetBuffer const &buff);

        public:
            void Connect(std::string const &ip, const uint16_t port);

        protected:
            Core::NetBuffer buff;

        private:
            std::unique_ptr<Network::Socket::ISockStreamHandler> model;
            Socket::OSSocket server;
        };
    }
}

#endif //RTYPE_AUDPCLIENT_HPP
