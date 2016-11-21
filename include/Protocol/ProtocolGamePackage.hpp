//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_PROTOCOLGAMEPACKAGE_HPP
#define RTYPE_PROTOCOLGAMEPACKAGE_HPP

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
    MOVE = 1,
    SHOT = 2,
    TAKE = 3,
    BEAM = 4,
    DROP = 5,
    DIE = 6,
    CREATE = 7,
    LAUNCH = 8,
    STATUS = 9,
    AUTHENTICATE = 10,
    PING = 11
} GamePurpose;

class PackageGameHeader {
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

class PINGPackageGame : public PackageGameHeader {
public:
    PINGPackageGame(int secret = 0, unsigned short sequenceID = 0, unsigned short transactionID = 0)
            : PackageGameHeader(true, sizeof(PINGPackageGame), sequenceID, PING, transactionID) {
        this->secret = secret;
    }

public:
    int secret;
};

class AUTHENTICATEPackageGame : public PackageGameHeader {
public:
    AUTHENTICATEPackageGame(int secret = 0, unsigned short sequenceID = 0, unsigned short transactionID = 0)
            : PackageGameHeader(true, sizeof(AUTHENTICATEPackageGame), sequenceID, AUTHENTICATE, transactionID) {
        this->secret = secret;
    }

public:
    int secret;
};

class ObjectIDPackageGame : public PackageGameHeader {
public:
    ObjectIDPackageGame(unsigned short size = 0, unsigned char purpose = 0, unsigned short sequenceID = 0,
                        unsigned short objectID = 0, bool reliable = 0, unsigned short transactionID = 0)
            : PackageGameHeader(reliable, size, sequenceID, purpose, transactionID) {
        this->objectID = objectID;
    }

public:
    unsigned short objectID;
};

class CREATEPackageGame : public ObjectIDPackageGame {
public:
    CREATEPackageGame(int posX = 0, int posY = 0, unsigned short ID = 0, unsigned short sequenceID = 0, unsigned short objectID = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(CREATEPackageGame), CREATE, sequenceID, objectID, true, transactionID) {
        this->posX = posX;
        this->posY = posY;
        this->ID = ID;
    }

public:
    int posX;
    int posY;
    unsigned short ID;
};

class STATUSPackageGame : public ObjectIDPackageGame {
public:
    STATUSPackageGame(int highScore, bool running, unsigned short sequenceID, unsigned short objectID, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(STATUSPackageGame), STATUS, sequenceID, objectID, false, transactionID) {
        this->highScore = highScore;
        this->run = (unsigned char)running;
        if (this->run == 1) {
            this->headerGameInfo.reliable = 1;
        } else {
            this->headerGameInfo.reliable = 0;
        }
    }

public:
    int highScore;
    unsigned char run : 2;
};

class MOVEPackageGame : public ObjectIDPackageGame {
public:
    MOVEPackageGame(int posX = 0, int posY = 0, unsigned short sequenceID = 0, unsigned short objectID = 0,
                    unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(MOVEPackageGame), MOVE, sequenceID, objectID, false, transactionID) {
        this->posX = posX;
        this->posY = posY;
    }

public:
    int posX;
    int posY;
};

class BEAMPackageGame : public ObjectIDPackageGame {
public:
    BEAMPackageGame(unsigned short sequenceID = 0, unsigned short objectID = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(BEAMPackageGame), BEAM, sequenceID, objectID, true, transactionID) {
    }
};

class SHOTPackageGame : public ObjectIDPackageGame {
public:
    SHOTPackageGame(unsigned short sequenceID = 0, unsigned short objectID = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(SHOTPackageGame), SHOT, sequenceID, objectID, true, transactionID) {
    }
};

class DIEPackageGame : public ObjectIDPackageGame {
public:
    DIEPackageGame(int posX = 0, int posY = 0, unsigned short ID = 0, unsigned short sequenceID = 0, unsigned short objectID = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(DIEPackageGame), DIE, sequenceID, objectID, true, transactionID) {
    }
};

class TAKEPackageGame : public ObjectIDPackageGame {
public:
    TAKEPackageGame(unsigned short sequenceID = 0, unsigned short objectID = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(TAKEPackageGame), TAKE, sequenceID, objectID, true, transactionID) {
    }
};

class DROPPackageGame : public ObjectIDPackageGame {
public:
    DROPPackageGame(unsigned short sequenceID = 0, unsigned short objectID = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(DROPPackageGame), DROP, sequenceID, objectID, true, transactionID) {
    }
};

class LAUNCHPackageGame : public ObjectIDPackageGame {
public:
    LAUNCHPackageGame(unsigned short sequenceID = 0, unsigned short objectID = 0, unsigned short transactionID = 0)
            : ObjectIDPackageGame(sizeof(LAUNCHPackageGame), LAUNCH, sequenceID, objectID, true, transactionID) {
    }
};

#endif //RTYPE_PROTOCOLGAMEPACKAGE_HPP
