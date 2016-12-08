//
// Created by gaspar_q on 11/25/16.
//

#ifndef RTYPE_AUDPCLIENT_HPP
#define RTYPE_AUDPCLIENT_HPP

#include <Network/Core/INetBufferContainer.hpp>
#include <memory>
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
            AUDPClient(Core::NativeSocketIOOperationDispatcher &dispatcher);
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

        public:
            void setServer(Core::BasicConnection *server);

        protected:
            Core::NetBuffer buff;
            Core::BasicConnection *serverStream;

        private:
            Socket::OSSocket server;
        };
    }
}

#endif //RTYPE_AUDPCLIENT_HPP
