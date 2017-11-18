//
// Created by asdoasdsadsad on 5/6/2017.
//

#ifndef SE3D_OBJLOADER_H
#define SE3D_OBJLOADER_H


#include <string>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include "OBJPointer.h"

namespace se
{
    class BlenderOBJ;

    class OBJLoader
    {

    protected:
        static OBJPointer loadObj(std::string fileName);

        static void stripLine(std::string first, std::string line, OBJPointer *obj);

        static bool _isWarned;
        static std::string defaultP;
    };
}
#endif //SE3D_OBJLOADER_H
