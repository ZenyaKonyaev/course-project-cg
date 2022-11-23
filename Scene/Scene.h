//
// Created by aa068 on 14.08.2022.
//

#ifndef OPENGLTEST_SCENE_H
#define OPENGLTEST_SCENE_H

#include "../Figures/BaseFigure.h"
#include "../Camera/Camera.h"
#include <memory>

class Scene {
public:
    Scene();
    void setActiveCamera(int idx);
    void addFigureToScene(std::shared_ptr<BaseFigure> newFigure);
    std::vector<std::shared_ptr<BaseFigure>> getFigures() { return _objects; };
    std::shared_ptr<Camera> getActiveCamera() { return _cameras[_idxActiveCamera]; };
    ~Scene() = default;
    //TODO: removeFigureFromScene
private:
    std::vector<std::shared_ptr<BaseFigure>> _objects;
    std::vector<std::shared_ptr<Camera>> _cameras;
    int _idxActiveCamera;
};


#endif //OPENGLTEST_SCENE_H
