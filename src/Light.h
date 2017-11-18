//
// Created by Abomy on 5/19/2017.
//

#ifndef SE3D_LIGHT_H
#define SE3D_LIGHT_H
#include "Transformable.h"
#include "Camera.h"
#include "Program.h"

class Light : public se::Transformable{

public:
    Light();
    void Update();
    void Draw();
    void initialise(GLuint vbo);
private:
    Program _program;
    GLuint  _lightVAO;
};


#endif //SE3D_LIGHT_H
