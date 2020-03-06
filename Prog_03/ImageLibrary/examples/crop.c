#include <stdio.h>
#include <stdlib.h>
#include <utilities.h>
#include <sys/stat.h>

/** CROP.C
 *  this program will crop an image using the crop utility function in utilities.h
 */

void checkDimensions(int x1, int x2, int y1, int y2, RasterImage img);

int main(int argc, char* argv[]){
    if(argc != 7){
        printf("Invalid number of arguments. Usage: ./crop <filePath> <filePath> <x,y> <x,y>\n");
        printf("CROP ARGS: %d\n", argc);
        for(int i = 0; i < argc; i++){
            printf("ARGV ARGS %d: %s\n", i, argv[i]);
        }
        exit(1);
    }
    char* readPath = argv[1];
    char* writePath = argv[2];

    //Upper left corner of the cropping rectangle
    int x1 = atoi(argv[3]);
    int y1 = atoi(argv[4]);

    //Lower right corner of the cropping rectangle 
    int x2 = atoi(argv[5]);
    int y2 = atoi(argv[6]);
    RasterImage img = readImage(readPath);
    checkDimensions(x1, x2, y1, y2, img);
    img = crop(img, x1, y1, x2, y2);
    if(doesDirectoryExist(writePath) == 0){
    	mkdir(writePath, 0777);
	printf("Directory created at: %s\n", writePath);
    }
    char* outPath = makeNewPath(readPath, writePath, "cropped");
    writeImage(outPath, &img);
    return 0;
}

/** will exit the program if the dimensions entered are larger than the image
 *  @param x1   the x-value of the upper-left corner of the crop rectangle
 *  @param y1   the y-value of the upper-left corner of the crop rectangle
 *  @param x2   the x-value of the bottom-right corner of the crop rectangle
 *  @param y2   the y-value of the bottom-right corner of the crop rectangle
 *  @param img  the RasterImage object to check dimensions on.
 */
void checkDimensions(int x1, int x2, int y1, int y2, RasterImage img){
    if(x1 < 0 || x2 > img.width || y1 < 0 || y2 > img.height){
        printf("The dimensions you've entered are larger than the image.\n");
        exit(1);
    }
}


