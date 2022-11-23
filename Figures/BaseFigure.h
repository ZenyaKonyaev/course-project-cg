//
// Created by aa068 on 14.08.2022.
//

#ifndef OPENGLTEST_BASEFIGURE_H
#define OPENGLTEST_BASEFIGURE_H

#include "../Other/defines.h"
#include <vector>
#include <GL/gl.h>

class BaseFigure {
public:
    BaseFigure() = default;
    BaseFigure(BaseFigure &&figure) {
        _position = figure._position;
        _vertices = figure._vertices;
        _normals = figure._normals;
        _indexes = figure._indexes;
        _position = figure._position;
        _typeDisplay = figure._typeDisplay;
    };

    std::vector<GLfloat> getArrayVertices() { return _vertices; };
    std::vector<unsigned int> getArrayIndexes() { return _indexes; };
    std::vector<GLfloat> getArrayColors() { return _colors; };
    std::vector<GLfloat> getArrayNormals() { return _normals; };
    Point_t getPosition() { return _position; };
    double getTypeDisplay() { return _typeDisplay; };

    void setArrayVertices(std::vector<GLfloat> vertices) {  _vertices = vertices; };
    void setArrayIndexes(std::vector<unsigned int> indexes) {  _indexes = indexes; };
    void setArrayColors(std::vector<GLfloat> colors) {  _colors = colors; };
    void setArrayNormals(std::vector<GLfloat> normals) {  _normals = normals; };
    void setPosition(Point_t position) {  _position = position; };
    void setTypeDisplay(double typeDisplay) {  _typeDisplay = typeDisplay; };

    virtual ~BaseFigure() = 0;

protected:
    std::vector<GLfloat> _colors;
    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _normals;
    std::vector<unsigned int> _indexes;
    Point_t _position;
    double _typeDisplay;
};

#endif //OPENGLTEST_BASEFIGURE_H
