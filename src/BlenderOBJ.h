//
// Created by asdoasdsadsad on 5/6/2017.
//

#ifndef SE3D_BLENDEROBJ_H
#define SE3D_BLENDEROBJ_H

#include <vector>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <string>
#include "Program.h"
#include "Renderable.h"
#include "OBJLoader.h"
#include "Light.h"
#include <functional>
#include "OBJPointer.h"


namespace se{
class Hitbox;
    class BlenderOBJ : public Renderable {

    public:
        BlenderOBJ() {};

        BlenderOBJ(OBJPointer obj, bool hitbox = false)
        {

            _isHitbox = hitbox;

            setType(UNIQUE);
            updateCallback = NULL;
            drawCallback = NULL;

            _objp = obj;

            disableWireframe();
        };

        void initialise();
        virtual void draw();
        virtual void update();

        std::string getName();

        void set_position(const glm::vec3 &_position) {
            BlenderOBJ::_position = _position;
        }

        void addUpdateCallback(const std::function<void(BlenderOBJ *)> &updateCallback) {
            BlenderOBJ::updateCallback = updateCallback;
        }

        void addDrawCallback(const std::function<void(BlenderOBJ *)> &drawCallback) {
            BlenderOBJ::drawCallback = drawCallback;
        }

        void enableWireframe() {
            _renderType = GL_LINE;
        }

        void disableWireframe() {
            _renderType = GL_FILL;
        }


    private:
        Light _l;
        std::string _objName;

        OBJPointer _objp;

        std::function<void(se::BlenderOBJ * )> updateCallback;
        std::function<void(se::BlenderOBJ * )> drawCallback;

        GLenum _renderType;
        bool _isHitbox;
        Hitbox * _hitbox;

    };
}



#endif //SE3D_BLENDEROBJ_H
