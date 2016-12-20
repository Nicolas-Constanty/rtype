//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_RTYPEPROTOCOLSERVERMANAGER_HPP
#define RTYPE_RTYPEPROTOCOLSERVERMANAGER_HPP

#include <map>
#include "Protocol/IRTypeProtocolManager.hpp"
#include "Protocol/Server/IProtocolServerHandler.hpp"

class RTypeProtocolServerManager : public IRTypeProtocolManager {

public:
    typedef struct ServerID {
        ServerPurpose     purposeID;
        unsigned short  size;

        ServerID(ServerPurpose ServerPurpose, unsigned short size) {
            this->purposeID = ServerPurpose;
            this->size = size;
        }

        bool operator==(ServerID const &ServerID) const {
            return (this->purposeID == ServerID.purposeID && this->size == ServerID.size);
        }

        ServerID &operator=(ServerID const &ServerID) {
            this->size = ServerID.size;
            this->purposeID = ServerID.purposeID;
            return (*this);
        }

        bool operator<(ServerID const &ServerID) const {
            return (this->purposeID < ServerID.purposeID);
        }
    } ServerID;

public:
    static const ServerID AUTHENTICATEID;
    static const ServerID LAUNCHID;
    static const ServerID STATUSID;

public:
    typedef void (IProtocolServerHandler::*MFP)(PackageServerHeader const &);

public:
    virtual ~RTypeProtocolServerManager();
    RTypeProtocolServerManager(IProtocolServerHandler &protocolServerHandler);

private:
    PackageServerHeader *getHeaderFrom(unsigned char *byte, size_t len);
    bool isPackageHeaderValid(PackageServerHeader *);

public:
    virtual bool handleProtocol(unsigned char *byte, size_t len);

private:
    IProtocolServerHandler    &protocolServerHandler;
    std::map<ServerID, MFP>                     fptr;
};

#endif //RTYPE_RTYPEPROTOCOLServerMANAGER_HPP
