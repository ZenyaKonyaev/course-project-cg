//
// Created by aa068 on 25.08.2022.
//

#include "BaseMapGenerator.h"
#include <iostream>

#define COLOR_BLUE 0x0000FF
#define COLOR_BROWN 0x804030
#define COLOR_GREEN 0x00FF00
#define COLOR_GRAY 0xBEBEBE
#define COLOR_DESERT 0xF5F5DC

#define TERRAIN_OCEAN 'O'
#define TERRAIN_FOREST 'F'
#define TERRAIN_PLAIN 'P'
#define TERRAIN_MOUNTAINS 'M'
#define TERRAIN_DESERT 'D'

#define EPS 1e-6

bool BaseMapGenerator::generateHeightMap() {
    generateTerrainMap();

    std::vector<std::vector<float>> tmpHeightMap = generateTmpHeightMap();
    typedef struct {
        char typeTerrain;
        float defaultHeight;
        float maxDeltaHeight;
    } TerrainEnumElement_t;
    std::vector<TerrainEnumElement_t> terrains = {TerrainEnumElement_t{'O', 0, 0.2},
                                                  TerrainEnumElement_t{'F', 10, 3},
                                                  TerrainEnumElement_t{'P', 10, 0.3},
                                                  TerrainEnumElement_t{'M', 80, 20},
                                                  TerrainEnumElement_t{'D', 40, 3}};

    for (auto &terrain: terrains)
    {
        tmpHeightMap = generateHeightDiamondSquare(tmpHeightMap, terrain.defaultHeight, terrain.maxDeltaHeight);
        {
            /*printf("%c:\n", terrain.typeTerrain);
            for (int i = 0; i < tmpHeightMap.size() &&  terrain.typeTerrain == 'M'; ++i)
            {
                printf("%d row:\n", i + 1);
                for (int j = 0; j < tmpHeightMap[i].size(); ++j)
                    printf("%d) %f\n", j + 1, tmpHeightMap[i][j]);
                printf("\n");
            }
            printf("\n");*/
        }

        setTmpToOriginHeightMap(tmpHeightMap, terrain.typeTerrain);
    }

    normalizeMap();
    dolinezeMap();


    return true;
}

BaseMapGenerator::BaseMapGenerator(std::vector<std::vector<unsigned int>> colorMap) : _colorMap(colorMap) {
    _terrainMap = std::vector<std::vector<char>>(colorMap.size(), std::vector<char>(colorMap[0].size()));
    _heightMap = std::vector<std::vector<float>>(colorMap.size(), std::vector<float>(colorMap[0].size()));
}

std::vector<std::vector<float>> BaseMapGenerator::getHeightMap() {
    return _heightMap;
}

char chooseTerrainType(unsigned int color)
{
    if (fabs(color - COLOR_BLUE) <= EPS)
        return TERRAIN_OCEAN;
    if (fabs(color - COLOR_BROWN) <= EPS)
        return TERRAIN_FOREST;
    if (fabs(color - COLOR_GREEN) <= EPS)
        return TERRAIN_PLAIN;
    if (fabs(color - COLOR_GRAY) <= EPS)
        return TERRAIN_MOUNTAINS;
    if (fabs(color - COLOR_DESERT) <= EPS)
        return TERRAIN_DESERT;
    return '-';
}

void BaseMapGenerator::generateTerrainMap() {
    for (int i = 0; i < _colorMap.size(); ++i)
        for (int j = 0; j < _colorMap[i].size(); ++j)
            _terrainMap[i][j] = chooseTerrainType(_colorMap[i][j]);
}

std::vector<std::vector<char>> BaseMapGenerator::getTerrainMap() {
    return _terrainMap;
}

std::vector<std::vector<float>> BaseMapGenerator::generateTmpHeightMap() {
    size_t maxDimension = _terrainMap.size() > _terrainMap[0].size() ? _terrainMap.size() : _terrainMap[0].size();
    maxDimension--; //карта не может быть слишком маленькой
    if (fabs(log2(maxDimension) - int(log2(maxDimension))) <= EPS) //размер карты был 2^n + 1
        maxDimension++;
    else
        maxDimension = pow(2, int(log2(maxDimension)) + 1) + 1;

    std::vector<std::vector<float>> tmpHeightMap = std::vector<std::vector<float>>(maxDimension, std::vector<float>(maxDimension));
    return tmpHeightMap;
}

void setMiddleRandomNumberToTable(float *tableElement, float valueFirst, float valueSecond, float valueThird, float valueFourth, float maxDeltaRnd)
{
    if (!tableElement)
        return;

    int sign = -1 + rand() % 2 * 2;
    float rnd = rand() / float(RAND_MAX) * maxDeltaRnd * sign;
    float resValue = (valueFirst + valueSecond + valueThird + valueFourth) / 4 + rnd;

    *tableElement =  resValue >= 0 ? resValue : 0;
}

std::vector<std::vector<float>>
BaseMapGenerator::generateHeightDiamondSquare(std::vector<std::vector<float>> map, float initialHeight,
                                              float maxDeltaHeight) {
    int w = map.size(); //square, w = h
    int iterations = 1;

    map[0][0] = map[w - 1][0] = map[0][w - 1] = map[w - 1][w - 1] = initialHeight;


    while(w > 2)
    {
        //square step
        for (int i = 0; i < iterations; ++i) {
            for (int j = 0; j < iterations; ++j) {
                float leftTopValue = map[i * (w - 1)][j * (w - 1)];
                float leftBottomValue = map[(i + 1) * (w - 1)][j * (w - 1)];
                float rightTopValue = map[i * (w - 1)][(j + 1) * (w - 1)];
                float rightBottomValue = map[(i + 1) * (w - 1)][(j + 1) * (w - 1)];
                setMiddleRandomNumberToTable(&(map[(w / 2) + (w - 1) * i][(w / 2) + (w - 1) * j]), leftBottomValue, leftTopValue, rightBottomValue, rightTopValue, maxDeltaHeight);
            }
        }

        //diamond step
        for (int i = 0; i < iterations; ++i) {
            for (int j = 0; j < iterations; ++j) {
                float leftTopValue = map[i * (w - 1)][j * (w - 1)];
                float leftBottomValue = map[(i + 1) * (w - 1)][j * (w - 1)];
                float rightTopValue = map[i * (w - 1)][(j + 1) * (w - 1)];
                float rightBottomValue = map[(i + 1) * (w - 1)][(j + 1) * (w - 1)];
                float centerValue = map[(w / 2) + (w - 1) * i][(w / 2) + (w - 1) * j];

                float topCenterValue = (w / 2) + (w - 1) * (i - 1) > 0 ? map[(w / 2) + (w - 1) * (i - 1)][(w / 2) + (w - 1) * j] : initialHeight;
                float bottomCenterValue = (w / 2) + (w - 1) * (i + 1) < map.size() ? map[(w / 2) + (w - 1) * (i + 1)][(w / 2) + (w - 1) * j] : initialHeight;
                float leftCenterValue = (w / 2) + (w - 1) * (j - 1) > 0 ? map[(w / 2) + (w - 1) * i][(w / 2) + (w - 1) * (j - 1)] : initialHeight;
                float rightCenterValue = (w / 2) + (w - 1) * (j + 1) < map.size() ? map[(w / 2) + (w - 1) * i][(w / 2) + (w - 1) * (j + 1)] : initialHeight;

                //midTop
                setMiddleRandomNumberToTable(&(map[i * (w - 1)][(w / 2) + (w - 1) * j]), centerValue, leftTopValue, rightTopValue, topCenterValue, maxDeltaHeight);
                //midLeft
                setMiddleRandomNumberToTable(&(map[(w / 2) + (w - 1) * i][j * (w - 1)]), centerValue, leftTopValue, leftBottomValue, leftCenterValue, maxDeltaHeight);
                //midBottom
                setMiddleRandomNumberToTable(&(map[(i + 1) * (w - 1)][(w / 2) + (w - 1) * j]), centerValue, leftBottomValue, rightBottomValue, bottomCenterValue, maxDeltaHeight);
                //midRight
                setMiddleRandomNumberToTable(&(map[(w / 2) + (w - 1) * i][(j + 1) * (w - 1)]), centerValue, rightTopValue, rightBottomValue, rightCenterValue, maxDeltaHeight);
            }
        }

        w = w / 2 + 1;
        iterations *= 2;
    }

    return map;
}

void BaseMapGenerator::setTmpToOriginHeightMap(std::vector<std::vector<float>> tmpMap, char typeTerrain) {
    for (int i = 0; i < _heightMap.size(); ++i)
        for (int j = 0; j < _heightMap[i].size(); ++j)
            _heightMap[i][j] = typeTerrain == _terrainMap[i][j] ? tmpMap[i][j] : _heightMap[i][j];
}

void BaseMapGenerator::normalizeMap() {
    float zMin = 1000, zMax = -1000;
    for (auto &row : _heightMap)
    {
        for (auto &element : row)
        {
            if (element > zMax)
                zMax = element;
            if (element < zMin)
                zMin = element;
        }
    }

    maxHeightMap = zMax;

    for (int i = 0; i < _heightMap.size(); ++i)
        for (int j = 0; j < _heightMap[i].size(); ++j)
            _heightMap[i][j] = (_heightMap[i][j] - zMin) / (zMax - zMin);
}

void BaseMapGenerator::dolinezeMap() {
    for (auto &row : _heightMap)
        for (auto &element : row)
            element = sqrt(element) * maxHeightMap;
}

void BaseMapGenerator::printHeightMapList() {
    printf("HeightMapList:\n");
    for (int i = 0; i < _heightMap.size(); ++i)
    {
        printf("%d row:\n", i + 1);
        for (int j = 0; j < _heightMap[i].size(); ++j)
            printf("%d) %f\n", j + 1, _heightMap[i][j]);
        printf("\n");
    }
    printf("\n");
}

void BaseMapGenerator::printTerrainMapTable() {
    printf("TerrainMapTable:\n");
    for (int i = 0; i < _terrainMap.size(); ++i)
    {
        printf("%d row:\n", i + 1);
        for (int j = 0; j < _terrainMap[i].size(); ++j)
            printf("%d) %f\n", j + 1, _terrainMap[i][j]);
        printf("\n");
    }
    printf("\n");
}

void BaseMapGenerator::printTerrainMapList() {
    printf("TerrainMapList:\n");
    for (auto &row : _terrainMap)
    {
        for (auto &element : row)
            printf("%c ", element);
        printf("\n");
    }
    printf("\n");
}






























/*
 * int w = map.size(); //square, w = h
    int iterations = 1;

    map[0][0] = map[w - 1][0] = map[0][w - 1] = map[w - 1][w - 1] = initialHeight;

    //square step
    while(w > 2)
    {
        for (int i = 0; i < iterations; ++i) {
            for (int j = 0; j < iterations; ++j) {
                float leftTopValue = map[i * (w - 1)][j * (w - 1)];
                float leftBottomValue = map[(i + 1) * (w - 1)][j * (w - 1)];
                float rightTopValue = map[i * (w - 1)][(j + 1) * (w - 1)];
                float rightBottomValue = map[(i + 1) * (w - 1)][(j + 1) * (w - 1)];
                float rnd = rand() / float(RAND_MAX) * maxDeltaHeight;
                map[(w / 2) + (w - 1) * i][(w / 2) + (w - 1) * j] = (leftBottomValue + leftTopValue + rightBottomValue + rightTopValue) / 4 + rnd;
            }
        }
        w = w / 2 + 1;
        iterations *= 2;
    }

    //diamond step
    iterations = 1;
    w = map.size();
    while(w > 2)
    {
        for (int i = 0; i < iterations; ++i) {
            for (int j = 0; j < iterations; ++j) {
                float leftTopValue = map[i * (w - 1)][j * (w - 1)];
                float leftBottomValue = map[(i + 1) * (w - 1)][j * (w - 1)];
                float rightTopValue = map[i * (w - 1)][(j + 1) * (w - 1)];
                float rightBottomValue = map[(i + 1) * (w - 1)][(j + 1) * (w - 1)];
                float centerValue = map[(w / 2) + (w - 1) * i][(w / 2) + (w - 1) * j];

                float topCenterValue = (w / 2) + (w - 1) * (i - 1) > 0 ? map[(w / 2) + (w - 1) * (i - 1)][(w / 2) + (w - 1) * j] : initialHeight;
                float bottomCenterValue = (w / 2) + (w - 1) * (i + 1) < map.size() ? map[(w / 2) + (w - 1) * (i + 1)][(w / 2) + (w - 1) * j] : initialHeight;
                float leftCenterValue = (w / 2) + (w - 1) * (j - 1) > 0 ? map[(w / 2) + (w - 1) * i][(w / 2) + (w - 1) * (j - 1)] : initialHeight;
                float rightCenterValue = (w / 2) + (w - 1) * (j + 1) < map.size() ? map[(w / 2) + (w - 1) * i][(w / 2) + (w - 1) * (j + 1)] : initialHeight;

                //midTop
                float rnd = rand() / float(RAND_MAX) * maxDeltaHeight;
                map[i * (w - 1)][(w / 2) + (w - 1) * j] = (centerValue + leftTopValue + rightTopValue + topCenterValue) / 4 + rnd;
                //midLeft
                map[(w / 2) + (w - 1) * i][j * (w - 1)] = (centerValue + leftTopValue + leftBottomValue + leftCenterValue) / 4 + rnd;
                //midBottom
                map[(i + 1) * (w - 1)][(w / 2) + (w - 1) * j] = (centerValue + leftBottomValue + rightBottomValue + bottomCenterValue) / 4 + rnd;
                //midRight
                map[(w / 2) + (w - 1) * i][(j + 1) * (w - 1)] = (centerValue + rightTopValue + rightBottomValue + rightCenterValue) / 4 + rnd;
             }
        }
        w = w / 2 + 1;
        iterations *= 2;
    }

    return map;
 */


