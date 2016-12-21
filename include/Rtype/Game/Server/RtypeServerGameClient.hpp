//
// Created by gaspar_q on 12/6/16.
//

#ifndef RTYPE_RTYPESERVERGAMECLIENT_HPP
#define RTYPE_RTYPESERVERGAMECLIENT_HPP

#include <Network/UDP/AUDPClient.hpp>
#include <Network/UDP/ReceptionStatus.hpp>
#include <Rtype/Game/Common/RtypeGameClient.hpp>
#include <Rtype/Game/Common/GameObjectContainer.hpp>
#include <cstdint>

namespace Rtype
{
    namespace Game
    {
        namespace Server
        {
            class RtypeGameServer;

            class RtypeServerGameClient : public Game::Common::RtypeGameClient
            {
            public:
                RtypeServerGameClient(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
                RtypeServerGameClient(RtypeServerGameClient const &ref);
                virtual ~RtypeServerGameClient();

            public:
                virtual bool OnStart();

            public:
                int getId() const;

            public:
                virtual void onGetSTATUSPackage(STATUSPackageGame const &);
                virtual void onGetPINGPackage(PINGPackageGame const &);
                virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &);
                virtual void onGetCREATEPackage(CREATEPackageGame const &);
                virtual void onGetBEAMPackage(BEAMPackageGame const &);
                virtual void onGetSHOTPackage(SHOTPackageGame const &);
                virtual void onGetDIEPackage(DIEPackageGame const &);
                virtual void onGetTAKEPackage(TAKEPackageGame const &);
                virtual void onGetCALLPackage(CALLPackageGame const &);
                virtual void onGetMOVEPackage(MOVEPackageGame const &);
                virtual void onGetLAUNCHPackage(LAUNCHPackageGame const &);
                virtual void onGetREBORNPackage(REBORNPackageGame const &);
                virtual void onGetFAILUREPackage(FAILUREPackageGame const &);
                virtual void onGetDISCONNECTPackage(DISCONNECTPackageGame const &);
                virtual void onGetENEMYSHOTPackage(ENEMYSHOTPackageGame const &);
                virtual void onGetUPGRADEPackage(UPGRADEPackageGame const &);
                virtual void onGetMATEPackage(MATEPackageGame const &);
                virtual void onGetGAMEOVERPackage(GAMEOVERPackageGame const &game);
                virtual void onGetDEATHPackage(DEATHPackage const &);

            public:
                void StartDisplayInformation();

            public:
                virtual void OnDisconnect();

            public:
                void ping();
                bool pong() const;

            private:
                Rtype::Game::Server::RtypeGameServer      *server1;

            private:
                int pingSecret;

            private:
                int id;
                double power;

            private:
                int __playerID;
            };
        }
    }
}

#endif //RTYPE_RTYPESERVERGAMECLIENT_HPP
