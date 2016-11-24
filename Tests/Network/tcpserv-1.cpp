//
// Created by gaspar_q on 11/24/16.
//

#include <Network/TCP/ATCPServer.hpp>
#include <Network/TCP/ATCPClient.hpp>
#include <Network/Core/NetBuffer.hpp>

class TestSwapClient : public Network::TCP::ATCPClient
{
public:
    TestSwapClient() :
            Network::TCP::ATCPClient()
    {

    }

    TestSwapClient(Network::TCP::ATCPClient const &ref) :
            Network::TCP::ATCPClient(ref)
    {

    }

    virtual ~TestSwapClient()
    {

    }

public:
    virtual void OnDataReceived(unsigned int len)
    {
        std::cout << "Réception nouveau client: \"" << buff.toString() << "\" of len: " << len << std::endl;
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << len << " bytes sent" << std::endl;
    }
};

class BasicClient : public Network::TCP::ATCPClient
{
public:
    BasicClient() :
            Network::TCP::ATCPClient()
    {

    }

    virtual ~BasicClient()
    {
        std::cout << "\e[31mDestructor called\e[0m" << std::endl;
    }

public:
    virtual void OnDataReceived(unsigned int len)
    {
        std::cout << "Receiving \"" << buff.toString() << "\" of len: " << len << std::endl;
        if (buff.toString() == "change\n")
        {
            std::cout << "Changing client to Testswap client" << std::endl;
            TestSwapClient  *newc = new TestSwapClient(*this);
            newc->pushBuffer(Network::Core::NetBuffer("on est bon\n"));
            Network::Core::NativeSocketIOOperationDispatcher::Instance().Swap(*this, *newc);
        }
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << "Number of bytes sent: " << len << std::endl;
    }
};

class BasicTCPServ : public Network::TCP::ATCPServer<BasicClient>
{
public:
    BasicTCPServ() :
            Network::TCP::ATCPServer<BasicClient>()
    {
        Start(4242);
    }

    virtual ~BasicTCPServ()
    {
        Stop();
    }

public:
    virtual void OnDataReceived(unsigned int)
    {
        std::cout << "New client accepted" << std::endl;
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << "Number of bytes sent: " << len << std::endl;
    }
};

int main()
{
    BasicTCPServ    serv;

    Network::Core::NativeSocketIOOperationDispatcher::Instance().Watch(serv);
    Network::Core::NativeSocketIOOperationDispatcher::Instance().setTimeout((struct timeval){5, 0});
    Network::Core::NativeSocketIOOperationDispatcher::Instance().Run();
    return 0;
}