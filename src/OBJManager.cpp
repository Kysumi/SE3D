//
// Created by Scott Maunder on 8/05/17.
//

#include "OBJManager.h"

std::map<std::string, se::OBJPointer> se::OBJManager::objMap;

/**
 *
 * @param objName Name of the object file that you want to get
 * @return Returns a pointer
 */
se::OBJPointer se::OBJManager::requestOBJ(std::string objName) {
    //Checks if it exists
    //NOT FOUND
    OBJPointer newobj;

    if (objMap.find(objName) == objMap.end()) {
        newobj = loadObj(objName);

        ///Generating them buffers

        glGenBuffers(1, &newobj.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, newobj.vbo);
        glBufferData(GL_ARRAY_BUFFER, newobj._vertices.size() * sizeof(glm::vec3), newobj._vertices.data(),
                     GL_STATIC_DRAW);

        glGenBuffers(1, &newobj.ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newobj.ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, newobj.vectorIndices.size() * sizeof(int), newobj.vectorIndices.data(),
                     GL_STATIC_DRAW);

        objMap[newobj.name] = newobj; //Adding map
    }
        //FOUND
    else {
        newobj = objMap[objName];
    }

    return newobj;
};
