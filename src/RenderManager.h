//
// Created by Abomy on 5/1/2017.
//

#ifndef SE3D_RENDERMANAGER_H
#define SE3D_RENDERMANAGER_H

#include <vector>
#include <SFML/Window.hpp>


namespace se{
    class Skybox;

class Renderable;
class RenderManager {

public:
    void registerRenderable(Renderable * r);
    void unregisterRenderable(Renderable * r);
    void drawThatShit();
    void updateThatShit();

    void setWindow (sf::Window * w){_window = w;}
    sf::Window * getWindow(){return _window;};


    void setSkybox (se::Skybox* sb){_skybox = sb;}
    se::Skybox * getSkybox(){return _skybox;};

    void cleanRenderables();

    RenderManager(){};
private:
    std::vector<Renderable *> _renderables;
    sf::Window * _window;
    se::Skybox * _skybox;
};


}
extern se::RenderManager g_RenderManager;


#endif //SE3D_RENDERMANAGER_H
