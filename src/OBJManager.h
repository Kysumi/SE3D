//
// Created by Scott Maunder on 8/05/17.
//

#ifndef SE3D_OBJMANAGER_H
#define SE3D_OBJMANAGER_H

#include <map>
#include "OBJLoader.h"
#include "OBJPointer.h"

namespace se {

    class OBJManager : se::OBJLoader {

    public:
        static OBJPointer requestOBJ(std::string objName);

    private:
        static std::map<std::string, se::OBJPointer> objMap;
    };
}


#endif //SE3D_OBJMANAGER_H
