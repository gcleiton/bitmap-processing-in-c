#include "../include/bitmap.h"
#include <stdio.h>
#include <stdlib.h>

const PIXEL paddPixel = {0, 0, 0};

int getPadding(int width){
    int padding = 0;
    while((width + padding) % 4){
        padding++;
    }

    return padding;
}

int getSizePixel(){
    return sizeof(struct PIXEL);
}

int combLinear(BYTE blue, BYTE green, BYTE red){
    int result;
    result = 0.11 * blue + 0.59 * green + 0.3 * red;
    
    return result;
}

BITMAPFILEHEADER loadBitmapFileHeader(FILE *file){
    BITMAPFILEHEADER fileHeader;
    fseek(file, 0, SEEK_SET);

    fread(&fileHeader.bfType, sizeof(WORD), 1, file);
    fread(&fileHeader.bfSize, sizeof(DWORD), 1, file);
    fread(&fileHeader.bfReserved1, sizeof(WORD), 1, file);
    fread(&fileHeader.bfReserved2, sizeof(WORD), 1, file);
    fread(&fileHeader.bfOffBits, sizeof(DWORD), 1, file);

    return fileHeader;
}

BITMAPINFOHEADER loadBitmapInfoHeader(FILE *file){
    BITMAPINFOHEADER infoHeader;
    fseek(file, 14, SEEK_SET);

    fread(&infoHeader.biSize, sizeof(DWORD), 1, file);
    fread(&infoHeader.biWidth, sizeof(DWORD), 1, file);
    fread(&infoHeader.biHeight, sizeof(DWORD), 1, file);
    fread(&infoHeader.biPlanes, sizeof(WORD), 1, file);
    fread(&infoHeader.biBitCount, sizeof(WORD), 1, file);
    fread(&infoHeader.biCompression, sizeof(DWORD), 1, file);
    fread(&infoHeader.biSizeImage, sizeof(DWORD), 1, file);
    fread(&infoHeader.biXPelsPerMeter, sizeof(DWORD), 1, file);
    fread(&infoHeader.biYPelsPerMeter, sizeof(DWORD), 1, file);
    fread(&infoHeader.biClrUsed, sizeof(DWORD), 1, file);
    fread(&infoHeader.biClrImportant, sizeof(DWORD), 1, file);

    return infoHeader;

}

IMAGE readImage(FILE *file){

    int width, height, padding, sizePixel, i, j;
    PIXEL **pixels;
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    IMAGE image;

    fileHeader = loadBitmapFileHeader(file);
    infoHeader = loadBitmapInfoHeader(file);

    width = infoHeader.biWidth;
    height = infoHeader.biHeight;

    image.fileHeader = fileHeader;
    image.infoHeader = infoHeader;

    padding = getPadding(width);

    sizePixel = getSizePixel(); 

    pixels = (struct PIXEL **)malloc(height * sizeof(struct PIXEL*));
    for(i = 0; i < height; i++){
        pixels[i] = (struct PIXEL *)malloc(width * sizeof(sizePixel));
    }

    if(pixels == NULL){
        printf("| AVISO | Memória insuficiente.");
        fclose(file);
        exit(1);
    }

    char tempPadding[4];

    for(i = 0; i < height; i++){
        for(j=0; j < width; j++){
            fread(&pixels[i][j], BYTES_PER_PIXEL, 1, file);
        }
        if(padding != 0){
            fread(&tempPadding, BYTES_PER_PIXEL, 1, file);
        }
    }

    image.pixels = pixels;

    return image;
}

IMAGE copy(IMAGE image){

    return image;
}

IMAGE rotate90DegreesRight(IMAGE image){

    IMAGE rotatedImage;
    PIXEL **rotatedPixels, **pixels = image.pixels;

    int width = image.infoHeader.biHeight;
    int height = image.infoHeader.biWidth;
    int sizePixel, i, j;

    sizePixel = getSizePixel();
    
    rotatedPixels = (struct PIXEL **)malloc(height * sizeof(struct PIXEL*));
    for(i = 0; i < height; i++){
        rotatedPixels[i] = (struct PIXEL *)malloc(width * sizeof(sizePixel));
    }

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            rotatedPixels[i][j] = pixels[j][height-1-i];
        }
    }

    rotatedImage.fileHeader = image.fileHeader;

    rotatedImage.infoHeader = image.infoHeader;
    rotatedImage.infoHeader.biWidth = width;
    rotatedImage.infoHeader.biHeight = height;

    rotatedImage.pixels = rotatedPixels;

    return rotatedImage;
}

IMAGE rotate90DegreesLeft(IMAGE image){
    
    IMAGE rotatedImage;
    PIXEL **rotatedPixels, **pixels = image.pixels;

    int width = image.infoHeader.biHeight;
    int height = image.infoHeader.biWidth;
    int sizePixel, i, j;

    sizePixel = getSizePixel();
    
    rotatedPixels = (struct PIXEL **)malloc(height * sizeof(struct PIXEL*));
    for(i = 0; i < height; i++){
        rotatedPixels[i] = (struct PIXEL *)malloc(width * sizeof(sizePixel));
    }

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            rotatedPixels[i][j] = pixels[width-1-j][i];
        }
    }

    rotatedImage.fileHeader = image.fileHeader;

    rotatedImage.infoHeader = image.infoHeader;
    rotatedImage.infoHeader.biWidth = width;
    rotatedImage.infoHeader.biHeight = height;

    rotatedImage.pixels = rotatedPixels;
    
    return rotatedImage;
}

IMAGE rotate180Degrees(IMAGE image){
    
    IMAGE rotatedImage;
    PIXEL **rotatedPixels, **pixels = image.pixels;

    int width = image.infoHeader.biWidth;
    int height = image.infoHeader.biHeight;
    int sizePixel, i, j;

    sizePixel = getSizePixel();
    
    rotatedPixels = (struct PIXEL **)malloc(height * sizeof(struct PIXEL*));
    for(i = 0; i < height; i++){
        rotatedPixels[i] = (struct PIXEL *)malloc(width * sizeof(sizePixel));
    }

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            rotatedPixels[i][j] = pixels[height-1-i][width-1-j];
        }
    }

    rotatedImage.fileHeader = image.fileHeader;

    rotatedImage.infoHeader = image.infoHeader;

    rotatedImage.pixels = rotatedPixels;

    return rotatedImage;
}

IMAGE flipHorizontally(IMAGE image){
    
    IMAGE flippedImage;
    PIXEL **flippedPixels, **pixels = image.pixels;

    int width = image.infoHeader.biWidth;
    int height = image.infoHeader.biHeight;
    int sizePixel, i, j;

    sizePixel = getSizePixel();
    
    flippedPixels = (struct PIXEL **)malloc(height * sizeof(struct PIXEL*));
    for(i = 0; i < height; i++){
        flippedPixels[i] = (struct PIXEL *)malloc(width * sizeof(sizePixel));
    }

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            flippedPixels[i][j] = pixels[i][width-1-j];
        }
    }

    flippedImage.fileHeader = image.fileHeader;

    flippedImage.infoHeader = image.infoHeader;

    flippedImage.pixels = flippedPixels;

    return flippedImage;
}

IMAGE flipVertically(IMAGE image){
    
    IMAGE flippedImage;
    PIXEL **flippedPixels, **pixels = image.pixels;

    int width = image.infoHeader.biWidth;
    int height = image.infoHeader.biHeight;
    int sizePixel, i, j;

    sizePixel = getSizePixel();
    
    flippedPixels = (struct PIXEL **)malloc(height * sizeof(struct PIXEL*));
    for(i = 0; i < height; i++){
        flippedPixels[i] = (struct PIXEL *)malloc(width * sizeof(sizePixel));
    }

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            flippedPixels[i][j] = pixels[height-1-i][j];
        }
    }

    flippedImage.fileHeader = image.fileHeader;

    flippedImage.infoHeader = image.infoHeader;

    flippedImage.pixels = flippedPixels;

    return flippedImage;
}

IMAGE applyGrayscale(IMAGE image){

    IMAGE appliedImage;
    PIXEL **grayscaledPixels, **pixels = image.pixels;
    
    int width = image.infoHeader.biWidth;
    int height = image.infoHeader.biHeight;
    int sizePixel, i, j;

    sizePixel = getSizePixel();
    
    grayscaledPixels = (struct PIXEL **)malloc(height * sizeof(struct PIXEL*));
    for(i = 0; i < height; i++){
        grayscaledPixels[i] = (struct PIXEL *)malloc(width * sizeof(sizePixel));
    }

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            grayscaledPixels[i][j].blue = combLinear(pixels[i][j].blue, pixels[i][j].green, pixels[i][j].red);
            grayscaledPixels[i][j].green = combLinear(pixels[i][j].blue, pixels[i][j].green, pixels[i][j].red);
            grayscaledPixels[i][j].red = combLinear(pixels[i][j].blue, pixels[i][j].green, pixels[i][j].red);
        }
    }

    appliedImage.fileHeader = image.fileHeader;

    appliedImage.infoHeader = image.infoHeader;

    appliedImage.pixels = grayscaledPixels;

    return appliedImage;
}

void writeToFile(FILE *file, IMAGE image){
    int i, padding;
    int width = image.infoHeader.biWidth;
    int height = image.infoHeader.biHeight;

    fwrite(&image.fileHeader, FILE_HEADER_SIZE, 1, file);
    fwrite(&image.infoHeader, INFO_HEADER_SIZE, 1, file);

    padding = getPadding(width);
    for(i = 0; i < height; i++){
        fwrite(image.pixels[i], width, BYTES_PER_PIXEL, file);
        fwrite(&paddPixel, padding, BYTES_PER_PIXEL, file);
    }

}