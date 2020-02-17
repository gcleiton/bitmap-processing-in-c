#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>

#define NULL 0
#define HEADER_SIZE 54
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define BYTES_PER_PIXEL 3
#define DEFAULT_PATH "images/"
#define NORMAL  "\x1B[0m"
#define YELLOW  "\x1B[33m"

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

typedef struct PIXEL{
    BYTE blue, green, red;
} PIXEL;

extern const PIXEL paddPixel;

#pragma pack(push, 1)

typedef struct BITMAPFILEHEADER{
    WORD bfType;  // 2 bytes
    DWORD bfSize; // 4 bytes
    WORD bfReserved1; // 2 bytes
    WORD bfReserved2; // 2 bytes
    DWORD bfOffBits; // 4 bytes
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER{
    DWORD biSize;
    DWORD biWidth;
    DWORD biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    DWORD biXPelsPerMeter;
    DWORD biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER;

typedef struct IMAGE{
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    PIXEL **pixels;
} IMAGE;

#pragma pack(pop)

int getPadding(int width);

int getSizePixel();

int combLinear(BYTE blue, BYTE green, BYTE red);

BITMAPFILEHEADER loadBitmapFileHeader(FILE *file);

BITMAPINFOHEADER loadBitmapInfoHeader(FILE *file);

IMAGE readImage(FILE *file);

IMAGE copy(IMAGE image);

IMAGE rotate90DegreesRight(IMAGE image);

IMAGE rotate90DegreesLeft(IMAGE image);

IMAGE rotate180Degrees(IMAGE image);

IMAGE flipHorizontally(IMAGE image);

IMAGE flipVertically(IMAGE image);

IMAGE applyGrayscale(IMAGE image);

void writeToFile(FILE *file, IMAGE image);

#endif