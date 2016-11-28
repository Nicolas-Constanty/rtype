//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_RTYPEPROTOCOLGAMEMANAGER_HPP
#define RTYPE_RTYPEPROTOCOLGAMEMANAGER_HPP

#include <map>
#include "Protocol/IRTypeProtocolManager.hpp"
#include "Protocol/Game/IProtocolGameHandler.hpp"

class RTypeProtocolGameManager : public IRTypeProtocolManager {

public:
    typedef struct GameID {
        GamePurpose     purposeID;
        unsigned short  size;

        GameID(GamePurpose gamePurpose, unsigned short size) {
            this->purposeID = gamePurpose;
            this->size = size;
        }

        bool operator==(GameID const &gameID) const {
            return (this->purposeID == gameID.purposeID && this->size == gameID.size);
        }

        GameID &operator=(GameID const &gameID) {
            this->size = gameID.size;
            this->purposeID = gameID.purposeID;
            return *this;
        }

        bool operator<(GameID const &gameID) const {
            return (this->purposeID < gameID.purposeID);
        }
    } GameID;

public:
    static const GameID MOVEID;// = GameID(MOVE, sizeof(MOVEPackageGame));
    static const GameID TAKEID;// = GameID(GAMETAKE, sizeof(TAKEPackageGame));
    static const GameID BEAMID;// = GameID(GAMEBEAM, sizeof(BEAMPackageGame));
    static const GameID DROPID;// = GameID(DROP, sizeof(DROPPackageGame));
    static const GameID DIEID;// = GameID(DIE, sizeof(DIEPackageGame));
    static const GameID CREATEID;// = GameID(CREATE, sizeof(CREATEPackageGame));
    static const GameID LAUNCHID;// = GameID(LAUNCH, sizeof(LAUNCHPackageGame));
    static const GameID STATUSID;// = GameID(STATUS, sizeof(STATUSPackageGame));
    static const GameID AUTHENTICATEID;// = GameID(AUTHENTICATE, sizeof(AUTHENTICATEPackageGame));
    static const GameID PINGID;// = GameID(PING, sizeof(PINGPackageGame));
    static const GameID SHOTID;// = GameID(SHOT, sizeof(SHOTPackageGame));

public:
    typedef void (IProtocolGameHandler::*MFP)(PackageGameHeader const &);

public:
    virtual ~RTypeProtocolGameManager();
    RTypeProtocolGameManager(IProtocolGameHandler &protocolGameHandler);

private:
    PackageGameHeader *getHeaderFrom(unsigned char *byte, size_t len);
    bool isPackageHeaderValid(PackageGameHeader *);

public:
    virtual bool handleProtocol(unsigned char *byte, size_t len);

private:
    IProtocolGameHandler    &protocolGameHandler;
    std::map<GameID, MFP>                     fptr;
};

#endif //RTYPE_RTYPEPROTOCOLGAMEMANAGER_HPP
