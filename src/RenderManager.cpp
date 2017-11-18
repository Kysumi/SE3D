//
// Created by Abomy on 5/1/2017.
//

#include <iostream>
#include "RenderManager.h"
#include "Renderable.h"
#include "BlenderOBJ.h"
#include <typeinfo>

se::RenderManager g_RenderManager;
namespace se {

    void RenderManager::registerRenderable(Renderable *r) {
        _renderables.push_back(r);
    }

    void RenderManager::drawThatShit() {
        for (int i = 0; i < _renderables.size(); ++i) {
            if (_renderables[i]->isDrawing())
                _renderables[i]->draw();
        }
    }

    void RenderManager::updateThatShit() {
        for (int i = 0; i < _renderables.size(); ++i) {
            if (_renderables[i]->isDrawing())
                _renderables[i]->update();
        }
    }


}