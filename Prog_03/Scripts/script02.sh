#!/bin/bash 

#Assignment 03
#script02
#John Sullivan
#2/28/2020

#================================================ |
# This script will take as arguments the   		  |
#  ImageLibrary path, images directory path,  	  |
# 	output directory path, and a filepath for  	  |
# 	several commands to use on the images in the  |
# 	provided directory.		  					  |
#================================================ |

imgLib="$1"
tgaDir="$2"
outDir="$3"
cmds="$4"
declare -a cmdsArray
if [ ! "$(ls -A "$1")" ]; 
then 
	echo "Directory for ImageLibrary you provided is empty or doesn't exist."
	exit 1
fi

if [ ! "$(ls -A "$2")" ]; 
then 
	echo "Directory for Images you provided is empty or doesn't exist."
	exit 1	
fi

if [ ! -d "$outDir" ];
then 
	mkdir "$outDir"
fi

# Make sure I have trailing slashes
if [ "${imgLib: -1}" != '/' ];
then
	imgLib="$imgLib""/"
fi
if [ "${tgaDir: -1}" != '/' ];
then
	tgaDir="$tgaDir""/"
fi

#Test my cmd file exists 
if test -f "$4" ;
then
	#Loops over all commands in the file
	while IFS= read -r line 
	do
		cmdsArray=(${line})
		
		# Switch statement to decide how to execute
		case ${cmdsArray[0]} in
			"crop")./crop "$tgaDir"${cmdsArray[1]} "$outDir" ${cmdsArray[2]} ${cmdsArray[3]} ${cmdsArray[4]} ${cmdsArray[5]}
			;;
			"comp")./comp "$tgaDir"${cmdsArray[1]} "$tgaDir"${cmdsArray[2]}
			;;
			"gray")./gray "$tgaDir"${cmdsArray[1]} "$outDir"
			;;
			"mirrorV")./mirrorV "$tgaDir"${cmdsArray[1]} "$outDir"
			;;	
			"mirrorH")./mirrorH "$tgaDir"${cmdsArray[1]} "$outDir"
			;;
			#======= DEFAULT ===========
			"*") echo "No command found for a given input."
			;;
		esac
	done < "$4"
else
	echo "The commands file you entered does not exist."
	exit 1
fi
		

