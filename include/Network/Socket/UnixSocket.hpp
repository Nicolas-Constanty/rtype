//
// Created by gaspar_q on 6/6/16.
//

#ifndef PSU_2015_ZAPPY_SOCKET_HPP
#define PSU_2015_ZAPPY_SOCKET_HPP

#ifdef __linux__
# include <string>
# include <stdexcept>
# include "ASocket.hpp"

namespace Network
{
    namespace Socket
    {
        /**
         * @brief Definition of a Unix socket
         */
        class PREF_EXPORT UnixSocket : public ASocket
        {
        public:
            UnixSocket(const Protocol &protocol = Socket::TCP, const sa_family_t domain = AF_INET, int option = 1);
            virtual ~UnixSocket();

            //IStream
        public:
            virtual int Receive(Core::NetBuffer &buff);
            virtual int Send(Core::NetBuffer const &buff) const;

            virtual int ReceiveFrom(Core::NetBuffer &buff, ISockStream &sender);
            int ReceiveFrom(char *arr, size_t n, ISockStream &sender);

            virtual int SendTo(Core::NetBuffer &buff, ISockStream const &receiver);

            int SendTo(char *arr, size_t towr, ISockStream const &receiver);

        public:
            void Open() throw(SocketException);
            void Close();

            static unsigned short GetAvailablePort();

        };

        /**
         * @brief If os on which the compilation is done is __linux__ then defines OSSocket as UnixSocket
         */
        using OSSocket = UnixSocket;
    }
}
#endif

#endif //PSU_2015_ZAPPY_SOCKET_HPP
