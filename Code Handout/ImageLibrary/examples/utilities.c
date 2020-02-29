//==================================================================/
//                          Utilities.c                             /
// This program houses all of my utility functions that perform     /
//              operations on RasterImage objects.                  /
//          Written by John Sullivan for CSC412 at URI.             /
//==================================================================/    

#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <utilities.h>
#include <string.h>

//=================================================================/
//                             GRAY                                /
//=================================================================/
RasterImage gray(RasterImage img){
    float sum = 0;
    float average = 0;
    unsigned char* rasterIn = (unsigned char*)img.raster;
    RasterImage grayImg = newImage(img.width, img.height, img.type, 0);
    unsigned char* rasterOut = (unsigned char*) calloc(img.bytesPerRow * img.height, 1);
    
    //  We'll take the sum of all the color channel values at a pixel, get the average, 
    //  and assign each color channel that average value.
    for (unsigned short i=0; i< img.height; i++)
	{
	    for (unsigned short j=0; j< img.width; j++)
        {
            sum = rasterIn[i*img.bytesPerRow + 4*j] + rasterIn[i*img.bytesPerRow + 4*j + 1] + 
                rasterIn[i*img.bytesPerRow + 4*j + 2];
            average = sum / 3;
            rasterOut[i*img.bytesPerRow + 4*j] = average;
            rasterOut[i*img.bytesPerRow + 4*j + 1] = average;
            rasterOut[i*img.bytesPerRow + 4*j + 2] = average;
        }
    }
    rasterOut = (void*)rasterOut;
    grayImg.raster = rasterOut;
    return grayImg;
}


//=================================================================/
//                             CROP                                /
//=================================================================/
RasterImage crop(RasterImage img, int x1, int y1, int x2, int y2){
    unsigned char* rasterIn = (unsigned char*)img.raster;
    unsigned short newHeight = y2 - y1;
    unsigned short newWidth = x2 - x1;

    // TGA images are read upside-down so we'll first mirror the image vertically.
    RasterImage cropImg = newImage(newWidth, newHeight, img.type, 0);
    RasterImage mirror = mirrorV(cropImg);
    unsigned char* rasterOut = (unsigned char*) calloc(cropImg.bytesPerRow * cropImg.height, 4);
    
    // Read from the original (mirrored) image dimensions at specified x and y values, and copy into a new raster.
    for (unsigned short i=0; i< img.height; i++)
	{
	    for (unsigned short j=0; j< img.width; j++)
        {
                rasterOut[i*mirror.bytesPerRow + 4*j] = rasterIn[(i+y1)*img.bytesPerRow + 4*(j+x1)];
                rasterOut[i*mirror.bytesPerRow + 4*j + 1] = rasterIn[(i+y1)*img.bytesPerRow + 4*(j+x1) + 1];
                rasterOut[i*mirror.bytesPerRow + 4*j + 2] = rasterIn[(i+y1)*img.bytesPerRow + 4*(j+x1) + 2];
                rasterOut[i*mirror.bytesPerRow + 4*j + 3] = rasterIn[(i+y1)*img.bytesPerRow + 4*(j+x1) + 3];
        }
    }

    // Now that we're done performing our crop, we can mirror the image back to return.
    RasterImage mirrorTwo = mirrorV(mirror);

    // We cast this back to a void* for consistency
    rasterOut = (void*)rasterOut;
    mirrorTwo.raster = rasterOut;
    freeImage(&mirror);
    freeImage(&cropImg);
    return mirrorTwo;
}

//=================================================================/
//                            MIRRORV                              /
//=================================================================/
RasterImage mirrorH(RasterImage img){
    unsigned char* rasterIn = (unsigned char*)img.raster;
    RasterImage mirrorImage = newImage(img.width, img.height, img.type, 0);
    unsigned char* rasterOut = (unsigned char*) calloc(img.bytesPerRow * img.height, 4);
    for (unsigned short i=0; i< img.height; i++)
	{
	    for (unsigned short j=0; j< img.width; j++)
        {
            rasterOut[i*img.bytesPerRow + 4*j] = rasterIn[(img.height-i)*img.bytesPerRow + 4*j];
            rasterOut[i*img.bytesPerRow + 4*j + 1] = rasterIn[(img.height-i)*img.bytesPerRow + 4*j + 1];
            rasterOut[i*img.bytesPerRow + 4*j + 2] = rasterIn[(img.height-i)*img.bytesPerRow + 4*j + 2];
            rasterOut[i*img.bytesPerRow + 4*j + 3] = rasterIn[(img.height-i)*img.bytesPerRow + 4*j + 3];
        }
    }
    rasterOut = (void*)rasterOut;
    mirrorImage.raster = rasterOut;
    return mirrorImage;
}

//=================================================================/
//                            MIRRORH                              /
//=================================================================/
RasterImage mirrorV(RasterImage img){
    unsigned char* rasterIn = (unsigned char*)img.raster;
    RasterImage mirrorImage = newImage(img.width, img.height, img.type, 0);
    unsigned char* rasterOut = (unsigned char*) calloc(img.bytesPerRow * img.height, 4);
    for (unsigned short i=0; i< img.height; i++)
	{
	    for (unsigned short j=0; j< img.width; j++)
        {
            rasterOut[i*img.bytesPerRow + 4*j] = rasterIn[i*img.bytesPerRow + 4*(img.width - j)];
            rasterOut[i*img.bytesPerRow + 4*j + 1] = rasterIn[i*img.bytesPerRow + 4*(img.width - j) + 1];
            rasterOut[i*img.bytesPerRow + 4*j + 2] = rasterIn[i*img.bytesPerRow + 4*(img.width - j) + 2];
            rasterOut[i*img.bytesPerRow + 4*j + 3] = rasterIn[i*img.bytesPerRow + 4*(img.width - j) + 3];
        }
    }
    rasterOut = (void*)rasterOut;
    mirrorImage.raster = rasterOut;
    return mirrorImage;
}

//=================================================================/
//                             COMP                                /
//=================================================================/
void comp(RasterImage imgOne, RasterImage imgTwo){
    unsigned char* rasterOne = (unsigned char*)imgOne.raster;
    unsigned char* rasterTwo = (unsigned char*)imgTwo.raster;
    int flag = 1;

    if (imgOne.height != imgTwo.height || imgOne.width != imgTwo.width || imgOne.type != imgTwo.type){
        exit(1);
    }

    for (unsigned short i=0; i< imgOne.height; i++)
	{
        if(flag == 0){
            exit(1);
        }
	    for (unsigned short j=0; j< imgOne.width; j++)
        {
            if((rasterTwo[i*imgTwo.bytesPerRow + 4*j] != rasterOne[i*imgOne.bytesPerRow + 4*j]) ||
               (rasterTwo[i*imgTwo.bytesPerRow + 4*j + 1] != rasterOne[i*imgOne.bytesPerRow + 4*j + 1]) ||
               (rasterTwo[i*imgTwo.bytesPerRow + 4*j + 2] != rasterOne[i*imgOne.bytesPerRow + 4*j + 2]) ||
               (rasterTwo[i*imgTwo.bytesPerRow + 4*j + 3] != rasterOne[i*imgOne.bytesPerRow + 4*j + 3]))
                    flag = 0;
        }
    }
    if(flag == 0){
        exit(1);
    }

    if(flag == 1){
        exit(0);
    }
}

//=================================================================/
//                          MAKENEWPATH                            /
//=================================================================/
char* makeNewPath(char* path, char* outputDir, char* type){
    int needsSlash = 0;
    if(outputDir[strlen(outputDir) -1] != '/'){
        needsSlash = 1;
    }
    char* base = basename(path);
    char* fName = strtok(base, ".");

    char* newPath = malloc(strlen(outputDir) + strlen(fName) + 7 + strlen(type));

    if(needsSlash)
        sprintf(newPath, "%s/%s [%s].tga", outputDir, fName, type);
    else
        sprintf(newPath, "%s%s [%s].tga", outputDir, fName, type);

    return newPath;
}