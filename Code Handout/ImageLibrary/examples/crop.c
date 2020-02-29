#include <stdio.h>
#include <stdlib.h>
#include <utilities.h>

int checkDimensions(int x1, int x2, int y1, int y2, RasterImage img);

int main(int argc, char* argv[]){
    if(argc != 7){
        printf("Invalid number of arguments. Usage: ./crop <filePath> <filePath> <x,y> <x,y>");
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
    char* outPath = makeNewPath(readPath, writePath, "crop");
    writeImage(outPath, &img);
    freeImage(&img);
    return 0;
}

int checkDimensions(int x1, int x2, int y1, int y2, RasterImage img){
    if(x1 < 0 || x2 > img.width || y1 < 0 || y2 > img.height){
        printf("The dimensions you've entered are larger than the image.\n");
        exit(1);
    }
}


