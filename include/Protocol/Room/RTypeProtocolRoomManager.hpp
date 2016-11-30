//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_RTYPEPROTOCOLROOMMANAGER_HPP
#define RTYPE_RTYPEPROTOCOLROOMMANAGER_HPP

#include <map>
#include "Protocol/IRTypeProtocolManager.hpp"
#include "Protocol/Room/IProtocolRoomHandler.hpp"

class RTypeProtocolRoomManager : public IRTypeProtocolManager {

public:
    typedef struct RoomID {
        RoomPurpose     purposeID;
        unsigned short  size;

        RoomID(RoomPurpose RoomPurpose, unsigned short size) {
            this->purposeID = RoomPurpose;
            this->size = size;
        }

        bool operator==(RoomID const &RoomID) const {
            return (this->purposeID == RoomID.purposeID && this->size == RoomID.size);
        }

        bool operator=(RoomID const &RoomID) {
            this->size = RoomID.size;
            this->purposeID = RoomID.purposeID;
        }

        bool operator<(RoomID const &RoomID) const {
            return (this->purposeID < RoomID.purposeID);
        }
    } RoomID;

public:
    static const RoomID AUTHENTICATEID;
    static const RoomID CREATEID;
    static const RoomID FAILUREID;
    static const RoomID GETID;
    static const RoomID JOINID;
    static const RoomID PLUGGEDID;
    static const RoomID SWAPID;
    static const RoomID QUITID;
    static const RoomID LAUNCHID;

public:
    typedef void (IProtocolRoomHandler::*MFP)(PackageRoomHeader const &);

public:
    virtual ~RTypeProtocolRoomManager();
    RTypeProtocolRoomManager(IProtocolRoomHandler &protocolRoomHandler);

private:
    PackageRoomHeader *getHeaderFrom(unsigned char *byte, size_t len);
    bool isPackageHeaderValid(PackageRoomHeader *);

public:
    virtual bool handleProtocol(unsigned char *byte, size_t len);

private:
    IProtocolRoomHandler    &protocolRoomHandler;
    std::map<RoomID, MFP>                     fptr;
};

#endif //RTYPE_RTYPEPROTOCOLROOMMANAGER_HPP
