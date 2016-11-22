//
// Created by gaspar_q on 6/6/16.
//

#ifndef PSU_2015_ZAPPY_SOCKET_HPP
#define PSU_2015_ZAPPY_SOCKET_HPP

//extern "C"
//{
//# ifdef __linux__
//#  include <sys/types.h>
//#  include <sys/socket.h>
//#  include <sys/select.h>
//#  include <netdb.h>
//#  include <netinet/in.h>
//#  include <arpa/inet.h>
//# elif _WIN32
//#  include <winsock2.h>
//#  include <ws2tcpip.h>
//# endif
//};

//#include <network/ISockStream.hpp>
//#include "INativeSocketContainer.hpp"
//#include "ISocket.hpp"

//#define __linux__

#ifdef __linux__
# include <string>
# include <stdexcept>
# include "ASocket.hpp"

namespace Network
{
    namespace Socket
    {
        class UnixSocket : public ASocket
        {
        public:
            UnixSocket(const Protocol &protocol = Socket::TCP, const sa_family_t domain = AF_INET, int option = 1);
            virtual ~UnixSocket();

            //IStream
        public:
            virtual int Receive(Core::NetBuffer &buff);
            virtual int Send(Core::NetBuffer &buff);

            virtual int ReceiveFrom(Core::NetBuffer &buff, ISockStream &sender);
            virtual int SendTo(Core::NetBuffer &buff, ISockStream const &receiver);

        public:
            void Open() throw(SocketException);
            void Close();
        };
    }
}
#endif

#endif //PSU_2015_ZAPPY_SOCKET_HPP
