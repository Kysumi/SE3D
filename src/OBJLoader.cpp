//
// Created by asdoasdsadsad on 5/6/2017.
//

#include "OBJLoader.h"
#include "BlenderOBJ.h"
#include "tools.h"
#include <fstream>
#include <sstream>

std::string se::OBJLoader::defaultP = "/content/Objects/";

bool se::OBJLoader::_isWarned; //Warns about missing texture data

se::OBJPointer se::OBJLoader::loadObj(std::string fileName) {

    OBJPointer obj;

    obj.name = fileName;

    _isWarned = false;

    std::string objDir = tools::getWorkingDirectory() + defaultP + fileName + ".obj";
    std::string mtlDir = tools::getWorkingDirectory() + defaultP + fileName + ".mtl";

    ///Opening files and error checking
    std::fstream objFile(objDir);
    std::fstream mtlFile(mtlDir);

    if(objFile.is_open() == false)
        std::cerr << "ERROR OPENING OBJ FILE: " << fileName << " :CHECK IT IS IN THE DIRECTORY" << std::endl;

    if(mtlFile.is_open() == false)
        std::cerr << "ERROR OPENING MTL FILE: " << fileName << " :CHECK IT IS IN THE DIRECTORY" << std::endl;

    ///READING FILE BEGINS
    std::string firstWord;

    //Gets the first characters till a blank space is hit
    while(objFile >> firstWord)
    {
        //Gets the remainder of the line
        std::string line;
        getline(objFile, line);

        stripLine(firstWord, line, &obj);
    }

    return obj;
}

void se::OBJLoader::stripLine(std::string first, std::string line, OBJPointer *obj) {

    //I change the string to string stream for easy mode casting
    std::stringstream stream;
    stream << line;

    //Comment skip
    if(first == "#")
       return;

    //Vertex
    if(first == "v")
    {
        glm::vec3 vec;
        stream >> vec.x >> vec.y >> vec.z;

        obj->checkMinMax(vec);
        obj->_vertices.push_back(vec);
    }
        //Vertex texture
    else if(first == "vt")
    {
        glm::vec2 vec;
        stream >> vec.x >> vec.y;
        obj->_uvs.push_back(vec);
    }
        //Vertex normal
    else if(first == "vn")
    {
        glm::vec3 normal;
        stream >> normal.x >> normal.y >> normal.z;
        obj->_normals.push_back(normal);
    }
        //indexed drawing
    else if(first == "f")
    {
        /* //Order vertice, vertex texture, vertex normal
         //Texture cordinates are optional -- need to program that in

         int lineLoc = line.find ("/");

         for (int i = 0; i < 3; ++i)
         {
             //Get the vertices
             obj->addVectI(std::atoi(line.substr (0,lineLoc).c_str()));

             //strip the vertice and the / out
             line = line.substr(lineLoc + 1);

             //find location of the next /
             lineLoc = line.find("/");

             //bar is the next character in the string so no texture coord
             if (lineLoc == 0 && _isWarned == false) {
                 std::cerr << "!!!!! No texture coords found: " << obj->getName() << ".obj !!!!!" << std::endl;
                 _isWarned = true;
             }
             //there was a number in next position get it
             else
                 obj->addUVI(std::atoi(line.substr(0, lineLoc).c_str()));

             //strip the texture coord and the / out
             line = line.substr(lineLoc + 1);

             //For the normals we look for a space not a /
             lineLoc = line.find(" ");

             obj->addNormalI(std::atoi(line.substr(0,lineLoc).c_str()));

             //strip the normal and the space out
             line = line.substr(lineLoc + 1);
         }*/

        for (int i = 0;i < 3; i++)
        {
            std::string face;
            stream >> face;

            std::istringstream faceData(face);
            std::string vertex;

            while (std::getline(faceData, vertex, '/'))
            {
                std::istringstream vertexData(vertex);

                unsigned int tmp;
                vertexData >> tmp;
                obj->vectorIndices.push_back(tmp - 1);
                break; //TODO implement texture co-ordinates and normals
            }
        }
    }
}

