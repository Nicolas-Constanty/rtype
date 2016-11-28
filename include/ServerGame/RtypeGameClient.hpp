//
// Created by gaspar_q on 11/28/16.
//

#ifndef RTYPE_RTYPEGAMECLIENT_HPP
#define RTYPE_RTYPEGAMECLIENT_HPP

#include <Network/UDP/AUDPClient.hpp>
#include <Protocol/Game/RTypeProtocolGameManager.hpp>

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
    RTypeProtocolGameManager    manager;
};

#endif //RTYPE_RTYPEGAMECLIENT_HPP
