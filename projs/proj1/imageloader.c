/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include "imageloader.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Opens a .ppm P3 image file, and constructs an Image object.
// You may find the function fscanf useful.
// Make sure that you close the file with fclose before returning.
Image *readData(char *filename) {
  // YOUR CODE HERE
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Failed to open %s\n", filename);
    return NULL;
  }
  Image *image = (Image *)malloc(sizeof(Image));

  char format[5];
  fscanf(fp, "%s", format);
  if (format[0] != 'P' || format[1] != '3') {
    printf("Wrong .ppm format\n");
    fclose(fp);
    return NULL;
  }

  fscanf(fp, "%d%d", &image->cols, &image->rows);

  int maxColor;
  fscanf(fp, "%d", &maxColor);

  if (image->cols <= 0 || image->rows <= 0 || maxColor > 255 || maxColor < 0) {
    printf("Wrong .ppm format\n");
    fclose(fp);
    return NULL;
  }

  image->image = (Color **)malloc(image->rows * sizeof(Color *));
  for (int i = 0; i < image->rows; ++i) {
    image->image[i] = (Color*) malloc(image->cols * sizeof(Color));
    Color *color = image->image[i];
    for (int j = 0; j < image->cols; ++j) {
      fscanf(fp, "%hhu%hhu%hhu", &color[j].R, &color[j].G, &color[j].B);
    }
  }

  fclose(fp);

  return image;
}

// Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the
// image's data.
void writeData(Image *image) {
  // YOUR CODE HERE
  printf("P3\n");
  printf("%d %d\n", image->cols, image->rows);
  printf("255\n");
  for (int i = 0; i < image->rows; ++i) {
    for (int j = 0; j < image->cols; ++j) {
      Color *color = image->image[i];
      printf("%3hhu %3hhu %3hhu", color[j].R, color[j].G, color[j].B);
      if (j == image->cols - 1) {
        printf("\n");
      } else {
        printf("   ");
      }
    }
  }
}

// Frees an image
void freeImage(Image *image) {
  // YOUR CODE HERE
  for (int i = 0; i < image->rows; ++i) {
    free(image->image[i]);
  }
  free(image->image);
  free(image);
}
