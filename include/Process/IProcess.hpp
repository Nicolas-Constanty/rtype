//
// Created by victor on 06/12/16.
//

#ifndef RTYPE_IPROCESS_HPP
#define RTYPE_IPROCESS_HPP

#include <string>

class IProcess {
public:
    virtual ~IProcess() {}

public:
    virtual void Launch(std::string const &cmd) = 0;
    virtual bool IsChild() const = 0;
    virtual void KillSon() = 0;
    virtual pid_t GetPid() const = 0;
    virtual bool IsAlive() const = 0;
    virtual int WaitSon() const = 0;
};

#endif //RTYPE_IPROCESS_HPP
