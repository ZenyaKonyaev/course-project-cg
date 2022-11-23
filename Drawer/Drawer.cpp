//
// Created by aa068 on 14.08.2022.
//

#include "Drawer.h"

Drawer::Drawer(std::shared_ptr<Scene> activeScene) {
    _scene = activeScene;
}

void Drawer::setActiveScene(std::shared_ptr<Scene> newActiveScene) {
    _scene = newActiveScene;
}

void Drawer::installScene() {
    //glLoadIdentity();
    //glFrustum(-1,1, -1,1, 2, 1500); //TODO: мб тоже параметры камеры?
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0,0,-2); //TODO: мб тоже параметры камеры?

    glClearColor(.0f, .0f, .0f, 0.0f);

    glEnable(GL_DEPTH_TEST);


//    glEnable(GL_LIGHTING);
//    glEnable(GL_NORMALIZE);
//    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_LIGHT0);


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
//    glEnableClientState(GL_NORMAL_ARRAY);
}

void Drawer::drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    std::vector<std::shared_ptr<BaseFigure>> objectsToDraw = _scene->getFigures();

    glPushMatrix();
    {
        glRotatef(_scene->getActiveCamera()->getAngle().x, 1, 0, 0);
        glRotatef(_scene->getActiveCamera()->getAngle().z, 0, 0, 1);
        glTranslatef(-_scene->getActiveCamera()->getPosition().x, -_scene->getActiveCamera()->getPosition().y, _scene->getActiveCamera()->getPosition().z);
        for (auto object : objectsToDraw) {
            std::vector<GLfloat> vertices = object->getArrayVertices();
            std::vector<GLfloat> colors = object->getArrayColors();
            std::vector<GLfloat> normals = object->getArrayNormals();
            std::vector<unsigned int> indexes = object->getArrayIndexes();

            glVertexPointer(3, GL_FLOAT, 0, &(vertices[0]));
            glNormalPointer(GL_FLOAT, 0, &(normals[0]));
            glColorPointer(3, GL_FLOAT, 0, &(colors[0]));

            glPushMatrix();
            {
                glTranslatef(object->getPosition().x, object->getPosition().y, object->getPosition().z);
                glDrawElements(object->getTypeDisplay(), indexes.size(), GL_UNSIGNED_INT, &(indexes[0]));
            }
            glPopMatrix();
        }
    }
    glPopMatrix();
}

void Drawer::unInstallScene() {
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
//    glDisableClientState(GL_NORMAL_ARRAY);

    glDisable(GL_DEPTH_TEST);

//    glDisable(GL_LIGHTING);
//    glDisable(GL_NORMALIZE);
//    glDisable(GL_COLOR_MATERIAL);
//    glDisable(GL_LIGHT0);
}
