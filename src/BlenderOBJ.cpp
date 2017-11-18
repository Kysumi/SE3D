//
// Created by asdoasdsadsad on 5/6/2017.
//

#include "BlenderOBJ.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Hitbox.h"


extern se::Camera g_Camera;

void se::BlenderOBJ::initialise() {

    _program.loadShaders("CubeTestVertex.glsl", "CubeTestFrag.glsl");

    _l.initialise(*getVbo());

    if(_isHitbox == false)
    {
        _hitbox = new Hitbox();

        float scaleX = (1 / (_objp._max.x - _objp._min.y)) * _scale.x;
        float scaleY = (1 / (_objp._max.y - _objp._min.y)) * _scale.y;
        float scaleZ = (1 / (_objp._max.z - _objp._min.z)) * _scale.z;

        _hitbox->setScale(glm::vec3(scaleX,scaleY,scaleZ));
        _hitbox->initialize();

    }

    subscribeMeFam();

}

void se::BlenderOBJ::draw() {

    _l.Update();

    if (getType() == SKYBOX || _isHitbox)
        _program.useProgram();


    glm::mat4 translationM = glm::translate(glm::mat4(), _position);

    glm::mat4 rotationM = glm::rotate(glm::mat4(), _rotation.x, glm::vec3(1.f,0.f,0.f));
    rotationM *= glm::rotate(glm::mat4(), _rotation.y, glm::vec3(0.f,1.f,0));

    glm::mat4 scalingM = glm::scale(glm::mat4(), _scale);

    glm::mat4 _model = translationM * rotationM * scalingM;

    //Getting positions
    GLint vLoc = glGetUniformLocation(_program.getID(), "V");
    GLint pLoc = glGetUniformLocation(_program.getID(), "P");

    GLint mLoc = glGetUniformLocation(_program.getID(), "M");


    glUniformMatrix4fv(mLoc,1,GL_FALSE, glm::value_ptr(_model));

    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(g_Camera.getView()));
    glUniformMatrix4fv(pLoc, 1,GL_FALSE, glm::value_ptr(g_Camera.getPerspective()));


    glPolygonMode( GL_FRONT_AND_BACK, _renderType );

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _objp.vbo);
    glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _objp.ibo);
    //glBindBuffer(GL_ARRAY_BUFFER, *getVbo());
    glVertexPointer(0, GL_FLOAT, 0, &_objp._vertices[0]);

    if(*getTexture()!= 0)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, *getTexture());
        //glDrawElements(GL_QUADS, vectorIndices.size(), GL_UNSIGNED_INT, 0);
    }
    glDrawElements(GL_TRIANGLES, _objp.vectorIndices.size(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);

    _l.Draw();

    if(_isHitbox == false)
        _hitbox->draw();

   //glDepthMask(GL_TRUE);

}

std::string se::BlenderOBJ::getName() {
    return _objName;
}

void se::BlenderOBJ::update() {


    if(_isHitbox == false) {
        _hitbox->setPosition(_position);
        _hitbox->update();
    }


    if(updateCallback != NULL)
        updateCallback(this);

}

