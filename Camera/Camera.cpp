//
// Created by aa068 on 13.08.2022.
//

#include "Camera.h"
#include <cmath>

void Camera::rotateRight() {
    _angle.z += _rotationAngle;
}

void Camera::rotateLeft() {
    _angle.z -= _rotationAngle;
}

void Camera::rotateUp() {
    _angle.x -= _rotationAngle;
}

void Camera::rotateDown() {
    _angle.x += _rotationAngle;
}

void Camera::setForwardDirection(int direction) {
    _directionAxis.y = direction == 0 ? 0 : direction / abs(direction);
}

void Camera::setRightDirection(int direction) {
    _directionAxis.x = direction == 0 ? 0 : direction / abs(direction);
}


void Camera::setUpDirection(int direction) {
    _directionAxis.z = direction == 0 ? 0 : direction / abs(direction);
}

void Camera::clearDirection() {
    _directionAxis.x = _directionAxis.y = _directionAxis.z = 0;
}

void Camera::move() {
    _directionAxis.z *= _speed;
    _position.z += _directionAxis.z;

    if (_directionAxis.y == _directionAxis.x && _directionAxis.x == 0) return;

    float length = sqrt(_directionAxis.x * _directionAxis.x + _directionAxis.y * _directionAxis.y);
    _directionAxis.x /= length;
    _directionAxis.y /= length;

    _directionAxis.x *= _speed;
    _directionAxis.y *= _speed;


    _position.x += _directionAxis.y * sin(_angle.z * M_PI / 180) + _directionAxis.x * cos(_angle.z * M_PI / 180);
    _position.y +=  _directionAxis.y * cos(_angle.z * M_PI / 180) - _directionAxis.x * sin(_angle.z * M_PI / 180);

}

Angle_t Camera::getAngle() {
    return _angle;
}

Point_t Camera::getPosition() {
    return _position;
}
