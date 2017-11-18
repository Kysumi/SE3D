//
// Created by Abomy on 21/05/2017.
//

#include "Hitbox.h"
#include "OBJManager.h"

bool se::Hitbox::DrawBoxes = false;


void se::Hitbox::initialize() {

    _box = se::BlenderOBJ(se::OBJManager::requestOBJ("cube"), true);

    _box.setPosition(_position);
    _box.setScale(_scale + glm::vec3(0.05f,0.05f,0.05f));
    _box.enableWireframe();
    _box.initialise();
}

void se::Hitbox::draw() {
    if(DrawBoxes)
        _box.draw();

}
