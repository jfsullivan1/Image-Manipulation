#include <stdio.h>
#include <stdlib.h>
#include <utilities.h>
#include <sys/stat.h>

/** GRAY.C
 *  this program will make an image gray using the gray utility function in utilities.h
 */

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Invalid number of arguments. Usage: ./gray <filePath> <filePath>\n");
        exit(1);
    }
    char* readPath = argv[1];
    char* writePath = argv[2];
    RasterImage img = readImage(readPath);
    img = gray(img);
    if(doesDirectoryExist(writePath) == 0){
	mkdir(writePath, 0777);
	printf("Directory created at: %s\n", writePath);
    }
    char* outputPath = makeNewPath(readPath, writePath, "gray");
    writeImage(outputPath, &img);
    return 0;
}


