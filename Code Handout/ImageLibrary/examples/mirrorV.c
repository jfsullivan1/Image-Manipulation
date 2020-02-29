#include <stdio.h>
#include <stdlib.h>
#include <utilities.h>

RasterImage mirrorH(RasterImage img);

int main(int argc, char* argv[]){
    if(argc < 3){
        printf("Not enough arguments, usage: ./mirrorV <path1> <path2>");
        exit(1);
    }

    char* readPath = argv[1];
    char* writePath = argv[2];
    RasterImage img = readImage(readPath);
    img = mirrorV(img);
    char* outputPath = makeNewPath(readPath, writePath, "mirrorV");
    writeImage(outputPath, &img);
    
    freeImage(&img);
    return 0;
}

