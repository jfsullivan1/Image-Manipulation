#include <stdio.h>
#include <stdlib.h>
#include <utilities.h>

/** COMP.C 
 *  this program will compare two images using the comp utility function in utilities.h
 */
int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Invalid number of arguments. Usage: ./comp <filePath> <filePath>\n");
        exit(1);
    }
    char* readPathOne = argv[1];
    char* readPathTwo = argv[2];
    RasterImage imgOne = readImage(readPathOne);
    RasterImage imgTwo = readImage(readPathTwo);
    return comp(imgOne, imgTwo);
}
