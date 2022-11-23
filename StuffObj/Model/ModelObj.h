//
// Created by aa068 on 22.08.2022.
//

#ifndef OBJPARSER_MODELOBJ_H
#define OBJPARSER_MODELOBJ_H

#include <vector>
#include <string>
#include "../../Other/defines.h"


class ModelObj {
public:
    size_t getAmountPoints() { return _points.size(); };
    std::vector<Point_t> getPoints() { return _points; };
    std::vector<PointTexture_t> getPointsTexture() { return _pointsTexture; };
    std::vector<Normal_t> getNormals() { return _normals; };
    std::vector<Surface_t> getSurfaces() { return _surfaces; };
    std::string getNameModel() { return _nameModel; };

    void setNameModel(std::string nameModel) { _nameModel = nameModel; };
    void setSurfaces(std::vector<Surface_t> surfaces) { _surfaces = surfaces; };
    void setNormals(std::vector<Normal_t> normals) { _normals = normals; };
    void setPointsTexture(std::vector<PointTexture_t> pointsTexture) { _pointsTexture = pointsTexture; };
    void setPoints(std::vector<Point_t> points) { _points = points; };

private:
    std::vector<Point_t> _points;
    std::vector<PointTexture_t> _pointsTexture;
    std::vector<Normal_t> _normals;
    std::vector<Surface_t> _surfaces;
    std::string _nameModel;
};


#endif //OBJPARSER_MODELOBJ_H
