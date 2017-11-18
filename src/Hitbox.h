//
// Created by Abomy on 21/05/2017.
//

#ifndef SE3D_HITBOX_H
#define SE3D_HITBOX_H


#include <glm/vec3.hpp>
#include "BlenderOBJ.h"


namespace se {

    class Hitbox  {

    public:
        void initialize();
       void draw();

       void update()
       {
           _box.setPosition(_position);
           _min = _position - _bounds;
           _max = _position + _bounds;
           _box.setDrawing(DrawBoxes);
       }

        bool containsPoint(glm::vec3 point) {
            return (point.x >= _min.x && point.x <= _max.x) &&
                   (point.y >= _min.y && point.y <= _max.y) &&
                   (point.z >= _min.z && point.z <= _max.z);
        }

        bool intersect(const Hitbox &b) {
            return (_min.x <= b.getMin().x && _max.x >= b.getMax().x) &&
                   (_min.y <= b.getMin().y && _max.y >= b.getMax().y) &&
                   (_min.z <= b.getMin().z && _max.z >= b.getMax().z);
        }

        const glm::vec3 &getMin() const {
            return _min;
        }

        const glm::vec3 &getMax() const {
            return _max;
        }

         static bool DrawBoxes;

        void setPosition(const glm::vec3 &_position) {
            Hitbox::_position = _position;
        }

        void setScale(const glm::vec3 &_scale) {
            Hitbox::_scale = _scale;
        }

    private:
        glm::vec3 _position,_bounds,_min,_max,_scale;
        BlenderOBJ _box;

    };


}

#endif //SE3D_HITBOX_H
