//
// Created by Scott Maunder on 23/04/17.
//

#ifndef SE3D_PROGRAM_H
#define SE3D_PROGRAM_H


#include <GL/glew.h>
#include <string>

class Program {

public:
    Program();
    void deleteProgram();

    bool loadShaders(std::string vertex, std::string fragment);

    bool linkProgram();

    void useProgram();

    GLuint getID();

private:

    bool checkCompile(GLuint shaderID, std::string shaderName);

    GLuint _programID;
    GLuint _fragShader;
    GLuint _vertShader;

    bool _isLinked;
};


#endif //SE3D_PROGRAM_H
