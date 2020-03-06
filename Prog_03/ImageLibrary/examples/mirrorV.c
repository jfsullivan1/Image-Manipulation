#include <stdio.h>
#include <stdlib.h>
#include <utilities.h>
#include <sys/stat.h>

/** MIRRORV.C
 *  this program will vertically mirror an image using the mirrorV utility function in utilities.h
 */

int main(int argc, char* argv[]){
    if(argc < 3){
        printf("Not enough arguments, usage: ./mirrorV <path1> <path2>\n");
        exit(1);
    }

    char* readPath = argv[1];
    char* writePath = argv[2];
    RasterImage img = readImage(readPath);
    img = mirrorV(img);
    if(doesDirectoryExist(writePath) == 0){
	mkdir(writePath, 0777);
	printf("Directory created at: %s\n", writePath);
    }
    char* outputPath = makeNewPath(readPath, writePath, "mirrorV");
    writeImage(outputPath, &img);
    return 0;
}

