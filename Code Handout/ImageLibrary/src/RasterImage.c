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
    RasterImage img;
    img.height = height;
    img.width = width;
    img.type = type;

    // with colored images we need 4 bytes per pixel. (RBGA)
    switch(type){
        case RGBA32_RASTER:
            img.bytesPerPixel = BYTES_RBGA;
            break;

        // I assign RBGA bytes per pixel here because a float is also 4 bytes. 
        case FLOAT_RASTER:
            img.bytesPerPixel = BYTES_RBGA;
            break;
        case GRAY_RASTER:
            img.bytesPerPixel = BYTES_GRAY;
            break;
        default:
            printf("Raster not supported");
            exit(1);
    }
    img.bytesPerRow = (img.bytesPerPixel * width);

    img.raster = (void*)calloc((width * height), img.bytesPerPixel);
    

    return img;
}

void readImage(char* path, unsigned short* width, unsigned short* height, ImageType imgType){
    char * extension = strrchr(path, '.');
    unsigned char* buffer;
    if(extension == ".tga"){
        FILE * tgaFile = fopen(path, "rb");
        if(tgaFile){
            buffer = readTGA(path, width, height, &imgType);
            RasterImage tgaImage = newImage(*width, *height, imgType, WORDSIZE);
        }
    }
}

void writeImage(char* path){

}

void freeImage(RasterImage* img){

}

