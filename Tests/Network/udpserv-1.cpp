//
// Created by gaspar_q on 11/22/16.
//

#include <Network/NativeSocketIOOperationDispatcher.hpp>
#include <csignal>
#include <zconf.h>

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
    Network::Socket::UnixSocket socket1(Network::Socket::UDP);
    fd_set s;
    Network::Core::NetBuffer    buff;
    Network::Socket::UnixSocket rec;

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
        std::cout << "Selecting socket" << std::endl;
//        select(socket1.Native() + 1, &s, NULL, NULL, NULL);
//        if (FD_ISSET(socket1.Native(), &s))
//        {
            socket1.ReceiveFrom(buff, rec);
            std::cout << "Reception of \"" << buff.toString() << "\" from " << rec << std::endl;
//        }
//        usleep(500000);
    }
    socket1.Close();
    return 0;
}