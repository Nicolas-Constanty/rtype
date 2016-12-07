//
// Created by gaspar_q on 12/6/16.
//

#ifndef RTYPE_RTYPECLIENTGAMECLIENT_HPP
#define RTYPE_RTYPECLIENTGAMECLIENT_HPP

#include <Rtype/Game/Common/RtypeGameClient.hpp>

namespace Rtype
{
    namespace Game
    {
        namespace Client
        {
            class RtypeClientGameClient : public Rtype::Game::Common::RtypeGameClient
            {
            public:
                RtypeClientGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
                RtypeClientGameClient(RtypeClientGameClient const &ref);
                virtual ~RtypeClientGameClient();

            public:
                virtual bool OnStart();

            public:
                virtual void onGetSTATUSPackage(STATUSPackageGame const &pack);
                virtual void onGetPINGPackage(PINGPackageGame const &pack);
                virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &pack);
                virtual void onGetCREATEPackage(CREATEPackageGame const &pack);
                virtual void onGetBEAMPackage(BEAMPackageGame const &pack);
                virtual void onGetSHOTPackage(SHOTPackageGame const &pack);
                virtual void onGetDIEPackage(DIEPackageGame const &pack);
                virtual void onGetTAKEPackage(TAKEPackageGame const &pack);
                virtual void onGetDROPPackage(DROPPackageGame const &pack);
                virtual void onGetMOVEPackage(MOVEPackageGame const &pack);
                virtual void onGetLAUNCHPackage(LAUNCHPackageGame const &pack);
                virtual void onGetREBORNPackage(REBORNPackageGame const &pack);

            private:
                GamePackageFactory  factory;
            };
        }
    }
}

#endif //RTYPE_RTYPECLIENTGAMECLIENT_HPP