#!/bin/bash 

#Assignment 03
#John Sullivan
#script01
#2/28/2020

#================================================ |
# This script will build all my .o files I need	  |
# in order to make my libraries, and then make the|
# static and dynamic libraries, and then compile  |
# the utility programs with those libraries		  |
# and then make executables for them.			  |
#================================================ |
if [ ! "$(ls -A "$1")" ]; 
then 
	echo "Directory for ImageLibrary you provided is empty or doesn't exist."
	exit 1
fi

if [ ! "$(ls -A "$1/lib")" ]; 
then 
	mkdir "$1"//lib
	mkdir "$1"/lib/static
	mkdir "$1"/lib/dynamic
fi

fname="$1"
gcc -c "$fname"/src/ImageIO_TGA.c -I "$fname"/include -o "$fname"/lib/static/ImageIO_TGA.o
gcc -c "$fname"/src/RasterImage.c -I "$fname"/include -o "$fname"/lib/static/RasterImage.o
gcc -c -fPIC "$fname"/src/ImageIO_TGA.c -I "$fname"/include -o "$fname"/lib/dynamic/ImageIO_TGA.o
gcc -c -fPIC "$fname"/src/RasterImage.c -I "$fname"/include -o "$fname"/lib/dynamic/RasterImage.o
gcc -c "$fname"/src/utilities.c -I "$fname"/include -o "$fname"/lib/static/utilities.o
gcc -c -fPIC "$fname"/src/utilities.c -I "$fname"/include -o "$fname"/lib/dynamic/utilities.o
ar rcs "$fname"/lib/static/libImage.a "$fname"/lib/static/ImageIO_TGA.o "$fname"/lib/static/RasterImage.o "$fname"/lib/static/utilities.o
gcc -shared "$fname"/lib/dynamic/ImageIO_TGA.o "$fname"/lib/dynamic/RasterImage.o "$fname"/lib/dynamic/utilities.o -o "$fname"/lib/dynamic/libImage.so 

echo "/================================================="
echo "/Successfully built static & dynamic libraries."
echo "/================================================="

gcc "$fname"/examples/crop.c -I "$fname"/include -L"$fname"/lib/static -lImage -o crop
gcc "$fname"/examples/comp.c -I "$fname"/include -L"$fname"/lib/static -lImage -o comp
gcc "$fname"/examples/gray.c -I "$fname"/include -L"$fname"/lib/static -lImage -o gray
gcc "$fname"/examples/mirrorV.c -I "$fname"/include -L"$fname"/lib/static -lImage -o mirrorV
gcc "$fname"/examples/mirrorH.c -I "$fname"/include -L"$fname"/lib/static -lImage -o mirrorH

echo "/================================================"
echo "/Successfully built all utility programs in your current local directory: "$(pwd)
echo "/================================================"
