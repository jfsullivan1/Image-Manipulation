//==================================================================/
//                          Utilities.c                             /
// This program houses all of my utility functions that perform     /
//              operations on RasterImage objects.                  /
//          Written by John Sullivan for CSC412 at URI.             /
//==================================================================/    

#include <stdlib.h>
#include <stdio.h>
#include <libgen.h> //Linux ONLY!!!
#include <utilities.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

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

    RasterImage cropImg = newImage(newWidth, newHeight, img.type, 0);
    unsigned char* rasterOut = (unsigned char*) calloc(cropImg.bytesPerRow * cropImg.height + 4, 4);
    int k = 0;
    for (unsigned short i=img.height-y2; i<= img.height - y1; i++)
	{
	    int l = 0;
	    for (unsigned short j=x1; j<= x2 ; j++)
        {
                rasterOut[k*cropImg.bytesPerRow + 4*l] = rasterIn[(i+y1)*img.bytesPerRow + 4*(j+x1)];
                rasterOut[k*cropImg.bytesPerRow + 4*l + 1] = rasterIn[(i+y1)*img.bytesPerRow + 4*(j+x1) + 1];
                rasterOut[k*cropImg.bytesPerRow + 4*l + 2] = rasterIn[(i+y1)*img.bytesPerRow + 4*(j+x1) + 2];
                rasterOut[k*cropImg.bytesPerRow + 4*l + 3] = rasterIn[(i+y1)*img.bytesPerRow + 4*(j+x1) + 3];
		l++;
        }
	k++;
    }

    // We cast this back to a void* for consistency
    rasterOut = (void*)rasterOut;
    cropImg.raster = rasterOut;
    return cropImg;
}

//=================================================================/
//                            MIRRORV                              /
//=================================================================/
RasterImage mirrorV(RasterImage img){
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
RasterImage mirrorH(RasterImage img){
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
int comp(RasterImage imgOne, RasterImage imgTwo){
    unsigned char* rasterOne = (unsigned char*)imgOne.raster;
    unsigned char* rasterTwo = (unsigned char*)imgTwo.raster;
    int flag = 1;

    if (imgOne.height != imgTwo.height || imgOne.width != imgTwo.width || imgOne.type != imgTwo.type){
        return 1;
    }

    for (unsigned short i=0; i< imgOne.height; i++)
	{
        if(flag == 0){
            return 1;
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
        return 1;
    }

    if(flag == 1){
        return 0;
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
    char* base = basename(path); //from libgen.h
    char* fName = strtok(base, "."); //gets everything before the .tga

    char* newPath = malloc(strlen(outputDir) + strlen(fName) + 7 + strlen(type));

    if(needsSlash)
        sprintf(newPath, "%s/%s [%s].tga", outputDir, fName, type);
    else
        sprintf(newPath, "%s%s [%s].tga", outputDir, fName, type);

    return newPath;
}

//=================================================================/
//                       DOESDIRECTORYEXIST                        /
//=================================================================/
int doesDirectoryExist(char* path){
	struct stat dir;
	stat(path, &dir);
	if (S_ISDIR(dir.st_mode))
		return 1;
	return 0;
}

