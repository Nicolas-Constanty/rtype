//
// Created by gaspar_q on 11/22/16.
//

#include <csignal>

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include <Network/Core/NetBuffer.hpp>
#include <Network/Socket/ISocket.hpp>

#ifdef __linux__
#include <unistd.h>
 #include <Network/UnixSocket.hpp>
#elif _WIN32
#include <c++/iostream>
 #include <Network/Socket/WinSocket.hpp>

#endif

static bool run = true;

void catchb(int)
{
    if (run)
        run = false;
    else
        abort();
}

int main()
{
#ifdef _WIN32
    Network::Socket::WinSocket::Start();
#endif

    Network::Socket::OSSocket socket1(Network::Socket::UDP);
    fd_set s;
    Network::Core::NetBuffer    buff;
    Network::Socket::OSSocket rec;

    try
    {
        socket1.Open();
    }
    catch (Network::Socket::SocketException const &err)
    {
        std::cerr << "Open fail: " << err.what() << std::endl;
        return 1;
    }

    try
    {
        socket1.Listen(4242);
    }
    catch (Network::Socket::SocketException const &err)
    {
        std::cerr << "Listen fail: " << err.what() << std::endl;
        return 1;
    }

    signal(SIGINT, catchb);

    while (run)
    {
        FD_ZERO(&s);
        FD_SET(socket1.Native(), &s);
        std::cout << "Receiving data" << std::endl;
        struct timeval timeout = {1, 0};
        select(socket1.Native() + 1, &s, NULL, NULL, &timeout);
        if (FD_ISSET(socket1.Native(), &s))
        {
            std::cout << "Length received: " << socket1.ReceiveFrom(buff, rec) << std::endl;
            std::cout << "Reception of \"" << buff.toString() << "\" from " << rec << std::endl;
            buff.setTextMessage("Je te dis que j'ai reçu");
            socket1.SendTo(buff, rec);
        }
        else
        {
            std::cout << "No one found" << std::endl;
        }
    }
    socket1.Close();
#ifdef _WIN32
    Network::Socket::WinSocket::Stop();
#endif
    return 0;
}