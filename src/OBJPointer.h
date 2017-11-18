//
// Created by Scott Maunder on 26/05/17.
//

#ifndef SE3D_OBJPOINTER_H
#define SE3D_OBJPOINTER_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace se {
    struct OBJPointer {

        OBJPointer() {

            _min = glm::vec3(0.f, 0.f, 0.f);
            _max = glm::vec3(0.f, 0.f, 0.f);
        };

        GLuint vbo;
        GLuint ibo;

        std::vector<glm::vec3> _vertices;
        std::vector<glm::vec2> _uvs;
        std::vector<glm::vec3> _normals;


        glm::vec3 _min, _max;

        std::vector<int> vectorIndices;
        std::vector<int> uvIndices;
        std::vector<int> normalIndices;

        std::string name;


        void checkMinMax(glm::vec3 vec) {

            if (vec.x < _min.x)
                _min.x = vec.x;
            if (vec.z < _min.y)
                _min.y = vec.z;
            if (vec.y < _min.z)
                _min.z = vec.y;


            if (vec.x > _max.x)
                _max.x = vec.x;
            if (vec.z > _max.y)
                _max.y = vec.z;
            if (vec.y > _max.z)
                _max.z = vec.y;
        }
    };
}

#endif //SE3D_OBJPOINTER_H
