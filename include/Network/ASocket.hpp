//
// Created by gaspar on 21/11/2016.
//

#ifndef NETWORK_ASOCKET_HPP
#define NETWORK_ASOCKET_HPP

#include <iostream>
#include "INativeSocketContainer.hpp"
#include "ISockStream.hpp"
#include "ISocket.hpp"

namespace Network
{
    namespace Socket
    {
        struct Protocol
        {
            const int proto;
            const int type;

            bool operator==(Protocol const &ref) const
            {
                return proto == ref.proto && type == ref.type;
            }

            bool operator!=(Protocol const &ref) const
            {
                return !(*this == ref);
            }
        };

        static const Protocol TCP = {IPPROTO_TCP, SOCK_STREAM};
        static const Protocol UDP = {IPPROTO_UDP, SOCK_DGRAM};
        static const SOCKET      DEFAULT = (SOCKET)-1;

        class ASocket : public ISocket, public ISockStream, public INativeSocketContainer
        {
        public:
            ASocket(const Protocol &protocol = Socket::TCP, const sa_family_t domain = AF_INET, int option = 1);
            virtual ~ASocket();
            ASocket(ASocket const &ref);

        public:
            ASocket &operator=(ASocket const &ref);

        public:
            bool    operator==(ASocket const &ref);

            //IStream
        public:
            virtual int Receive(Core::NetBuffer &buff) = 0;
            virtual int Send(Core::NetBuffer &buff) = 0;

            virtual int ReceiveFrom(Core::NetBuffer &buff, ISockStream &sender) = 0;
            virtual int SendTo(Core::NetBuffer &buff, ISockStream const &receiver) = 0;

            //INativeSocketContainer
        public:
            virtual SOCKET Native() const;

            //ISocket
        public:
            virtual void Open() throw(SocketException) = 0;
            virtual void Close() = 0;

            virtual void Listen(const uint16_t port, const int nbc = SOMAXCONN) throw(SocketException);
            virtual void Talk(const std::string &ip, const uint16_t port) throw(SocketException);

            virtual void Accept(ISocket &sock);

        public:
            void print(std::ostream &output = std::cout) const;

        protected:
            const Protocol      &protocol;
            const sa_family_t   domain;
            const int           option;
            struct sockaddr_in  sockaddr;
            SOCKET              fd;
        };

        std::ostream    &operator<<(std::ostream &output, ASocket const &ref);
    }
}

#endif //NETWORK_ASOCKET_HPP
