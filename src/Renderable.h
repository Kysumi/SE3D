//
// Created by Abomy on 5/1/2017.
//

#ifndef SE3D_RENDERABLE_H
#define SE3D_RENDERABLE_H
#include "RenderManager.h"
#include "Program.h"
#include "Transformable.h"
#include "tools.h"
#include <GL/glew.h>
#include <stdexcept>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

/**
 * Types of renderables
 */
enum RenderType {
    NONE,
    CUBE,
    UNIQUE,
    SKYBOX
};

enum  BufferType
{
    VBO,VAO,IBO
};

namespace se {
    class Renderable : public se::Transformable {

    public:
        Renderable() {
            drawing = true;
            _texture = 0;
        };

        void subscribeMeFam()
        {
            g_RenderManager.registerRenderable(this);
        }


        bool isDrawing() { return drawing; };

        /**
         * Pure virtual for draw.
         */
        virtual void draw() = 0;

        virtual void update() = 0;

        Program *getProgram() {
            return &_program;
        }


        RenderType getType() const {
            return _type;
        }

        void setScale(glm::vec3 scale) {
            _scale = scale;
        }

        void rotateX(float v) {
            _rotation.x += v;
        }

        void rotateY(float v) {
            _rotation.y += v;
        }

        GLuint *getTexture() {
            return &_texture;
        }

        void setTexture(GLuint _texture) {
            Renderable::_texture = _texture;
        }
        /**
         * Sets the VBO/VAO type of the object.
         * @param t
         */
        void setType(RenderType t) { _type = t; }


        void setDrawing(bool drawing) {
            Renderable::drawing = drawing;
        }

    protected:


        /**
         * Returns the VBO of the object
         * @return
         */
        GLuint *getVbo() { return returnType(VBO); }

        /**
         * Returns the VAO of the object
         * @return
         */
        GLuint *getVao() { return returnType(VAO); }

        /**
         * Returns the IBO of the object
         * @return
         */
        GLuint *getIbo() { return returnType(IBO); }


        bool drawing;
    private:
        /**
         * Handler for returning either the VBO or VAO of the object
         * @param isVbo Boolean for if its a vbo or not
         * @return
         */
        GLuint *returnType(BufferType type) {
            if (_type == NONE) {
                throw std::invalid_argument("[Renderable::returnType()] - Renderable type has not been set.");
            }
            if (_type == CUBE)
                return (type == VBO ? &_vboCube : (type == VAO ? &_vaoCube : &_iboCube));
            else if (_type == UNIQUE)
                return (type == VBO ? &_vbo : (type == VAO ? &_vao : &_ibo));
            else if (_type == SKYBOX)
                return (type == VBO ? &_vbo : (type == VAO ? &_vao : &_ibo));

            return nullptr;
        }

        GLuint _vao, _vbo, _ibo, _texture;


    private:
        GLuint _vaoCube, _vboCube, _iboCube;
        RenderType _type;

    protected:

        Program _program;

    };

}


#endif //SE3D_RENDERABLE_H
