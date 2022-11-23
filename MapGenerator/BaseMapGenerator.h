//
// Created by aa068 on 25.08.2022.
//

#ifndef MODIFIEDDIAMONDSQUARE_BASEMAPGENERATOR_H
#define MODIFIEDDIAMONDSQUARE_BASEMAPGENERATOR_H

#include <vector>
#include <memory>
#include <cmath>

class BaseMapGenerator {
public:
    explicit BaseMapGenerator(std::vector<std::vector<unsigned int>> colorMap);
    bool generateHeightMap();
    std::vector<std::vector<float>> getHeightMap();
    std::vector<std::vector<char>> getTerrainMap();
    void printHeightMapList();
    void printTerrainMapTable();
    void printTerrainMapList();

private:
    float maxHeightMap; //костыль
    std::vector<std::vector<unsigned int>> _colorMap;
    std::vector<std::vector<char>> _terrainMap;
    std::vector<std::vector<float>> _heightMap;

    void generateTerrainMap();
    std::vector<std::vector<float>> generateTmpHeightMap();
    static std::vector<std::vector<float>> generateHeightDiamondSquare(std::vector<std::vector<float>> map, float initialHeight, float maxDeltaHeight);
    void setTmpToOriginHeightMap(std::vector<std::vector<float>> tmpMap, char typeTerrain);
    void normalizeMap();
    void dolinezeMap();
};


#endif //MODIFIEDDIAMONDSQUARE_BASEMAPGENERATOR_H
