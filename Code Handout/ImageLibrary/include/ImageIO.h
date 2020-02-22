#ifndef	IMAGE_IO_H
#define	IMAGE_IO_H

#include "RasterImage.h"

RasterImage readImage(char* filePath);
int writeImage(char* filePath, RasterImage* image);

#endif	//	IMAGE_IO_H
