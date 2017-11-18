//
// Created by asdoasdsadsad on 4/30/2017.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

se::Camera g_Camera(45.f, 1024/720, 0.1f, 3000.f);

se::Camera::Camera()
{

}

se::Camera::Camera(float fov, float aspect, float near, float far)
{
    _perspective = glm::perspective(fov, aspect, near, far);
    _far = far;

    _up = glm::vec3(0,1,0);
}

glm::mat4 se::Camera::getMatrix()
{
    glm::mat4 camera;

    camera *= _perspective;
    //camera *= Orientation();
    //camera = glm::translate(camera, _position);

    camera *= getView();

    return camera;
}

/**
 * Returns the perspective of the camera (FOV, Near and Far clipping plane)
 * @return
 */
glm::mat4 se::Camera::getPerspective()
{
    return _perspective;
}

/**
 * Use this to get the camera view
 * @return Returns the view that the camera has from the position
 */
glm::mat4 se::Camera::getView()
{
    return glm::lookAt(_position, _position + _front, _up);
}

/**
 * Will move the camera in the direction sent * moveSpeed * the frameTime
 * @param pos
 */
void se::Camera::translate(CameraDirection direction, float frameTime)
{
    switch (direction) {
        case CameraDirection::CFORWARD:
            _position += _front * (_moveSpeed * frameTime);
            break;

        case CameraDirection::CBACK:
            _position -= _front * (_moveSpeed * frameTime);
            break;

        case CameraDirection::CLEFT:
            _position -= glm::normalize(glm::cross(_front, _up)) * (_moveSpeed * frameTime);
            break;

        case CameraDirection::CRIGHT:
            _position += glm::normalize(glm::cross(_front, _up)) * (_moveSpeed * frameTime);
            break;
    }
}

/**
 * Camera will instantly rotate to provided angles
 * @param x X axis
 * @param y Y axis
 */
void se::Camera::focus(float x, float y)
{
    _xAngle = x;
    _yAngle = y;
}

void se::Camera::rotate(float x, float y)
{
    _xAngle += x;
    _yAngle += y;
}

/**
 * Will add the sent angles to the current angles of the camera
 * @param pos the new angles to be added
 */
void se::Camera::rotate(glm::vec2 pos)
{
    _xAngle += pos.x;
    _yAngle += pos.y;
}

/**
 * Camera will follow the mouse while this is being called
 * @param window the current game window
 */
void se::Camera::trackMouse(sf::Window *window)
{
   if( window->hasFocus())
   {
       window->setMouseCursorVisible(false);
       float wsX = window->getSize().x;
       float wsY = window->getSize().y;

       float x = (sf::Mouse::getPosition(*window).x);
       float y = (sf::Mouse::getPosition(*window).y);

       x = (x - (wsX / 2)) * _mouseSensitivity;
       y = (y - (wsY / 2)) * _mouseSensitivity;

       rotate(x, -y); //negative y to invert the mouse control

       //Calculating where camera is facing
       glm::vec3 front;
       front.x = (float)(cos(glm::radians(_yAngle)) * cos(glm::radians(_xAngle)));
       front.y = (float)sin(glm::radians(_yAngle));
       front.z = (float)(cos(glm::radians(_yAngle)) * sin(glm::radians(_xAngle)));
       _front = glm::normalize(front);

       sf::Mouse::setPosition(sf::Vector2i(wsX / 2, wsY / 2), *window);
   }
   else
       window->setMouseCursorVisible(true);
}

/**
 * Will move the camera to the position instantly
 * @param position position the camera will be.
 */
void se::Camera::move(glm::vec3 position)
{
    _position = position;
}

const glm::vec3 &se::Camera::getPosition() const {
    return _position;
}
