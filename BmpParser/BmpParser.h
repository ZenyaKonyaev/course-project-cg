//
// Created by aa068 on 25.08.2022.
//

#ifndef MODIFIEDDIAMONDSQUARE_BMPPARSER_H
#define MODIFIEDDIAMONDSQUARE_BMPPARSER_H

#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include "../Other/defines.h"

class BmpParser {
public:
    explicit BmpParser(std::string fileName);
    void setFileName(std::string fileName);
    bool parseFile();
    std::vector<std::vector<RGBQUAD_t>> getColorTable();
    std::vector<std::vector<unsigned int>> getColorHex();
    void printColorTable();
private:
    std::string _fileName;
    bool _parsed = false;
    std::vector<std::vector<RGBQUAD_t>> _colorTable;

    static unsigned short read_u16(FILE *fp);
    static unsigned int read_u32(FILE *fp);
    static int read_s32(FILE *fp);

    static void readHeaderFile(BITMAPFILEHEADER_t *ptrHeaderStruct, FILE *ptrFile);
    static void readHeaderImage(BITMAPINFOHEADER_t *ptrHeaderStruct, FILE *ptrFile);
};


#endif //MODIFIEDDIAMONDSQUARE_BMPPARSER_H
