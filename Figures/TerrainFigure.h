//
// Created by aa068 on 27.08.2022.
//

#ifndef OPENGLTEST_TERRAINFIGURE_H
#define OPENGLTEST_TERRAINFIGURE_H

#include "BaseFigure.h"
#include <vector>
#include "../Other/defines.h"

class TerrainFigure : public BaseFigure {
public:
    TerrainFigure(std::vector<std::vector<float>> heightMap, std::vector<std::vector<RGBQUAD_t>> colorTable, \
                    float xStart, float xEnd, float yStart, float yEnd);
private:
    std::vector<std::vector<float>> _heightMap;
};


#endif //OPENGLTEST_TERRAINFIGURE_H
