//
// Created by aa068 on 16.08.2022.
//

#ifndef OPENGLTEST_PYRAMIDFIGURE_H
#define OPENGLTEST_PYRAMIDFIGURE_H

#include "BaseFigure.h"

class PyramidFigure : public BaseFigure {
public:
    PyramidFigure(Point_t positionCenter, float widthBase, float height, Point_t color) {
        _typeDisplay = GL_TRIANGLES;
        _vertices = std::vector<GLfloat>({ -widthBase/2,-widthBase/2,0,
                                           -widthBase/2,widthBase/2,0,
                                           widthBase/2,widthBase/2,0,
                                           widthBase/2,-widthBase/2,0,
                                           0,0,positionCenter.z + height
                                           });
        _normals = std::vector<GLfloat>({ -1,-1,-3,
                                          -1,1,-3,
                                          1,1,-3,
                                          1,-1,-3,
                                          0,0,3});


        _colors = std::vector<GLfloat>({ color.x, color.y, color.z,
                                         color.x, color.y, color.z,
                                         color.x, color.y, color.z,
                                         color.x, color.y, color.z,
                                         color.x, color.y, color.z});
        _indexes = std::vector<unsigned int>({  0,1,2,  2,3,0, 0,1,4, 1,2,4, 2,3,4, 3,0,4  });
        _position = positionCenter;
    }

    ~PyramidFigure() override;
};


#endif //OPENGLTEST_PYRAMIDFIGURE_H
