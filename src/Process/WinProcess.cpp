#include <iostream>
#include "Process/WinProcess.hpp"

#if _WIN32

WinProcess::WinProcess() :
    ProcessInfo(),
    StartupInfo(),
    alive(0)
{

}

WinProcess::~WinProcess()
{

}

void WinProcess::Launch(std::string const &cmd)
{
    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    StartupInfo.cb = sizeof StartupInfo ;

    alive = CreateProcess(NULL, const_cast<char *>(cmd.c_str()),
                          NULL,NULL,FALSE,0,NULL,
                          NULL,&StartupInfo,&ProcessInfo);

    if (!IsAlive())
    {
        std::cerr << "CreateProcess failed " << GetLastError() << std::endl;
    }
}

bool WinProcess::IsChild() const
{
    return false;
}

void WinProcess::KillSon()
{
    if (IsAlive())
    {
        alive = TerminateProcess(ProcessInfo.hProcess, 1);
    }
}

pid_t WinProcess::GetPid() const
{
    return alive;
}

bool WinProcess::IsAlive() const
{
    return alive > 0;
}

int WinProcess::WaitSon() const
{
    if (!IsAlive())
        return 0;

    DWORD status = WaitForSingleObject(ProcessInfo.hProcess, INFINITE);

    CloseHandle(ProcessInfo.hThread);
    CloseHandle(ProcessInfo.hProcess);
    return static_cast<int>(status);
}

#endif