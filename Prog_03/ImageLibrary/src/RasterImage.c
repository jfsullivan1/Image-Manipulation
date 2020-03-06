#include "RasterImage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ImageIO_TGA.h"

#define BYTES_RBGA 4
#define BYTES_GRAY 1
#define WORDSIZE 16

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

    img.raster = calloc((width * height), img.bytesPerPixel);
    img.raster2D = raster2D((char*)img.raster, img.height, img.width);
    (void)wordSizeRowPadding;

    return img;
}

RasterImage readImage(char* path){
    unsigned short width, height;
	ImageType imgType;
    char * extension = malloc(sizeof(char*));
    extension = strrchr(path, '.');
    char * trimmedExt = calloc(4, sizeof(char*)); // I found that I needed to trim the extension 
    for(int i = 0; i < 4; i++){                         // when the filepath ended with a quotation. (i.e, .tga")
        trimmedExt[i] = extension[i];
    }
    trimmedExt[4] = '\0';
    unsigned char* buffer;
    if(strcmp(trimmedExt, ".tga") == 0){
        FILE * tgaFile = fopen(path, "rb");
        if(tgaFile){
            buffer = readTGA(path, &width, &height, &imgType);
            RasterImage tgaImage = newImage(width, height, imgType, WORDSIZE);
            tgaImage.raster = buffer;
            return tgaImage;
        }
        else{
            printf("File not found at path: %s\n", path);
            exit(1);
        }
    }
    else{
        printf("Invalid file extension.");
        exit(1);
    }
}

int writeImage(char* path, RasterImage * img){

    // We can assume already that our image is a valid TGA because it's verified at readImage.
    writeTGA(path, img->raster, img->width, img->height, img->type);
    return 0;
}

void freeImage(RasterImage* img){
    free(img->raster);
    free(img->raster2D);
    free(img);
}

char** raster2D(char* s, unsigned int numRows, unsigned int numCols){
	char** raster2D = (char**)calloc((numRows), sizeof(char*));
	raster2D[0] = s;
	for(unsigned int i = 1; i < numRows; i++){
		raster2D[i] = raster2D[i-1] + numCols;
	}
	return raster2D;
}