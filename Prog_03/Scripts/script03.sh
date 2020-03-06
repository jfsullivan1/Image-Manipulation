#!/bin/bash 

#Assignment 03
#script03
#John Sullivan
#2/28/2020

#================================================ |
# This script will take as arguments the   		  |
#  ImageLibrary path, and a directory path,  	  |
# 	to search for tga images, the script will     |
# 	recurse in subfolders and find all .tga images|
# 	and compare each to each.  					  |
#================================================ |
imgLib="$1"
searchFldr="$2"
currDir=$(pwd)

if [[ "${imgLib: -1}" != '/' || "${imgLib: -1}" != '\' ]];
then
	imgLib="$imgLib""/"
fi

if [ ! "$(ls -A "$searchFldr")" ]; 
then 
	echo "Directory for .tga files you provided is empty or doesn't exist."
	exit 1
fi

if [ ! "$(ls -A "$imgLib")" ]; 
then 
	echo "Directory for ImageLibrary you provided is empty or doesn't exist."
	exit 1
fi

cd "$searchFldr"

#This will make an array of all .tga files and their absolute paths (finds all in subdirs)
declare -a IMAGES
IFS=$'\n'
for Image in "$(find ~+ -type f -name '*tga')"
do	
	thePath=$Image
	if [[ $Image == *.tga ]];
	then
		IMAGES+=$thePath
	fi
done

cd "$currDir"
incorrectVal=1
#Compare all images 
for tga in ${IMAGES[*]};
do	
	for secondtga in ${IMAGES[*]};
	do
		if [ $tga != $secondtga ];
		then
			./comp $tga $secondtga
			if [ $? == 0 ];
			then
				echo "======================================================"
				echo $tga" and "$secondtga" are identical!"
				echo "======================================================"
			fi
		fi
	done
done


