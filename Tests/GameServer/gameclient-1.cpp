//
// Created by gaspar_q on 12/1/16.
//

#include <ServerGame/RtypeGameClient.hpp>
#include <SaltyEngine/SaltyEngine.hpp>

class udpclient : public Rtype::RtypeGameClient
{
public:
    udpclient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Rtype::RtypeGameClient(dispatcher),
            factory()
    {

    }

    ~udpclient()
    {

    }

public:
    bool OnStart()
    {
//        SendReliable(*factory.create<PINGPackageGame>(32, 0));
        SendReliable(*factory.create<AUTHENTICATEPackageGame>(42));
        connected = true;
        return true;
    }

public:
    virtual void onGetSTATUSPackage(STATUSPackageGame const &pack)
    {
        OnDiscoveringPackage(pack);

    }

    virtual void onGetPINGPackage(PINGPackageGame const &pack)
    {
        reply = false;
        OnDiscoveringPackage(pack);
        SendReliable(*factory.create<PINGPackageGame>(pack.secret));
    }

    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &pack)
    {
        std::cout << "\e[32mAuthenticated\e[0m" << std::endl;
        OnDiscoveringPackage(pack);
        //todo define in engine which player is controlled by user through gameobject id <pack.playerId>
    }

    virtual void onGetCREATEPackage(CREATEPackageGame const &pack)
    {
        OnDiscoveringPackage(pack);

    }

    virtual void onGetBEAMPackage(BEAMPackageGame const &pack)
    {
        OnDiscoveringPackage(pack);

    }

    virtual void onGetSHOTPackage(SHOTPackageGame const &pack)
    {
        OnDiscoveringPackage(pack);

    }

    virtual void onGetDIEPackage(DIEPackageGame const &pack)
    {
        OnDiscoveringPackage(pack);

    }

    virtual void onGetTAKEPackage(TAKEPackageGame const &pack)
    {
        OnDiscoveringPackage(pack);

    }

    virtual void onGetDROPPackage(DROPPackageGame const &pack)
    {
        OnDiscoveringPackage(pack);

    }

    virtual void onGetMOVEPackage(MOVEPackageGame const &pack)
    {
        OnDiscoveringPackage(pack);

    }

    virtual void onGetLAUNCHPackage(LAUNCHPackageGame const &pack)
    {
        OnDiscoveringPackage(pack);
    }

    virtual void onGetREBORNPackage(REBORNPackageGame const &pack)
    {
        OnDiscoveringPackage(pack);
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