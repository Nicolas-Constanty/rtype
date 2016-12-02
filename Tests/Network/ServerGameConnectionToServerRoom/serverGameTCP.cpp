//
// Created by victor on 30/11/16.
//

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include "serverGameClient.hpp"
#include <unistd.h>
#include <vector>
#include <sys/select.h>
#include <sstream>
#include <cstdlib>


bool inputAvailable()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    select(1, &fds, NULL, NULL, &tv);
    return (FD_ISSET(0, &fds));
}

#include "Protocol/Server/ServerPackageFactory.hpp"

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


int main()
{
    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
    BasicClient client(dispatcher);

    client.Connect("127.0.0.1", 4242);
    dispatcher.setTimeout((const struct timeval){0, 0});
    dispatcher.Watch(client, Network::Core::NativeSocketIOOperationDispatcher::READ);

    ServerPackageFactory factory;
//    dispatcher.Run();
    while (12) {
        std::string buffer;
        dispatcher.Poll();
        if (inputAvailable()) {
            std::getline(std::cin, buffer);
            std::vector<std::string> cmds = split(buffer, ' ');
            if (cmds[0] == "STATUS" && cmds.size() == 2) {
                client.SendData(*(factory.create<STATUSPackageServer>((unsigned int)std::atoi(cmds[1].c_str()), ServerInformation::SERVEROVER)));
            }
            else {
                std::cout << "unknown cmd" << std::endl;
            }
            std::cout << buffer << std::endl;
        }
        usleep(3000);

    }
    return 0;
}