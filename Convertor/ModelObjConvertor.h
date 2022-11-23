//
// Created by aa068 on 24.08.2022.
//

#ifndef OPENGLTEST_MODELOBJCONVERTOR_H
#define OPENGLTEST_MODELOBJCONVERTOR_H

#include "../Figures/BaseFigure.h"
#include "../StuffObj/Model/ModelObj.h"
#include <memory>

class ModelObjConvertor {
public:
    ModelObjConvertor() = default;
    explicit ModelObjConvertor(std::shared_ptr<ModelObj> model) : _modelObj(model) {};
    void setupModelObj(std::shared_ptr<ModelObj> model);
    void convertModel();
    std::shared_ptr<BaseFigure> getModelGl();
    ~ModelObjConvertor() = default;
private:
    std::shared_ptr<BaseFigure> _modelGl;
    std::shared_ptr<ModelObj> _modelObj;
};


#endif //OPENGLTEST_MODELOBJCONVERTOR_H
