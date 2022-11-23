//
// Created by aa068 on 13.08.2022.
//

#ifndef OPENGLTEST_DEFINES_H
#define OPENGLTEST_DEFINES_H

#include <vector>

struct vector_t {
    float x;
    float y;
    float z;

    vector_t() = default;
    vector_t(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

typedef struct vector_t Point_t, Normal_t, Vector_t, Angle_t, Color_t;

typedef struct {
    double u,v;
} PointTexture_t;

typedef struct {
    int idxPoint;
    int idxPointTexture;
    int idxNormal;
} PointSurface_t;

typedef struct {
    std::vector<PointSurface_t> points;
} Surface_t;

typedef struct
{
    unsigned int    bfType;
    unsigned long   bfSize;
    unsigned int    bfReserved1;
    unsigned int    bfReserved2;
    unsigned long   bfOffBits;
} BITMAPFILEHEADER_t;

typedef struct
{
    unsigned int    biSize;
    int             biWidth;
    int             biHeight;
    unsigned short  biPlanes;
    unsigned short  biBitCount;
    unsigned int    biCompression;
    unsigned int    biSizeImage;
    int             biXPelsPerMeter;
    int             biYPelsPerMeter;
    unsigned int    biClrUsed;
    unsigned int    biClrImportant;
} BITMAPINFOHEADER_t;

typedef struct
{
    int   rgbBlue;
    int   rgbGreen;
    int   rgbRed;
    int   rgbReserved;
} RGBQUAD_t;

#endif //OPENGLTEST_DEFINES_H
