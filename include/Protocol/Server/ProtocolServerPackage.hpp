//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_PROTOCOLSERVERPACKAGE_HPP
#define RTYPE_PROTOCOLSERVERPACKAGE_HPP

#include <string>
#include <cstring>

typedef struct HeaderServerInfo {
    unsigned char verLeft : 1;
    unsigned char verMiddle : 1;
    unsigned char verRight : 1;
    unsigned char reservedLeftOne : 1;
    unsigned char reservedLeftZero : 1;
    unsigned char reservedMiddleOne : 1;
    unsigned char reservedRightZero : 1;
    unsigned char reservedRightOne : 1;
} HeaderServerInfo;

typedef enum ServerPurpose : unsigned char{
    SERVERAUTHENTICATE = 1,
    SERVERLAUNCH = 2,
    SERVERSTATUS = 3
} ServerPurpose;

typedef enum ServerInformation : unsigned short {
    SERVERBUSY = 1,
    SERVERERRORSTOP = 2,
    SERVEROVER = 3
} ServerInformation;

class PackageServerHeader {
public:
    HeaderServerInfo headerServerInfo;
    unsigned short length;
    unsigned char purpose;

    PackageServerHeader(unsigned short length = 0,
                      unsigned char purpose = 0) {
        memset(this, 0, length);
        this->headerServerInfo.reservedLeftOne = 1;
        this->headerServerInfo.reservedLeftZero = 0;
        this->headerServerInfo.reservedMiddleOne = 1;
        this->headerServerInfo.reservedRightOne = 1;
        this->headerServerInfo.reservedRightZero = 0;
        this->headerServerInfo.verLeft = 0;
        this->headerServerInfo.verMiddle = 1;
        this->headerServerInfo.verRight = 0;
        this->length = length;
        this->purpose = purpose;
    }
};

class AUTHENTICATEPackageServer : public PackageServerHeader {
public:
    AUTHENTICATEPackageServer(unsigned int userID, unsigned short roomNumber)
            : PackageServerHeader(sizeof(AUTHENTICATEPackageServer), ServerPurpose::SERVERAUTHENTICATE) {
        this->userID = userID;
        this->roomNumber = roomNumber;
    }

public:
    unsigned int userID;
    unsigned short roomNumber;
};

class LAUNCHPackageServer : public PackageServerHeader {
public:
    LAUNCHPackageServer(unsigned short roomPlayer, unsigned short mapID, unsigned int secret,
                        unsigned int ip = 0, unsigned short port = 0)
            : PackageServerHeader(sizeof(LAUNCHPackageServer), ServerPurpose::SERVERLAUNCH) {
        this->roomPlayer = roomPlayer;
        this->mapID = mapID;
        this->secret = secret;
        this->ip = ip;
        this->port = port;
    }

public:
    unsigned short roomPlayer;
    unsigned short mapID;
    unsigned int secret;
    unsigned int ip;
    unsigned short port;
};

class STATUSPackageServer : public PackageServerHeader {
public:
    STATUSPackageServer(unsigned int secret, ServerInformation information)
            : PackageServerHeader(sizeof(STATUSPackageServer), ServerPurpose::SERVERSTATUS) {
        this->secret = secret;
        this->information = information;
    }

public:
    unsigned int secret;
    ServerInformation information;
};


#endif //RTYPE_PROTOCOLServerPACKAGE_HPP
