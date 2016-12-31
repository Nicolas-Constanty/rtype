//
// Created by victor on 06/12/16.
//

#ifndef RTYPE_UNIXPROCESS_HPP
#define RTYPE_UNIXPROCESS_HPP

#ifdef __linux__

#include "IProcess.hpp"

class UnixProcess : public IProcess {
public:
    virtual ~UnixProcess();
    UnixProcess();

public:
    virtual void Launch(std::string const &cmd);
    virtual bool IsChild() const;
    virtual void KillSon();
    virtual pid_t GetPid() const;
    virtual bool IsAlive() const;
    virtual int WaitSon() const;

private:
    pid_t pid;
    mutable bool alive;
};

typedef UnixProcess OSProcess;

#endif

#endif //RTYPE_UNIXPROCESS_HPP
