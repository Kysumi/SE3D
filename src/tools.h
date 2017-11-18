//
// Created by Scott Maunder on 18/04/17.
//

#ifndef SE3D_TOOLS_H
#define SE3D_TOOLS_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#ifdef __APPLE__
#include <zconf.h>
#endif

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#include <io.h>
#endif

class tools {
public:
    static void fps(sf::Window *window){
        static sf::Clock clock;
        static double previous_seconds = clock.getElapsedTime().asSeconds();
        static int frame_count;
        double current_seconds = clock.getElapsedTime().asSeconds();
        double elapsed_seconds = current_seconds - previous_seconds;

        if (elapsed_seconds > 0.25) {
            previous_seconds = current_seconds;
            double fps = (double)frame_count / elapsed_seconds;
            char tmp[128];
            sprintf(tmp, "SE3D @ fps: %.2f", fps);
            window->setTitle(tmp);
            frame_count = 0;
        }
        frame_count++;
    }

    static void Print(std::string msg, bool console = false)
    {
        std::cout  << msg <<std::endl;
    }

    static std::vector<std::string> Split(const char *str, char c = ' ')
    {
        std::vector<std::string> result;

        do
        {
            const char *begin = str;

            while(*str != c && *str)
                str++;

            result.push_back(std::string(begin, str));
        } while (0 != *str++);

        return result;
    }

    static std::string getWorkingDirectory()
    {
        std::string dir;

        //Getting current file directory
        char buffer[100];
        char *answer = getcwd(buffer, sizeof(buffer));

        if (answer)
            dir = answer;
        else
            std::cerr << "Error getting current directory while loading SKYBOX: " << dir << std::endl;

        return dir;
    }



/*
    static std::map<std::string,std::map<std::string, auto>> readIni()
    {

    };*/
};


#endif //SE3D_TOOLS_H
