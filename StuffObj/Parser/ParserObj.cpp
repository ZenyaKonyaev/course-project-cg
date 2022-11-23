//
// Created by aa068 on 22.08.2022.
//

#include "ParserObj.h"

ParserObj::ParserObj() {
    setupParsingFile("");
}

void ParserObj::setupParsingFile(std::string fileName) {
    _fileName = fileName;
    _isParsed = false;
    _models.resize(0);
}

std::vector<ModelObj> ParserObj::getModels() {
    if (_isParsed)
        return _models;
    return std::vector<ModelObj>();
}

bool ParserObj::parseFile() {
    if (_fileName.empty() || _isParsed)
        return false;

    std::shared_ptr<std::ifstream> filePtr = std::make_shared<std::ifstream>();
    filePtr->open(_fileName);

    if (!filePtr->is_open())
        return false;

    if (filePtr->eof()) {
        filePtr->close();
        return false;
    }

    //while (!filePtr->eof())
    readModel(filePtr);

    filePtr->close();

    _isParsed = true;

    return true;
}

void ParserObj::skipLine(std::shared_ptr<std::ifstream> file) {
    std::string str;
    std::getline(*file, str);
}

void ParserObj::rewindFile(std::shared_ptr<std::ifstream> file) {
    file->clear();
    file->seekg(0);
}

void ParserObj::readModel(std::shared_ptr<std::ifstream> file) {
    ModelObj modelObj;

    modelObj.setNameModel(readNameModel(file));
    modelObj.setPoints(readPointsModel(file));
    modelObj.setPointsTexture(readPointsTexture(file));
    modelObj.setNormals(readNormals(file));
    modelObj.setSurfaces(readSurfacesInfo(file));

    _models.push_back(modelObj);
}

std::string ParserObj::readNameModel(std::shared_ptr<std::ifstream> file) {
    std::string code;
    std::string nameModel;

    *file >> code;
    while(code != "o" && !file->eof()) {
        skipLine(file);
        *file >> code;
    }

    *file >> nameModel;

    rewindFile(file);

    return nameModel;
}

std::vector<Point_t> ParserObj::readPointsModel(std::shared_ptr<std::ifstream> file) {
    std::vector<Point_t> points(0);
    std::string code;
    Point_t pointTmp;

    *file >> code;
    while (code != "v" && !file->eof()) {
        skipLine(file);
        *file >> code;
    }

    while (code == "v" && !file->eof()) {
        *file >> pointTmp.x >> pointTmp.y >> pointTmp.z >> code;
        points.push_back(pointTmp);
    }

    rewindFile(file);

    return points;
}

std::vector<PointTexture_t> ParserObj::readPointsTexture(std::shared_ptr<std::ifstream> file) {
    std::vector<PointTexture_t> pointsTexture(0);
    std::string code;
    PointTexture_t pointTextureTmp;

    *file >> code;
    while (code != "vt" && !file->eof()) {
        skipLine(file);
        *file >> code;
    }

    while (code == "vt" && !file->eof()) {
        *file >> pointTextureTmp.u >> pointTextureTmp.v >> code;
        pointsTexture.push_back(pointTextureTmp);
    }

    rewindFile(file);

    return pointsTexture;
}

std::vector<Normal_t> ParserObj::readNormals(std::shared_ptr<std::ifstream> file) {
    std::vector<Normal_t> normals(0);
    std::string code;
    Normal_t normalTmp;

    *file >> code;
    while (code != "vn" && !file->eof()) {
        skipLine(file);
        *file >> code;
    }

    while (code == "vn" && !file->eof()) {
        *file >> normalTmp.x >> normalTmp.y >> normalTmp.z >> code;
        normals.push_back(normalTmp);
    }

    rewindFile(file);

    return normals;
}

static std::vector<std::string> splitStr(std::string strToSplit, std::string delimiter) //strToSplit must be trimmed from left and right
{
    std::vector<std::string> arrayTokens(0);
    std::string token;
    size_t pos = 0;

    while ((pos = strToSplit.find(delimiter)) != std::string::npos) {
        token = strToSplit.substr(0, pos);
        arrayTokens.push_back(token);
        strToSplit.erase(0, pos + delimiter.length());
    }
    arrayTokens.push_back(strToSplit);

    return arrayTokens;
}

std::vector<Surface_t> ParserObj::readSurfacesInfo(std::shared_ptr<std::ifstream> file) {
    std::vector<Surface_t> surfaces(0);
    std::string code;
    Surface_t surfaceTmp;
    PointSurface_t pointSurfaceTmp;

    *file >> code;
    while (code != "f" && !file->eof()) {
        skipLine(file);
        *file >> code;
    }

    while (code == "f" && !file->eof()) {
        surfaceTmp.points.resize(0);

        std::string strToParse;
        std::getline(*file, strToParse);
        strToParse.erase(0,1);

        std::vector<std::string> pointsSurfaceStr = splitStr(strToParse, " ");
        for (auto &point : pointsSurfaceStr)
        {
            std::vector<std::string> valuesStr = splitStr(point, "/");
            pointSurfaceTmp.idxPoint = std::stoi(valuesStr[0]) - 1;
            pointSurfaceTmp.idxPointTexture = std::stoi(valuesStr[1]) - 1;
            pointSurfaceTmp.idxNormal = std::stoi(valuesStr[2]) - 1;


            surfaceTmp.points.push_back(pointSurfaceTmp);
        }

        surfaces.push_back(surfaceTmp);
        *file >> code;
    }

    rewindFile(file);

    return surfaces;
}

ModelObj ParserObj::getModel(size_t idx) {
    if (idx >= _models.size())
        return ModelObj();
    return _models[idx];
}
