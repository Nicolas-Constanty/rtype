//
// Created by gaspar_q on 12/1/16.
//

#include <ServerGame/RtypeGameClient.hpp>

class udpclient : public Network::UDP::AUDPClient
{
public:
    udpclient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Network::UDP::AUDPClient(dispatcher)
    {

    }

    ~udpclient()
    {

    }

public:
    void OnDataReceived(unsigned int)
    {
        std::cout << "Received: " << buff << std::endl;

        Network::UDP::ReceptionStatus<uint16_t> status;

        status.setStatus(buff.buff<MOVEPackageGame>()->transactionID);
        status.Receiving(buff.buff<MOVEPackageGame>()->sequenceID);

        std::cout << "Status: " << status << std::endl << std::endl;

        static int i = 0;

        if (i < 10)
            SendData(*factory.create<MOVEPackageGame>(15, 42, 8, 0));
        ++i;
    }

    void OnDataSent(unsigned int)
    {

    }

    void OnStart()
    {
        SendData(*factory.create<MOVEPackageGame>(15, 42, 8, 0));
    }

private:
    GamePackageFactory  factory;
};

int main()
{
    Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
    udpclient client(dispatcher);

    client.Connect("127.0.0.1", 4242);
    dispatcher.Watch(client, Network::Core::NativeSocketIOOperationDispatcher::READ);
    dispatcher.Run();
    return 0;
}