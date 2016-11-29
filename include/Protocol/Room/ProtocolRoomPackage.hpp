//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_PROTOCOLROOMPACKAGE_HPP
#define RTYPE_PROTOCOLROOMPACKAGE_HPP

#include <string>
#include <cstring>

typedef struct HeaderRoomInfo {
    unsigned char verLeft : 1;
    unsigned char verMiddle : 1;
    unsigned char verRight : 1;
    unsigned char reservedLeftOne : 1;
    unsigned char reservedLeftZero : 1;
    unsigned char reservedMiddleOne : 1;
    unsigned char reservedRightZero : 1;
    unsigned char reservedRightOne : 1;
} HeaderRoomInfo;

typedef enum RoomPurpose : unsigned char{
    ROOMCREATE = 1,
    ROOMJOIN = 2,
    ROOMQUIT = 3,
    ROOMAUTHENTICATE = 4,
    ROOMPLUGGED = 5,
    ROOMSWAP = 6,
    ROOMGET = 7,
    ROOMFAILURE = 8,
    ROOMLAUNCH = 9
} RoomPurpose;

class PackageRoomHeader {
public:
    HeaderRoomInfo headerRoomInfo;
    unsigned short length;
    unsigned char purpose;

    PackageRoomHeader(unsigned short length = 0,
                      unsigned char purpose = 0) {
        memset(this, 0, length);
        this->headerRoomInfo.reservedLeftOne = 1;
        this->headerRoomInfo.reservedLeftZero = 0;
        this->headerRoomInfo.reservedMiddleOne = 1;
        this->headerRoomInfo.reservedRightOne = 1;
        this->headerRoomInfo.reservedRightZero = 0;
        this->headerRoomInfo.verLeft = 0;
        this->headerRoomInfo.verMiddle = 0;
        this->headerRoomInfo.verRight = 1;
        this->length = length;
        this->purpose = purpose;
    }
};

class CREATEPackageRoom : public PackageRoomHeader {
public:
    CREATEPackageRoom(unsigned short roomPlayer, unsigned short roomPlayerMax,
                      std::string const &name, unsigned short roomID,
                      unsigned short mapID)
            : PackageRoomHeader(sizeof(CREATEPackageRoom), RoomPurpose::ROOMCREATE) {
        this->roomPlayer = roomPlayer;
        this->roomPlayerMax = roomPlayerMax;
        memset(this->name, 0, sizeof(this->name));
        if (name.length() < sizeof(name)) {
            strncpy(this->name, name.c_str(), name.length());
        }
        this->roomID = roomID;
        this->mapID = mapID;
    }

public:
    unsigned short roomPlayer;
    unsigned short roomPlayerMax;
    char name[8];
    unsigned short roomID;
    unsigned short mapID;
};

class JOINPackageRoom : public PackageRoomHeader {
public:
    JOINPackageRoom(unsigned short roomID)
            : PackageRoomHeader(sizeof(JOINPackageRoom), RoomPurpose::ROOMJOIN) {
        this->roomID = roomID;
    }

public:
    unsigned short roomID;
};

class QUITPackageRoom : public PackageRoomHeader {
public:
    QUITPackageRoom(unsigned int userID, unsigned short roomID)
            : PackageRoomHeader(sizeof(QUITPackageRoom), RoomPurpose::ROOMQUIT) {
        this->roomID = roomID;
        this->userID = userID;
    }

public:
    unsigned int userID;
    unsigned short roomID;
};

class AUTHENTICATEPackageRoom : public PackageRoomHeader {
public:
    AUTHENTICATEPackageRoom(std::string const &pseudo, unsigned int userID)
            : PackageRoomHeader(sizeof(AUTHENTICATEPackageRoom), RoomPurpose::ROOMAUTHENTICATE) {
        memset(this->name, 0, sizeof(this->name));
        if (pseudo.length() < sizeof(name)) {
            strncpy(this->name, pseudo.c_str(), pseudo.length());
        }
        this->userID = userID;
    }

public:
    char name[8];
    unsigned int userID;
};

class PLUGGEDPackageRoom : public PackageRoomHeader {
public:
    PLUGGEDPackageRoom(std::string const &pseudo, unsigned int userID, unsigned short roomID)
            : PackageRoomHeader(sizeof(PLUGGEDPackageRoom), RoomPurpose::ROOMPLUGGED) {
        memset(this->name, 0, sizeof(this->name));
        if (pseudo.length() < sizeof(name)) {
            strncpy(this->name, pseudo.c_str(), pseudo.length());
        }
        this->userID = userID;
        this->roomID = roomID;
    }

public:
    char name[8];
    unsigned int userID;
    unsigned short roomID;
};

class SWAPPackageRoom : public PackageRoomHeader {
public:
    SWAPPackageRoom(unsigned int addrIP, unsigned int port, unsigned int secret)
            : PackageRoomHeader(sizeof(SWAPPackageRoom), RoomPurpose::ROOMSWAP) {
        this->addrIP = addrIP;
        this->port = port;
        this->secret = secret;
    }

public:
    unsigned int addrIP;
    unsigned int port;
    unsigned int secret;
};

class GETPackageRoom : public PackageRoomHeader {
public:
    GETPackageRoom(unsigned short roomPlayer, unsigned short roomPlayerMax,
                   std::string const &pseudo, unsigned short roomID, unsigned short mapID)
            : PackageRoomHeader(sizeof(GETPackageRoom), RoomPurpose::ROOMGET) {
        memset(this->name, 0, sizeof(this->name));
        if (pseudo.length() < sizeof(name)) {
            strncpy(this->name, pseudo.c_str(), pseudo.length());
        }
        this->roomPlayer = roomPlayer;
        this->roomPlayerMax = roomPlayerMax;
        this->roomID = roomID;
        this->mapID = mapID;
    }

public:
    unsigned short roomPlayer;
    unsigned short roomPlayerMax;
    char name[8];
    unsigned short roomID;
    unsigned short mapID;
};

class FAILUREPackageRoom : public PackageRoomHeader {
public:
    FAILUREPackageRoom(std::string const &msg, unsigned char purposeFailed)
            : PackageRoomHeader(sizeof(FAILUREPackageRoom), RoomPurpose::ROOMFAILURE) {
        memset(this->msg, 0, sizeof(this->msg));
        if (msg.length() < sizeof(msg)) {
            strncpy(this->msg, msg.c_str(), msg.length());
        }
        this->purposeFailed = purposeFailed;
    }

public:
    char msg[8];
    unsigned char purposeFailed;
};

class LAUNCHPackageRoom : public PackageRoomHeader {

public:
    LAUNCHPackageRoom(unsigned short roomID)
            : PackageRoomHeader(sizeof(LAUNCHPackageRoom), RoomPurpose::ROOMLAUNCH) {
        this->roomID = roomID;
    }

public:
    unsigned short roomID;
};

#endif //RTYPE_PROTOCOLROOMPACKAGE_HPP
