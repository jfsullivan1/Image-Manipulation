#include <stdio.h>
#include <stdlib.h>
#include <utilities.h>

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Invalid number of arguments. Usage: ./comp <filePath> <filePath>");
        exit(1);
    }
    char* readPathOne = argv[1];
    char* readPathTwo = argv[2];
    RasterImage imgOne = readImage(readPathOne);
    RasterImage imgTwo = readImage(readPathTwo);
    comp(imgOne, imgTwo);
    return 0;
}
