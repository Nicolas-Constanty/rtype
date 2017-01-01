//
// Created by gaspar_q on 11/11/16.
//

#ifndef SPIDER_SERVER_INATIVESOCKET_HPP
#define SPIDER_SERVER_INATIVESOCKET_HPP

# ifdef __linux__
typedef int SOCKET;
# elif _WIN32
typedef short sa_family_t;
# endif

extern  "C"
{
 #ifdef __linux__
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <sys/select.h>
#  include <netdb.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
 #elif _WIN32
#  include <winsock2.h>
#  include <ws2tcpip.h>
  #endif
};

#include "Common/DLLexport.hpp"

class PREF_EXPORT INativeSocketContainer
{
public:
    virtual ~INativeSocketContainer(){}

public:
    virtual SOCKET Native() const = 0;
};

#endif //SPIDER_SERVER_INATIVESOCKET_HPP
