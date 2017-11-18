
#include <GL/glew.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include "tools.h"
#include "Skybox.h"
#include "Console.h"
#include "WebRequest.h"
#include "MazeGeneration.h"

extern se::Camera g_Camera;
extern se::Console g_Console;

void testUpdateCallback(se::BlenderOBJ * obj)
{
    obj->setPosition(obj->getPosition() + glm::vec3(0.f,0.f,0.00001f));
}

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 1;

    sf::Window window(sf::VideoMode(2560, 1080), "SE3D", sf::Style::Default, settings);
    g_RenderManager.setWindow(&window);
    se::g_Console.setup();

    //Sets default clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        std::cout << "GLEW BROKE INIT" << std::endl;
        return 1;
    }

    g_Camera.move(0, 0, 0);


#ifdef __APPLE__
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
#endif

    //z buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    se::BlenderOBJ objCube(se::OBJManager::requestOBJ("circle"));

    objCube.addUpdateCallback(testUpdateCallback);

    objCube.set_position(glm::vec3(0, 0, -2));
    objCube.initialise();

    se::Skybox skybox("dark");

    se::BlenderOBJ key(se::OBJManager::requestOBJ("key"));
    key.set_position(glm::vec3(0, 0, 0));
    key.initialise();

    se::BlenderOBJ key2(se::OBJManager::requestOBJ("key"));
    key2.set_position(glm::vec3(2, 2, 2));
    key2.initialise();

    //NO cubs yet! need to be modified ALOT
    se::Maze maze(10,10);
    maze.Generate();

    sf::Clock clock;

    while (window.isOpen()) {
        tools::fps(&window);

        // Process events
        sf::Event Event;
        while (window.pollEvent(Event)) {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                window.close();

            // Escape key : exit
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                window.close();

            if (Event.type == sf::Event::KeyPressed) {

                float frameT = clock.getElapsedTime().asSeconds();

                switch (Event.key.code) {
                    case sf::Keyboard::W:
                        g_Camera.translate(CameraDirection::CFORWARD,frameT);
                        break;
                    case sf::Keyboard::S:
                        g_Camera.translate(CameraDirection::CBACK, frameT);
                        break;

                    case sf::Keyboard::A:
                        g_Camera.translate(CameraDirection::CLEFT, frameT);
                        break;

                    case sf::Keyboard::D:
                        g_Camera.translate(CameraDirection::CRIGHT, frameT);
                        break;
                    case sf::Keyboard::H:
                    se::WebRequest::fetchHighscores();
                        break;
                }

                //clock.restart();
            }
        }

        //clears window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        skybox.update();

        g_Camera.trackMouse(&window);

        g_RenderManager.updateThatShit();
        g_RenderManager.drawThatShit();

        glDisableVertexAttribArray(0);


        clock.restart();

        window.display();
    }

    return EXIT_SUCCESS;
}