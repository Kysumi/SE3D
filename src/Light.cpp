//
// Created by Abomy on 5/19/2017.
//

#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Light::Light()
{
    _program.loadShaders("diffuseVS.glsl","diffuseFrag.glsl");



}

void Light::Update()
{
    _program.useProgram();


    glm::mat4 translationM = glm::translate(glm::mat4(), _position);

    glm::mat4 rotationM = glm::rotate(glm::mat4(), _rotation.x, glm::vec3(1.f,0.f,0.f));
    rotationM *= glm::rotate(glm::mat4(), _rotation.y, glm::vec3(0.f,1.f,0));

    glm::mat4 scalingM = glm::scale(glm::mat4(), _scale);

    glm::mat4 _model = translationM  * rotationM * scalingM;

    //Getting positions
    GLint vLoc = glGetUniformLocation(_program.getID(), "V");
    GLint pLoc = glGetUniformLocation(_program.getID(), "P");

    GLint mLoc = glGetUniformLocation(_program.getID(), "M");

    GLint ocLoc = glGetUniformLocation(_program.getID(), "objectColor");
    GLint lcLoc = glGetUniformLocation(_program.getID(), "lightColor");
    GLint lpLoc = glGetUniformLocation(_program.getID(), "lightPos");
    GLint vpLoc = glGetUniformLocation(_program.getID(), "viewPos");



    glUniformMatrix4fv(mLoc,1,GL_FALSE, glm::value_ptr(_model));

    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(g_Camera.getView()));
    glUniformMatrix4fv(pLoc, 1,GL_FALSE, glm::value_ptr(g_Camera.getPerspective()));

    glUniform3fv(ocLoc,1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
    glUniform3fv(lcLoc,1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    glUniform3fv(lpLoc,1, glm::value_ptr(glm::vec3(1.3f, 1.3f, 2.f)));
    glUniform3fv(vpLoc,1, glm::value_ptr(g_Camera.getPosition()));

}
void Light::Draw()
{

    glBindVertexArray(_lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


void Light::initialise(GLuint vbo)
{
    glGenVertexArrays(1, &_lightVAO);
    glBindVertexArray(_lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER,  vbo);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(0);
}