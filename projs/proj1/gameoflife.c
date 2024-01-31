/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include "imageloader.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

const int dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                       {0, 1},   {1, -1}, {1, 0},  {1, 1}};

int calRow(int row, int op, int len) {
  int ret = row + dir[op][0];
  if (ret < 0) {
    ret = len - 1;
  } else if (ret >= len) {
    ret = 0;
  }
  return ret;
}

int calCol(int col, int op, int len) {
  int ret = col + dir[op][1];
  if (ret < 0) {
    ret = len - 1;
  } else if (ret >= len) {
    ret = 0;
  }
  return ret;
}

// Determines what color the cell at the given row/col should be. This function
// allocates space for a new Color. Note that you will need to read the eight
// neighbors of the cell in question. The grid "wraps", so we treat the top row
// as adjacent to the bottom row and the left column as adjacent to the right
// column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule) {
  // YOUR CODE HERE
  int isAliveR, isAliveG, isAliveB;
  isAliveR = (image->image[row][col].R == 255);
  isAliveG = (image->image[row][col].G == 255);
  isAliveB = (image->image[row][col].B == 255);

  uint32_t aliveNeighborsR, aliveNeighborsG, aliveNeighborsB;
  aliveNeighborsR = isAliveR ? 9 : 0;
  aliveNeighborsG = isAliveG ? 9 : 0;
  aliveNeighborsB = isAliveB ? 9 : 0;
  for (int i = 0; i < 8; ++i) {
    int nr = calRow(row, i, image->rows);
    int nc = calCol(col, i, image->cols);

    aliveNeighborsR += (image->image[nr][nc].R == 255);
    aliveNeighborsG += (image->image[nr][nc].G == 255);
    aliveNeighborsB += (image->image[nr][nc].B == 255);
  }

  Color *nextGen = (Color *)malloc(sizeof(Color));
  int lifeR, lifeG, lifeB;
  lifeR = rule & (1 << aliveNeighborsR);
  lifeG = rule & (1 << aliveNeighborsG);
  lifeB = rule & (1 << aliveNeighborsB);

  nextGen->R = lifeR ? 255 : 0;
  nextGen->G = lifeG ? 255 : 0;
  nextGen->B = lifeB ? 255 : 0;

  return nextGen;
}

// The main body of Life; given an image and a rule, computes one iteration of
// the Game of Life. You should be able to copy most of this from
// steganography.c
Image *life(Image *image, uint32_t rule) {
  // YOUR CODE HERE
  Image *newLife = (Image*) malloc(sizeof(Image));
  if (newLife == NULL) {
    exit(-1);
  }
  newLife->cols = image->cols;
  newLife->rows = image->rows;
  newLife->image = (Color**) malloc(newLife->rows * sizeof(Color *));
  if (newLife->image == NULL) {
    exit(-1);
  }
  for (int i = 0; i < image->rows; ++i) {
    newLife->image[i] = (Color*) malloc(newLife->cols * sizeof(Color));
    if (newLife->image[i] == NULL) {
      exit(-1);
    }
    for (int j = 0; j < image->cols; ++j) {
      Color *nextGen = evaluateOneCell(image, i, j, rule);
      newLife->image[i][j] = *nextGen;
      free(nextGen);
    }
  }

  return newLife;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then
prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this
will be a string. You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you
should exit with code -1. Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv) {
  // YOUR CODE HERE
  if (argc != 3) {
    printf("usage: ./gameOfLife filename rule\n");
    printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
    printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
    exit(-1);
  }

  char *filename = argv[1];
  uint32_t rule = strtol(argv[2], NULL, 16);
  Image *image = readData(filename);
  Image *newLife = life(image, rule);
  writeData(newLife);
  //writeData(image);

  freeImage(image);
  freeImage(newLife);
  return 0;
}
