#include "RasterImage.h"
#include <stdio.h>
#include <stdlib.h>

RasterImage newImage(unsigned short width, unsigned short height, ImageType type,
					 unsigned char wordSizeRowPadding)
{
    RasterImage * img = (RasterImage *)calloc(wordSizeRowPadding, (width * height) * sizeof(RasterImage));
    img->height = height;
    img->width = width;
    img->type = type;
    img->bytesPerRow = width * 4;
    if (type == RGBA32_RASTER || type == FLOAT_RASTER){
        img->bytesPerRow = width * 4;
        img->bytesPerPixel = 4;
    }
    else if(type == GRAY_RASTER){
        img->bytesPerRow = width * 4;
        img->bytesPerPixel = 1;
    }
    img->raster = (unsigned char*)malloc((width * height) * wordSizeRowPadding);
}