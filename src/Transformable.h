//
// Created by Abomy on 14/05/2017.
//

#ifndef SE3D_TRANSFORMABLE_H
#define SE3D_TRANSFORMABLE_H

#include <glm/gtc/matrix_transform.hpp>
namespace se
{
    class Transformable
    {
    public:
         Transformable()
        {
            _scale = glm::vec3(0.1, 0.1, 0.1);
            _rotation = glm::vec3(0, 0, 0);
        }
        glm::vec3 getFacing()
        {
            //Calculating where object is facing
            glm::vec3 front;
            front.x = (float)(cos(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x)));
            front.y = (float)sin(glm::radians(_rotation.y));
            front.z = (float)(cos(glm::radians(_rotation.y)) * sin(glm::radians(_rotation.x)));
            return  glm::normalize(front);
        }

        glm::vec3 getPosition() {
            return _position;
        }

        void setPosition(glm::vec3 pos) {
            Transformable::_position = pos;
        }

        glm::vec3 getScale() {
            return _scale;
        }

        void setScale(glm::vec3 s) {
            Transformable::_scale = s;
        }

        glm::vec3 getRotation() {
            return _rotation;
        }

        void setRotation(glm::vec3 rot) {
            Transformable::_rotation = rot;
        }

    protected:
        glm::vec3 _position,_scale,_rotation;

    };
}
#endif //SE3D_TRANSFORMABLE_H
