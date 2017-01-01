#ifndef WIN_PROCESS_HPP
# define WIN_PROCESS_HPP

#ifdef _WIN32

#include <windows.h>

typedef BOOL pid_t;

#include <Process/IProcess.hpp>

class WinProcess : public IProcess
{
public:
    WinProcess();
    virtual ~WinProcess();

public:
    virtual void Launch(std::string const &cmd);
    virtual bool IsChild() const;
    virtual void KillSon();
    virtual pid_t GetPid() const;
    virtual bool IsAlive() const;
    virtual int WaitSon() const;

private:
    PROCESS_INFORMATION ProcessInfo;
    STARTUPINFO StartupInfo;
    BOOL alive;
};

typedef WinProcess OSProcess;

#endif

#endif /* WIN_PROCESS_HPP */