//
// Created by aa068 on 14.08.2022.
//

#include "Scene.h"

Scene::Scene() {
    _objects.resize(0);

    _cameras.resize(0);
    _cameras.push_back(std::make_shared<Camera>());

    _idxActiveCamera = 0;
}

void Scene::setActiveCamera(int idx) {
    if (idx >= 0 && idx < _cameras.size())
        _idxActiveCamera = idx;
}

void Scene::addFigureToScene(std::shared_ptr<BaseFigure> newFigure) {
    _objects.push_back(newFigure);
}
