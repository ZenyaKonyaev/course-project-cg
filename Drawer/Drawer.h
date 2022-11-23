//
// Created by aa068 on 14.08.2022.
//

#ifndef OPENGLTEST_DRAWER_H
#define OPENGLTEST_DRAWER_H

#include "../Scene/Scene.h"
#include <GL/gl.h>

class Drawer {
public:
    Drawer() = default;
    explicit Drawer(std::shared_ptr<Scene> activeScene);
    void setActiveScene(std::shared_ptr<Scene> newActiveScene);
    void installScene();
    void drawScene();
    void unInstallScene();
    std::shared_ptr<Scene> getScene() { return _scene; }

private:
    std::shared_ptr<Scene> _scene;
};


#endif //OPENGLTEST_DRAWER_H
