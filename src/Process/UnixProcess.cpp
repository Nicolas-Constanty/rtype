//
// Created by victor on 06/12/16.
//

#include <stdexcept>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <wait.h>
#include "Process/UnixProcess.hpp"

UnixProcess::UnixProcess() {
    alive = false;
    pid = -1;
}

UnixProcess::~UnixProcess() {
    if (IsAlive())
        KillSon();
}

void UnixProcess::Launch(std::string const &cmd) {
    std::string output;

    if ((pid = fork()) == -1)
        throw std::runtime_error("fork has failed !");
    if (pid == 0)
    {
        std::system(cmd.c_str());
        exit(0);
    }
    alive = true;
}

bool UnixProcess::IsChild() const {
    return pid == 0;
}

void UnixProcess::KillSon() {
    if (pid != -1 && !IsChild())
        kill(pid, SIGKILL);
}

pid_t UnixProcess::GetPid() const {
    return pid;
}

bool UnixProcess::IsAlive() const {
    if (!alive)
        return false;
    if (!IsChild() && GetPid() != -1)
    {
        int stat;
        waitpid(GetPid(), &stat, WNOHANG);
        alive = (kill(GetPid(), 0) == 0);
    }
    return alive;
}

int UnixProcess::WaitSon() const {
    int status = 0;

    if (!IsChild() && IsAlive())
        waitpid(GetPid(), &status, 0);
    return status;
}
