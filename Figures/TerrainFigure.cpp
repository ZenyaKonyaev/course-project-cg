//
// Created by aa068 on 27.08.2022.
//

#include "TerrainFigure.h"

TerrainFigure::TerrainFigure(std::vector<std::vector<float>> heightMap, std::vector<std::vector<RGBQUAD_t>> colorTableHex, \
                             float xStart, float xEnd, float yStart, float yEnd) : _heightMap(heightMap) {
    //Fill arrays
    float deltaX = (xEnd - xStart) / _heightMap.size();
    float deltaY = (yEnd - yStart) / _heightMap[0].size();
    for (int i = 0; i < _heightMap.size() - 1; ++i) {
        for (int j = 0; j < _heightMap[i].size() - 1; ++j) {
            size_t vertSize = _vertices.size() / 3;

            _vertices.push_back(xStart + i * deltaX); _vertices.push_back(yStart + j * deltaY); _vertices.push_back(_heightMap[i][j]);
            _vertices.push_back(xStart + (i + 1) * deltaX); _vertices.push_back(yStart + j * deltaY); _vertices.push_back(_heightMap[i + 1][j]);
            _vertices.push_back(xStart + i * deltaX); _vertices.push_back(yStart + (j + 1) * deltaY); _vertices.push_back(_heightMap[i][j + 1]);
            _vertices.push_back(xStart + (i + 1) * deltaX); _vertices.push_back(yStart + (j + 1) * deltaY); _vertices.push_back(_heightMap[i + 1][j + 1]);

            _colors.push_back(colorTableHex[i][j].rgbRed / 255.0); _colors.push_back(colorTableHex[i][j].rgbGreen / 255.0); _colors.push_back(colorTableHex[i][j].rgbBlue / 255.0);
            _colors.push_back(colorTableHex[i + 1][j].rgbRed / 255.0); _colors.push_back(colorTableHex[i + 1][j].rgbGreen / 255.0); _colors.push_back(colorTableHex[i + 1][j].rgbBlue / 255.0);
            _colors.push_back(colorTableHex[i][j + 1].rgbRed / 255.0); _colors.push_back(colorTableHex[i][j + 1].rgbGreen / 255.0); _colors.push_back(colorTableHex[i][j + 1].rgbBlue / 255.0);
            _colors.push_back(colorTableHex[i + 1][j + 1].rgbRed / 255.0); _colors.push_back(colorTableHex[i + 1][j + 1].rgbGreen / 255.0); _colors.push_back(colorTableHex[i + 1][j + 1].rgbBlue / 255.0);


            _indexes.push_back(vertSize); _indexes.push_back(vertSize + 1); _indexes.push_back(vertSize + 2);
            _indexes.push_back(vertSize + 1); _indexes.push_back(vertSize + 2); _indexes.push_back(vertSize + 3);
        }
    }

    _position = Point_t{0, 0, 0};
    _typeDisplay = GL_TRIANGLES;
}
