//
// Created by Scott Maunder on 23/04/17.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "Program.h"
#include "tools.h"

Program::Program()
{
    if(_isLinked)
    {
        glDeleteProgram(_programID);
        _isLinked = false;
    }

    _programID = glCreateProgram();
}

/*
 * Tries to link if it fails it returns false else ok
 */
bool Program::linkProgram()
{
    glLinkProgram(_programID);

    GLint linkStatus;
    glGetProgramiv(_programID, GL_LINK_STATUS, &linkStatus);

    _isLinked = (linkStatus == GL_TRUE);

    return _isLinked;
}

void Program::useProgram()
{
    if(_isLinked)
        glUseProgram(_programID);
}

GLuint Program::getID() {
    return _programID;
}

bool Program::loadShaders(std::string vertex, std::string fragment)
{
    bool isOK = true;

    //Create the shaders
    _fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    _vertShader = glCreateShader(GL_VERTEX_SHADER);

    ///READING SHADER'S INTO STRINGS

    std::string cwd = tools::getWorkingDirectory() + "/content/shaders/";

    //Reading the Vertex shader from file into a string
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(cwd + vertex.c_str());

    //Checks file was opened correctly
    if(VertexShaderStream.is_open())
    {
        //Read file line by line
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;

        VertexShaderStream.close();
    }
    else
    {
        std::cout << "Vertex shader could not be opened: " <<
                  vertex << " Make sure file is in correct directory " << std::endl;
        isOK = false;
    }

    //Reading the Fragment shader from file into a string
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(cwd + fragment.c_str());

    //Checks file was opened correctly
    if(FragmentShaderStream.is_open())
    {
        //Read file line by line
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;

        FragmentShaderStream.close();
    }
    else
    {
        std::cout << "Fragment shader could not be opened: " <<
                  fragment << " Make sure file is in correct directory " << std::endl;
        isOK = false;
    }

    ///READING SHADER'S INTO STRINGS END

    ///COMPILING SHADER'S

    //Can you think of a way to concat this into a single line?
    char const *vertexSource = VertexShaderCode.c_str();
    char const *fragmentSource = FragmentShaderCode.c_str();

    //Setting the source for both shader's
    glShaderSource(_fragShader,1, &fragmentSource, NULL);
    glShaderSource(_vertShader, 1, &vertexSource, NULL);

    //compiling the shader
    glCompileShader(_fragShader);
    glCompileShader(_vertShader);

    ///COMPILING SHADER'S END

    ///ERROR CHECKING

    if(checkCompile(_fragShader, fragment) == false)
        isOK = false;

    if(checkCompile(_vertShader, vertex) == false)
        isOK = false;

    ///ERROR CHECKING END

    //Linking shader's to the program
    glAttachShader(_programID, _fragShader);
    glAttachShader(_programID, _vertShader);
    glLinkProgram(_programID);

    //These can be deleted now that they are linked
    glDetachShader(_programID, _fragShader);
    glDeleteShader(_fragShader);

    glDetachShader(_programID, _vertShader);
    glDeleteShader(_vertShader);

    GLint linkOK;
    glGetProgramiv(_programID, GL_LINK_STATUS, &linkOK);

    if(linkOK == 0)
    {
        GLchar ErrorLog[1024];
        glGetProgramInfoLog(_programID, sizeof(ErrorLog), NULL, ErrorLog);

        std::cerr << "ERROR LINKING SHADER'S TO PROGRAM: \n" << ErrorLog << std::endl;
    }

    //Will stay active until you call use program on another one
    glUseProgram(_programID);

    if(isOK)
        _isLinked = true;

    return isOK;
}

/**
 * @note Checks if the shader is compiled correctly. if not will print out an error to console
 * @param shaderID the shader GLuint
 * @param shaderName the shader file name
 * @return
 */
bool Program::checkCompile(GLuint shaderID, std::string shaderName)
{
    GLint isOK;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isOK);

    if(!isOK)
    {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderID, sizeof(InfoLog), NULL, InfoLog);

        std::cerr << "Error compiling shader: " << shaderName << "\n"
                  << InfoLog << std::endl;

        return false;
    }

    return true;
}