//====================================================================================
//	Simple demo program for reading and writing TGA image files.
//====================================================================================

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
//
#include "RasterImage.h"


//	Note that I completely hard-coded the file paths.  Obviously, you will
//	have to change that in your program.
#define IN_PATH		"../Images/Renoir.tga"
#define OUT_PATH	"../Output/output.tga"


#define	VERSION_1	1
#define	VERSION_2	2

//	Choose VERSION_1 or VERSION_2
#define VERSION		VERSION_2


int main(int argc, char** argv)
{
	//	Read the image from a TGA file
	RasterImage img = readImage(IN_PATH);

	unsigned int imgTotalBytes = img.height * img.bytesPerRow;
		
	//	I allocate a raster at the same dimensions as the image I just read
	unsigned char* rasterOut = (unsigned char*) calloc(imgTotalBytes, 1);

	#if VERSION == VERSION_2

			//Version 2:
		
			//I view my raster as an array of pixels stored on a 4-byte int.
			//I use boolean operators to kill the right channel
		int* pixelRasterIn = (int*) img.raster;
		int* pixelRasterOut = (int*) rasterOut;
	
	#endif
	
		//I do something simple with my image, before writing it back
		//For example, I "kill" the green channel of the image, so that
		//it will come out in magenta-ish tint.
	for (unsigned short i=0; i< img.height; i++)
	{
		for (unsigned short j=0; j< img.width; j++)
		{
				// Here I do the same operation in two different ways, because this might
				// give you some ideas on how to do your HDR calculations.  You can enable
				// either version by setting the #define with the proper value to verify
				// that they do the same thing.
			
			#if VERSION == VERSION_1

				// 	Version 1:  I view my raster as an array of unsigned char
				
				// 	Even though the image on-file has 24 bytes per pixel, we store in
				// 	memory as 4-bytes per pixel (because this aligns a pixel with the size of
				// 	an int.  This is where the factor 4 comes from
				// the color channel order is red-green-blue-alpha, hence the +1
				rasterOut[i*img.bytesPerRow + 4*j] = img.raster[i*img.bytesPerRow + 4*j];
				rasterOut[i*img.bytesPerRow + 4*j + 1] = 0;
				rasterOut[i*img.bytesPerRow + 4*j + 2] = img.raster[i*img.bytesPerRow + 4*j + 2];
				rasterOut[i*img.bytesPerRow + 4*j + 3] = img.raster[i*img.bytesPerRow + 4*j + 3];

			#elif VERSION == VERSION_2

				// 	Version 2:
				
				// 	I view my raster as an array of pixels stored on a 4-byte int.
				//  and access my pixel.  Note the absence of 4 factor, thanks to pointer algebra.
				 int* pixelIn = pixelRasterIn + i*img.width + j;
				 int* pixelOut = pixelRasterOut + i*img.width + j;
				// 	I use boolean operators to kill the right channel.  Note that x86 CPUs use
				// 	a little-endian ordering of int/float/etc, so I need to give my mask in
				// 	reverse order of what I intend to do in memory.  I want RGBA --> R0BA
				// 	set green to zero.  So my mask is written as follows:
				*pixelOut = (*pixelIn) & 0xFFFF00FF;
			
			#else
				#error invalid version setting
			#endif
		}
	}
	
	//	And we write back the modified image into the Output folder.
    int outErr = writeImage(OUT_PATH, &img);
    if (outErr !=0)
	{
		printf("Writing out of the image failed.\n");
	}
	
    // Print a brief summary detailing the results
    //
    printf("Done!\n");
    
	freeImage(&img);
	
    return 0;
}

