//
// Created by gaspar_q on 11/25/16.
//

#include <Network/UDP/AUDPServer.hpp>
#include <Network/UDP/AUDPClient.hpp>
#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>

class BasicUDPClient : public Network::UDP::AUDPClient
{
public:
    BasicUDPClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Network::UDP::AUDPClient::AUDPClient(this, dispatcher)
    {

    }

    BasicUDPClient(BasicUDPClient const &ref) :
            Network::UDP::AUDPClient(ref)
    {

    }

public:
    virtual void OnDataReceived(unsigned int len)
    {
        std::cout << "Data received: " << getBuffer() << " from " << sock << std::endl;
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << "Sent " << len << " bytes" << std::endl;
    }
};

class BasicUDPServ : public Network::UDP::AUDPServer<BasicUDPClient>
{
public:
    BasicUDPServ(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Network::UDP::AUDPServer<BasicUDPClient>(dispatcher)
    {
        sock.Open();
        sock.Listen(4242);
    }

    ~BasicUDPServ()
    {
        sock.Close();
    }

public:
    virtual void OnDataReceived(unsigned int len)
    {
        std::cout << "Server reception" << std::endl;
        WantSend();
        newclient->SendData("hello\n");
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << "Data server sent" << std::endl;
    }
};

int main()
{
    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
    BasicUDPServ    serv(dispatcher);

    dispatcher.Watch(serv);
    dispatcher.Run();
    return 0;
}