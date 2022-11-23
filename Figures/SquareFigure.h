//
// Created by aa068 on 14.08.2022.
//

#ifndef OPENGLTEST_SQUAREFIGURE_H
#define OPENGLTEST_SQUAREFIGURE_H

#include "BaseFigure.h"

class SquareFigure : public BaseFigure {
public:
    SquareFigure(Point_t positionCenter, float width, Point_t color) {
        _typeDisplay = GL_TRIANGLES;
        _vertices = std::vector<GLfloat>({ -width/2,-width/2,0,
                                           -width/2,width/2,0,
                                           width/2,width/2,0,
                                           width/2,-width/2,0 });
        _normals = std::vector<GLfloat>({ -1,-1,3,
                                             -1,1,3,
                                             1,1,3,
                                             1,-1,3});

        _colors = std::vector<GLfloat>({ color.x, color.y, color.z,
                                         color.x, color.y, color.z,
                                         color.x, color.y, color.z,
                                         color.x, color.y, color.z  });
        _indexes = std::vector<unsigned int>({  0,1,2,  2,3,0   });
        _position = positionCenter;
    }

    ~SquareFigure() override;
};


#endif //OPENGLTEST_SQUAREFIGURE_H
