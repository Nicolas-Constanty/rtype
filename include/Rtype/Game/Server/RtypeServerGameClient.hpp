//
// Created by gaspar_q on 12/6/16.
//

#ifndef RTYPE_RTYPESERVERGAMECLIENT_HPP
#define RTYPE_RTYPESERVERGAMECLIENT_HPP

#include <Network/UDP/AUDPClient.hpp>
#include <Network/UDP/ReceptionStatus.hpp>
#include <Rtype/Game/Common/RtypeGameClient.hpp>
#include <Rtype/Game/Common/GameObjectContainer.hpp>

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
                virtual void onGetDROPPackage(DROPPackageGame const &);
                virtual void onGetMOVEPackage(MOVEPackageGame const &);
                virtual void onGetLAUNCHPackage(LAUNCHPackageGame const &);
                virtual void onGetREBORNPackage(REBORNPackageGame const &);
                virtual void onGetFAILUREPackage(FAILUREPackageGame const &);
                virtual void onGetINPUTPackage(INPUTPackageGame const &);

            public:
                void StartDisplayInformation();

                //todo implémenter dès que la classe de script saltybehaviour est codée
                //public:
                //    void setScript(TYPE toset);
                //    TYPE getScript();

            public:
                bool timedout() const;
                void ping();
                bool pong() const;

            private:
                Rtype::Game::Server::RtypeGameServer      *server1;

            private:
                int pingSecret;
                std::chrono::time_point<std::chrono::steady_clock>  pingTime;

            private:
                int id;

            private:
                //ScriptRtypePLayerController *script;
            };
        }
    }
}

#endif //RTYPE_RTYPESERVERGAMECLIENT_HPP
