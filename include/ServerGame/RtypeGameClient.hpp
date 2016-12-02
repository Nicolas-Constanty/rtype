//
// Created by gaspar_q on 11/28/16.
//

#ifndef RTYPE_RTYPEGAMECLIENT_HPP
#define RTYPE_RTYPEGAMECLIENT_HPP

#include <Network/UDP/AUDPClient.hpp>
#include <Protocol/Game/RTypeProtocolGameManager.hpp>
#include <Protocol/Game/GamePackageFactory.hpp>
#include <Network/UDP/ReceptionStatus.hpp>

class RtypeGameClient : public Network::UDP::AUDPClient, public IProtocolGameHandler
{
public:
    RtypeGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
    RtypeGameClient(RtypeGameClient const &ref);
    virtual ~RtypeGameClient();

public:
    virtual void OnDataReceived(unsigned int len);
    virtual void OnDataSent(unsigned int len);

public:
    virtual void OnStart();

public:
    const int getId() const;

public:
    virtual void onGetSTATUSPackage(STATUSPackageGame const &);
    virtual void onGetPINGPackage(PINGPackageGame const &);
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &);
    virtual void onGetCREATEPackage(CREATEPackageGame const &);
    virtual void onGetBEAMPackage(BEAMPackageGame const &);
    virtual void onGetSHOTPackage(SHOTPackageGame const &);
    virtual void onGetDIEPackage(DIEPackageGame const &);
    virtual void onGetTAKEPackage(TAKEPackageGame const &);
    virtual void onGetDROPPackage(DROPPackageGame const &);
    virtual void onGetMOVEPackage(MOVEPackageGame const &);
    virtual void onGetLAUNCHPackage(LAUNCHPackageGame const &);

private:
    template <typename Pack>
    void OnDiscoveringPackage(Pack const &pack)
    {
        if (reply)
        {
            SendData(pack);
            serverStream->WantSend();
        }
        buff += sizeof(Pack);
    }

    //todo implémenter dès que la classe de script saltybehaviour est codée
//public:
//    void setScript(TYPE toset);
//    TYPE getScript();

private:
    RTypeProtocolGameManager    manager;
    //ScriptRtypePLayerController *script;
//    GamePackageFactory  gamePackageFactory;
    Network::UDP::ReceptionStatus<uint16_t, uint32_t>   status;
    int id;
    bool reply;
};

#endif //RTYPE_RTYPEGAMECLIENT_HPP
