#include <stdio.h>
#include <stdlib.h>
#include <utilities.h>

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Invalid number of arguments. Usage: ./gray <filePath> <filePath>");
        exit(1);
    }
    char* readPath = argv[1];
    char* writePath = argv[2];
    RasterImage img = readImage(readPath);
    img = gray(img);
    char* outputPath = makeNewPath(readPath, writePath, "gray");
    writeImage(outputPath, &img);
    freeImage(&img);
    return 0;
}


