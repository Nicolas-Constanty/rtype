//
// Created by gaspar on 21/11/2016.
//

#ifndef NETWORK_WINSOCKET_HPP
# define NETWORK_WINSOCKET_HPP

# ifdef _WIN32
#  include "Network/Socket/ASocket.hpp"

namespace Network
{
    namespace Socket
    {
        class WinSocket : public ASocket
        {
        public:
            static void Start();
            static void Stop();

        public:
            WinSocket(const Protocol &protocol = Socket::TCP, const sa_family_t domain = AF_INET, int option = 1);
            virtual ~WinSocket();

            //IStreamudpclient
        public:
            virtual int Receive(Core::NetBuffer &buff);
            virtual int Send(Core::NetBuffer const &buff) const;

            virtual int ReceiveFrom(Core::NetBuffer &buff, ISockStream &sender);
            virtual int SendTo(Core::NetBuffer &buff, ISockStream const &receiver);

        public:
            void Open() throw(SocketException);
            void Close();

            static unsigned short GetAvailablePort();
        };

        using OSSocket = WinSocket;
    }
}
# endif

#endif //NETWORK_WINSOCKET_HPP
