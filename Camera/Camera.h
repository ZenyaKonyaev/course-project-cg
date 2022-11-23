//
// Created by aa068 on 13.08.2022.
//

#ifndef OPENGLTEST_CAMERA_H
#define OPENGLTEST_CAMERA_H

#include "../Other/defines.h"

class Camera {
public:
    // функции контроллера 50/50 start
    void rotateRight();
    void rotateLeft();
    void rotateUp();
    void rotateDown();
    // функции контроллера 50/50 end

    //функции контроллера start
    void setForwardDirection(int);
    void setRightDirection(int);
    void setUpDirection(int);
    void clearDirection();

    void move();
    //функции контроллера end

    Point_t getPosition();
    Angle_t getAngle();

private:
    Point_t _position = { 0, 0, 0 };
    Angle_t _angle = { 0, 0, 0 };
    Vector_t _directionAxis = { 0, 0, 0 };
    float _speed = 0.5;
    float _rotationAngle = 2;
};


#endif //OPENGLTEST_CAMERA_H
