/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color* pixel = (Color*) malloc(sizeof(Color));
	if (pixel == NULL) {
		exit(-1);
	}

	uint8_t LSB = image->image[row][col].B & 1;
	pixel->R = pixel->G = pixel->B = 255 * LSB;

	return pixel;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image* newImg = (Image*) malloc(sizeof(Image));
	if (newImg == NULL) {
		exit(-1);
	}
	newImg->cols = image->cols;
	newImg->rows = image->rows;
	newImg->image = (Color**) malloc(newImg->rows * sizeof(Color*));
	if (newImg->image == NULL) {
		exit(-1);
	}
	for (int i = 0; i < image->rows; ++i) {
		newImg->image[i] = (Color*) malloc(newImg->cols * sizeof(Color));
		if (newImg->image[i] == NULL) {
			exit(-1);
		}
		for (int j = 0; j < image->cols; ++j) {
			Color* color = evaluateOnePixel(image, i, j);
			newImg->image[i][j] = *color;
			free(color);
		}
	}

	return newImg;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 2) {
		exit(-1);
	}

	char* filename = argv[1];
	Image* image = readData(filename);
	Image* newImg = steganography(image);
	writeData(newImg);

	freeImage(image);
	freeImage(newImg);
	return 0;
}
