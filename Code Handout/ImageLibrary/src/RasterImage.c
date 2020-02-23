#include "RasterImage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ImageIO_TGA.h"

#define BYTES_RBGA 4
#define BYTES_GRAY 1
#define WORDSIZE 16

void readImage(char* path, unsigned short* width, unsigned short* height, ImageType imgType);
void writeImage(char* path);

RasterImage newImage(unsigned short width, unsigned short height, ImageType type,
					 unsigned char wordSizeRowPadding)
{
    RasterImage * img = (RasterImage *)malloc((width * height) * sizeof(RasterImage) * wordSizeRowPadding);
    img->height = height;
    img->width = width;
    img->type = type;
    img->bytesPerRow = width * 4;

    // with colored images we need 4 bytes per pixel. (RBGA)
    switch(type){
        case RGBA32_RASTER:
            img->bytesPerRow = width * 4;
            img->bytesPerPixel = BYTES_RBGA;
            break;
        case FLOAT_RASTER:
            img->bytesPerRow = width * 4;
            img->bytesPerPixel = BYTES_RBGA;
            break;
        case GRAY_RASTER:
            img->bytesPerRow = width * 4;
            img->bytesPerPixel = BYTES_GRAY;
            break;
        default:
            printf("Raster not supported");
            exit(1);
    }

    (unsigned char*)img->raster = (unsigned char*)malloc((width * height) * wordSizeRowPadding);
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            unsigned char* rgba = (unsigned char*)img->raster + img->bytesPerPixel*(i*height + j);
            rgba = (unsigned char*)malloc(img->bytesPerPixel);
        }
    }
    
    return *img;
}

void readImage(char* path, unsigned short* width, unsigned short* height, ImageType imgType){
    char extension = strrchr(path, '.');
    unsigned char* buffer;
    if(extension == ".tga"){
        FILE * tgaFile = fopen(path, "rb");
        if(tgaFile){
            buffer = readTGA(path, &width, &height, &imgType);
            RasterImage tgaImage = newImage(&width, &height, &imgType, WORDSIZE);
        }
    }
}

void writeImage(FILE* path){

}

void freeImage(RasterImage* img){

}

