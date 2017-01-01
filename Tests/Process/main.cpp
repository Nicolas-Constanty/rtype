//
// Created by gaspar on 31/12/2016.
//

#include "Process/Process.hpp"

int main()
{
    OSProcess   process;

    process.Launch("test.bat");
    if (process.IsAlive())
        process.WaitSon();
    return 0;
}