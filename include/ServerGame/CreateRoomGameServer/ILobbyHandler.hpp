//
// Created by victor on 06/12/16.
//

#ifndef RTYPE_ILOBBYHANDLER_HPP
#define RTYPE_ILOBBYHANDLER_HPP

class ILobbyHandler {
public:
    virtual ~ILobbyHandler() {}

public:
    virtual void OnProcessEnd(int status, void *data) = 0;
    virtual void OnProcessBegin(void *) = 0;

};

#endif //RTYPE_ILOBBYHANDLER_HPP
