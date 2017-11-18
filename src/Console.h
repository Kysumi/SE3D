//
// Created by Abomy on 5/4/2017.
//

#ifndef SE3D_CONSOLE_H
#define SE3D_CONSOLE_H

#ifdef _WIN32
#include "thread.h"
#endif
#ifdef __APPLE__

#include <thread>

#endif

#include <iostream>
#include <stdio.h>

namespace se
{
    class Console
    {
    public:
        Console();
        ~Console();

        void fetchInput();
        void setup();

        std::thread* fetchThread;


        void runCommand(std::string command);
    };

    extern Console g_Console;
}


#endif //SE3D_CONSOLE_H
