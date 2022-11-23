//
// Created by aa068 on 22.08.2022.
//

#ifndef OBJPARSER_PARSEROBJ_H
#define OBJPARSER_PARSEROBJ_H

#include "../Model/ModelObj.h"
#include <fstream>
#include <iostream>
#include <memory>

class ParserObj {
public:
    ParserObj();
    void setupParsingFile(std::string fileName);
    bool parseFile();
    std::vector<ModelObj> getModels();
    ModelObj getModel(size_t idx);

private:
    bool _isParsed;
    std::string _fileName;
    std::vector<ModelObj> _models;

    void skipLine(std::shared_ptr<std::ifstream> file);
    void rewindFile(std::shared_ptr<std::ifstream>file);

    void readModel(std::shared_ptr<std::ifstream> file);
    std::string readNameModel(std::shared_ptr<std::ifstream> file);
    std::vector<Point_t> readPointsModel(std::shared_ptr<std::ifstream> file);
    std::vector<PointTexture_t> readPointsTexture(std::shared_ptr<std::ifstream> file);
    std::vector<Normal_t> readNormals(std::shared_ptr<std::ifstream> file);
    std::vector<Surface_t> readSurfacesInfo(std::shared_ptr<std::ifstream> file);

};


#endif //OBJPARSER_PARSEROBJ_H
