//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_PROTOCOLGAMEPACKAGE_HPP
#define RTYPE_PROTOCOLGAMEPACKAGE_HPP

#include <cstring>
#include "Common/DLLexport.hpp"

typedef struct HeaderGameInfo {
    unsigned char verLeft : 1;
    unsigned char verRight : 1;
    unsigned char reservedLeftOne : 1;
    unsigned char reservedLeftZero : 1;
    unsigned char reservedMiddleOne : 1;
    unsigned char reservedRightZero : 1;
    unsigned char reservedRightOne : 1;
    unsigned char reliable : 1;
} HeaderGameInfo;

typedef enum : unsigned char {
    GAMEMOVE = 1,
    GAMESHOT = 2,
    GAMETAKE = 3,
    GAMEBEAM = 4,
    GAMECALL = 5,
    GAMEDIE = 6,
    GAMECREATE = 7,
    GAMELAUNCH = 8,
    GAMESTATUS = 9,
    GAMEAUTHENTICATE = 10,
    GAMEPING = 11,
    GAMEREBORN = 12,
    GAMEFAILURE = 13,
    GAMEDISCONNECT = 14,
    GAMEENEMYSHOT = 15,
    GAMEUPGRADE = 16,
    GAMEMATE = 17,
    GAMEGAMEOVER = 18,
    GAMEDEATH = 19,
    GAMERECONNECT = 20
} GamePurpose;

class  PackageGameHeader {
public:
    HeaderGameInfo headerGameInfo;
    unsigned short length;
    unsigned short sequenceID;
    unsigned char purpose;
    unsigned short transactionID;

    PackageGameHeader(bool reliable = true,
                      unsigned short length = 0,
                      unsigned short sequenceID = 0,
                      unsigned char purpose = 0,
                      unsigned short transactionID = 0) {
        memset(this, 0, length);
        this->headerGameInfo.reliable = (unsigned char)(reliable ? 1 : 0);
        this->headerGameInfo.reservedLeftOne = 1;
        this->headerGameInfo.reservedLeftZero = 0;
        this->headerGameInfo.reservedMiddleOne = 1;
        this->headerGameInfo.reservedRightOne = 1;
        this->headerGameInfo.reservedRightZero = 0;
        this->headerGameInfo.verLeft = 0;
        this->headerGameInfo.verRight = 1;
        this->length = length;
        this->sequenceID = sequenceID;
        this->purpose = purpose;
        this->transactionID = transactionID;
    }
};

class  PINGPackageGame : public PackageGameHeader {
public:
    PINGPackageGame(unsigned short sequenceID = 0, int secret = 0, unsigned short transactionID = 0)
            : PackageGameHeader(true, sizeof(PINGPackageGame), sequenceID, GamePurpose::GAMEPING, transactionID) {
        this->secret = secret;
    }

public:
    int secret;
};

class  AUTHENTICATEPackageGame : public PackageGameHeader {
public:
    AUTHENTICATEPackageGame(unsigned short sequenceID = 0, unsigned int secret = 0, unsigned char playerId = 0, unsigned short transactionID = 0)
            : PackageGameHeader(true, sizeof(AUTHENTICATEPackageGame), sequenceID, GamePurpose::GAMEAUTHENTICATE, transactionID) {
        this->secret = secret;
        this->playerId = playerId;
    }

public:
    unsigned int secret;
    unsigned char playerId;
};

class  DISCONNECTPackageGame : public PackageGameHeader
{
public:
    DISCONNECTPackageGame(unsigned short sequenceID = 0, unsigned char playerID = 0, unsigned int errcode = 0, unsigned short transactionID = 0) :
            PackageGameHeader(true, sizeof(DISCONNECTPackageGame), sequenceID, GamePurpose::GAMEDISCONNECT, transactionID)
    {
        this->errcode = errcode;
        this->playerID = playerID;
    }

public:
    unsigned int errcode;
    unsigned char playerID;
};

class  ObjectIDPackageGame : public PackageGameHeader {
public:
    ObjectIDPackageGame(unsigned short size = 0, unsigned char purpose = 0, unsigned short sequenceID = 0,
                        unsigned short objectID = 0, bool reliable = 0, unsigned short transactionID = 0)
            : PackageGameHeader(reliable, size, sequenceID, purpose, transactionID) {
        this->objectID = objectID;
    }

public:
    unsigned short objectID;
};

class  CREATEPackageGame : public ObjectIDPackageGame {
public:
    CREATEPackageGame(unsigned short sequenceID = 0, int posX = 0, int posY = 0, unsigned short ID = 0,
                      unsigned short objectID = 0, float rotation = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(CREATEPackageGame), GamePurpose::GAMECREATE, sequenceID, objectID, true, transactionID) {
        this->posX = posX;
        this->posY = posY;
        this->ID = ID;
        this->rotation = rotation;
    }

public:
    int posX;
    int posY;
    unsigned short ID;
    float rotation;
};

class  STATUSPackageGame : public PackageGameHeader {
public:
    STATUSPackageGame(unsigned short sequenceID = 0, int highScore = 0, unsigned char playerID = 0, unsigned short transactionID = 0)
            : PackageGameHeader(true, sizeof(STATUSPackageGame), sequenceID, GamePurpose::GAMESTATUS, transactionID) {
        this->highScore = highScore;
        this->playerID = playerID;
    }

public:
    int highScore;
    unsigned char playerID;
};

class  MOVEPackageGame : public ObjectIDPackageGame {
public:
    MOVEPackageGame(unsigned short sequenceID = 0, int posX = 0, int posY = 0, unsigned short objectID = 0,
                    unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(MOVEPackageGame), GamePurpose::GAMEMOVE, sequenceID, objectID, false, transactionID) {
        this->posX = posX;
        this->posY = posY;
    }

public:
    int posX;
    int posY;
};

class  BEAMPackageGame : public ObjectIDPackageGame {
public:
    BEAMPackageGame(unsigned short sequenceID = 0, unsigned short objectID = 0, unsigned int id = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(BEAMPackageGame), GamePurpose::GAMEBEAM, sequenceID, objectID, true, transactionID) {
        this->id = id;
    }

public:
    unsigned int id;
};

class  SHOTPackageGame : public ObjectIDPackageGame {
public:
    SHOTPackageGame(unsigned short sequenceID = 0, unsigned short objectID = 0, int power = 0, unsigned int id = 0, int x = 0, int y = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(SHOTPackageGame), GamePurpose::GAMESHOT, sequenceID, objectID, true, transactionID) {
        this->power = power;
        this->id = id;
        this->x = x;
        this->y = y;
    }

public:
    int power;
    unsigned int id;
    int x;
    int y;
};

class  ENEMYSHOTPackageGame : public ObjectIDPackageGame {
public:
    ENEMYSHOTPackageGame(unsigned short sequenceID = 0, unsigned short objectID = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(ENEMYSHOTPackageGame), GamePurpose::GAMEENEMYSHOT, sequenceID, objectID, true, transactionID) {
    }
};


class  DIEPackageGame : public ObjectIDPackageGame {
public:
    DIEPackageGame(unsigned short sequenceID = 0, unsigned short objectID = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(DIEPackageGame), GamePurpose::GAMEDIE, sequenceID, objectID, true, transactionID) {
    }
};

class  TAKEPackageGame : public ObjectIDPackageGame {
public:
    TAKEPackageGame(unsigned short sequenceID = 0, unsigned short podID = 0, unsigned short playerObjectID = 0, unsigned char front = 0, unsigned short transactionID = 0) :
            ObjectIDPackageGame(sizeof(TAKEPackageGame), GamePurpose::GAMETAKE, sequenceID, podID, true, transactionID),
            playerObjectID(playerObjectID),
            front(front)
    {

    }

public:
    unsigned short playerObjectID;
    unsigned char   front;
};

class  CALLPackageGame : public ObjectIDPackageGame {
public:
    CALLPackageGame(unsigned short sequenceID = 0, unsigned short podID = 0, unsigned short playerObjectID = 0, unsigned short transactionID = 0) :
            ObjectIDPackageGame(sizeof(CALLPackageGame), GamePurpose::GAMECALL, sequenceID, podID, true, transactionID),
            playerObjectID(playerObjectID)
    {

    }

public:
    unsigned short playerObjectID;
};

class  LAUNCHPackageGame : public ObjectIDPackageGame {
public:
    LAUNCHPackageGame(unsigned short sequenceID = 0, unsigned short podID = 0, unsigned short playerObjectID = 0, int posX = 0, int posY = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(LAUNCHPackageGame), GamePurpose::GAMELAUNCH, sequenceID, podID, true, transactionID),
              playerObjectID(playerObjectID),
              fromX(posX),
              fromY(posY)
    {

    }

public:
    unsigned short playerObjectID;
    int fromX;
    int fromY;
};

class  REBORNPackageGame : public ObjectIDPackageGame {
public:
    REBORNPackageGame(unsigned short sequenceID = 0, unsigned short objectID = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(REBORNPackageGame), GamePurpose::GAMEREBORN, sequenceID, objectID, true, transactionID) {
    }
};

class  DEATHPackage : public ObjectIDPackageGame
{
public:
    DEATHPackage(unsigned short sequenceID = 0, unsigned short playerObjectID = 0, unsigned short transactionID = 0) :
            ObjectIDPackageGame(sizeof(DEATHPackage), GAMEDEATH, sequenceID, playerObjectID, true, transactionID)
    {

    }
};

class  FAILUREPackageGame : public PackageGameHeader {
public:
    FAILUREPackageGame(unsigned short sequenceID = 0, unsigned char failPurpose = 0, unsigned short failseq = 0, unsigned short transactionID = 0) :
            PackageGameHeader(true, sizeof(FAILUREPackageGame), sequenceID, GAMEFAILURE, transactionID),
            failPurpose(failPurpose),
            failSequence(failseq)
    {

    }

    unsigned char failPurpose;
    unsigned short failSequence;
};

class  UPGRADEPackageGame : public ObjectIDPackageGame
{
public:
    UPGRADEPackageGame(unsigned short sequenceID = 0, unsigned short podID = 0, unsigned short rocket = 0, unsigned short transactionID = 0) :
            ObjectIDPackageGame(sizeof(UPGRADEPackageGame), GamePurpose::GAMEUPGRADE, sequenceID, podID, true, transactionID),
            rocket(rocket)
    {

    }

public:
    unsigned short rocket;
};

class  MATEPackageGame : public ObjectIDPackageGame
{
public:
    MATEPackageGame(unsigned short sequenceID = 0, int x = 0, int y = 0, int playerID = 0, unsigned short objectID = 0, unsigned short transactionID = 0) :
            ObjectIDPackageGame(sizeof(MATEPackageGame), GamePurpose::GAMEMATE, sequenceID, objectID, true, transactionID)
    {
        this->x = x;
        this->y = y;
        this->playerID = playerID;
    }

public:
    int x;
    int y;
    int playerID;
};

class  GAMEOVERPackageGame : public PackageGameHeader
{
public:
    GAMEOVERPackageGame(unsigned short sequenceID = 0, unsigned char status = 0, unsigned short transactionID = 0) :
            PackageGameHeader(true, sizeof(GAMEOVERPackageGame), sequenceID, GamePurpose::GAMEGAMEOVER, transactionID)
    {
            this->status = status;
    }

public:
    unsigned char status;
};

class  RECONNECTPackageGame : public PackageGameHeader
{
public:
    RECONNECTPackageGame(unsigned short sequenceID = 0, unsigned char playerID = 0, unsigned short transactionID = 0) :
            PackageGameHeader(true, sizeof(RECONNECTPackageGame), sequenceID, GamePurpose::GAMERECONNECT, transactionID)
    {
        this->playerID = playerID;
    }

public:
    unsigned char playerID;
};

#endif //RTYPE_PROTOCOLGAMEPACKAGE_HPP
