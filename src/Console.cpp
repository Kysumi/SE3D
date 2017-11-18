//
// Created by Abomy on 5/4/2017.
//

#include "Console.h"
#include "RenderManager.h"
#include "tools.h"
#include "Skybox.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include "Hitbox.h"


namespace se
{
    Console g_Console;

    Console::Console()
    {


    }

    Console::~Console()
    {
    }
    void Console::fetchInput()
    {

        while (g_RenderManager.getWindow()->isOpen())
        {
            std::string input;


            std::getline(std::cin, input);

            g_Console.runCommand(input);
        }
    }
    void Console::setup()
    {
        fetchThread = new std::thread(&Console::fetchInput, g_Console);

        fetchThread->detach();
    }
    void Console::runCommand(std::string command)
    {

        std::string c = command.substr(0, command.find(' '));
        std::transform(c.begin(), c.end(), c.begin(), ::tolower);

        std::string p = command.substr(command.find(' ') + 1);



        if (c == "reload")
        {
            tools::Print("Reload type '" + p + "' not found.");
        }
        else if(c == "skybox")
        {
           // g_RenderManager.getSkybox()->setSkybox(p);
        }
        else if(c == "gizmos")
        {
            se::Hitbox::DrawBoxes = !se::Hitbox::DrawBoxes;

        }
        else if(c == "camera")
        {

            std::vector<std::string> _params = tools::Split(p.c_str(),' ');

            if(_params.size() == 4)
            {
                if(_params[0] == "teleport" || _params[0] == "tp")
                {
                    float x,y,z = 0;

                    x = std::stof(_params[1]);
                    y = std::stof(_params[2]);
                    z = std::stof(_params[3]);
                    g_Camera.move(x, y, z);
                }
            }
        }
        else
        {
            tools::Print("Command not found.");
        }

    }
}