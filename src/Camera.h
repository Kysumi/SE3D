//
// Created by Scott Maunder on 4/30/2017.
//

#ifndef SE3D_CAMERA_H
#define SE3D_CAMERA_H

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

enum CameraDirection {
    CFORWARD,
    CBACK,
    CRIGHT,
    CLEFT,
};

namespace se{

    class Renderable;

    struct CameraMove{
        CameraMove(){x = 0; y = 0; z = 0;}
        float x,y,z;
    };
    struct MoveCX : public CameraMove{ public: MoveCX(float xAmount){ x = xAmount;}; };
    struct MoveCY: public CameraMove{ public: MoveCY(float yAmount){ y = yAmount;}; };
    struct MoveCZ : public CameraMove{ public: MoveCZ(float zAmount){ z = zAmount;}; };

    class Camera {

    public:
        Camera();
        Camera(float fov, float aspect, float near, float far);

        void focus(float x, float y);

        void rotate(float x, float y);
        void rotate(glm::vec2 pos);

        void translate(CameraDirection direction, float frameTime);

        //Might update this to give the camera a direction to look
        void move(glm::vec3 position);
        void move(float x = 0, float y = 0, float z = 0)
        {
            move(glm::vec3(x,y,z));
        };
        void move(CameraMove b)
        {
            move(glm::vec3(b.x,b.y,b.z));
        };

        void trackMouse(sf::Window *window);
        float getClippingPlane(){return _far;};

        glm::mat4 getMatrix();

        glm::mat4 getPerspective();

        glm::mat4 getView();

        const glm::vec3 &getPosition() const;

    private:

        glm::mat4 _perspective;

        glm::vec3 _position;
        glm::vec3 _front;
        glm::vec3 _up;

        float _moveSpeed = 200.f;

        float _mouseSensitivity = 0.05f;

        float _xAngle;      //X axis angle for camera
        float _yAngle;      //Y axis angle for camera
        float _far;

        se::Renderable * _target;

        /*
        float _FOV;         //Field of view
        float _AspectRatio; //Window height / window width
        float _nearPlane;   //OpenGL near cut off on z axis
        float _farPlane;    //OpenGL far cut off on z axis
        */
    };

}

extern se::Camera g_Camera;



#endif //SE3D_CAMERA_H
