//
// Created by aa068 on 25.08.2022.
//

#include "BmpParser.h"

BmpParser::BmpParser(std::string fileName) {
    setFileName(fileName);
}

std::vector<std::vector<RGBQUAD_t>> BmpParser::getColorTable() {
    if (_parsed)
        return _colorTable;
    return std::vector<std::vector<RGBQUAD_t>>(0);
}

bool BmpParser::parseFile() {
    FILE * pFile = fopen(&(_fileName[0]), "rb");
    if (!pFile)
        return false;

    // считываем заголовок файла
    BITMAPFILEHEADER_t header;
    readHeaderFile(&header, pFile);


    // считываем заголовок изображения
    BITMAPINFOHEADER_t bmiHeader;
    readHeaderImage(&bmiHeader, pFile);

    _colorTable = std::vector<std::vector<RGBQUAD_t>>(bmiHeader.biHeight, std::vector<RGBQUAD_t>(bmiHeader.biWidth));

    for (int i = 0; i < bmiHeader.biHeight; i++) {
        for (int j = 0; j < bmiHeader.biWidth; j++) {
            _colorTable[i][j].rgbBlue = getc(pFile);
            _colorTable[i][j].rgbGreen = getc(pFile);
            _colorTable[i][j].rgbRed = getc(pFile);
        }

        // пропускаем последний байт в строке
        for (int j = 0; j < bmiHeader.biWidth % 4; ++j)
            getc(pFile);
    }

    //переворачиваем картинку
    for (int i = 0; i < bmiHeader.biHeight / 2; ++i) {
        for (int j = 0; j < bmiHeader.biWidth; ++j)
        {
            RGBQUAD_t tmp = _colorTable[i][j];
            _colorTable[i][j] = _colorTable[bmiHeader.biHeight - 1 - i][j];
            _colorTable[bmiHeader.biHeight - 1 - i][j] = tmp;
        }
    }

    fclose(pFile);
    _parsed = true;

    return true;
}

unsigned short BmpParser::read_u16(FILE *fp) {
    unsigned char b0, b1;

    b0 = getc(fp);
    b1 = getc(fp);

    return ((b1 << 8) | b0);
}

unsigned int BmpParser::read_u32(FILE *fp) {
    unsigned char b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

int BmpParser::read_s32(FILE *fp) {
    unsigned char b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

void BmpParser::readHeaderFile(BITMAPFILEHEADER_t *ptrHeaderStruct, FILE *ptrFile) {
    ptrHeaderStruct->bfType      = read_u16(ptrFile);
    ptrHeaderStruct->bfSize      = read_u32(ptrFile);
    ptrHeaderStruct->bfReserved1 = read_u16(ptrFile);
    ptrHeaderStruct->bfReserved2 = read_u16(ptrFile);
    ptrHeaderStruct->bfOffBits   = read_u32(ptrFile);
}

void BmpParser::readHeaderImage(BITMAPINFOHEADER_t *ptrHeaderStruct, FILE *ptrFile) {
    ptrHeaderStruct->biSize          = read_u32(ptrFile);
    ptrHeaderStruct->biWidth         = read_u32(ptrFile);
    ptrHeaderStruct->biHeight        = read_u32(ptrFile);
    ptrHeaderStruct->biPlanes        = read_u16(ptrFile);
    ptrHeaderStruct->biBitCount      = read_u16(ptrFile);
    ptrHeaderStruct->biCompression   = read_u32(ptrFile);
    ptrHeaderStruct->biSizeImage     = read_u32(ptrFile);
    ptrHeaderStruct->biXPelsPerMeter = read_u32(ptrFile);
    ptrHeaderStruct->biYPelsPerMeter = read_u32(ptrFile);
    ptrHeaderStruct->biClrUsed       = read_u32(ptrFile);
    ptrHeaderStruct->biClrImportant  = read_u32(ptrFile);
}

void BmpParser::printColorTable() {
    if (!_parsed)
        return;

    printf("width x height: (%d,%d)\n", _colorTable.size(), _colorTable.empty() ? 0 : _colorTable[0].size());
    for (int i = 0; i < _colorTable.size(); i++) {
        printf("%d row:\n", i + 1);
        for (int j = 0; j < _colorTable[i].size(); j++) {
            printf("%d pixel) R:%d G:%d B:%d\n", j + 1, _colorTable[i][j].rgbRed, _colorTable[i][j].rgbGreen, _colorTable[i][j].rgbBlue);
        }
        printf("\n");
    }
}

void BmpParser::setFileName(std::string fileName) {
    _fileName = fileName;
    _parsed = false;
    _colorTable.resize(0);
}

std::vector<std::vector<unsigned int>> BmpParser::getColorHex() {
    if (!_parsed)
        return std::vector<std::vector<unsigned int>>();

    std::vector<std::vector<unsigned int>> result = std::vector<std::vector<unsigned int>>(_colorTable.size(), std::vector<unsigned int>(_colorTable[0].size()));
    for (int i = 0; i < _colorTable.size(); ++i)
        for (int j = 0; j < _colorTable[0].size(); ++j)
            result[i][j] = _colorTable[i][j].rgbBlue + _colorTable[i][j].rgbGreen * 256 + _colorTable[i][j].rgbRed * 256 * 256;

    return result;
}


