//
// Created by aa068 on 24.08.2022.
//

#include "ModelObjConvertor.h"
#include "../Figures/GeneralFigure.h"

void ModelObjConvertor::setupModelObj(std::shared_ptr<ModelObj> model) {
    _modelObj = model;
}

void ModelObjConvertor::convertModel() {
    std::vector<Point_t> pointsObj = _modelObj->getPoints();
    std::vector<Normal_t> normalsObj = _modelObj->getNormals();

    std::vector<GLfloat> pointsConverted(0);
    std::vector<GLfloat> colorsConverted(0);
    std::vector<GLfloat> normalsConverted(0);
    std::vector<unsigned int> indexesConverted(0);

    unsigned int idx = 0;
    for (auto &surface: _modelObj->getSurfaces())
    {
        for (auto & point : surface.points)
        {
            pointsConverted.push_back(pointsObj[point.idxPoint].x);
            pointsConverted.push_back(pointsObj[point.idxPoint].y);
            pointsConverted.push_back(pointsObj[point.idxPoint].z);

            normalsConverted.push_back(normalsObj[point.idxNormal].x);
            normalsConverted.push_back(normalsObj[point.idxNormal].y);
            normalsConverted.push_back(normalsObj[point.idxNormal].z);

            colorsConverted.push_back(1);
            colorsConverted.push_back(0);
            colorsConverted.push_back(1);

            indexesConverted.push_back(idx++);
        }
    }

    _modelGl = std::make_shared<GeneralFigure>();

    _modelGl->setTypeDisplay(GL_TRIANGLES);
    _modelGl->setPosition(Point_t(0, 0, 0));
    _modelGl->setArrayVertices(pointsConverted);
    _modelGl->setArrayColors(colorsConverted);
    _modelGl->setArrayNormals(normalsConverted);
    _modelGl->setArrayIndexes(indexesConverted);

}

std::shared_ptr<BaseFigure> ModelObjConvertor::getModelGl() {
    return _modelGl;
}
