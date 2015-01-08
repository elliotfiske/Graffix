/*
  CPE 471 Lab 1 
  Base code for Rasterizer
  Example code using B. Somers' image code - writes out a sample tga
*/

#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include "types.h"
#include "cage.cpp"
#include <algorithm>

typedef struct Point {
    int x, y, z;
} point;

int trimin(int a, int b, int c) {
  return (a < b) ? (a < c ? a : c) : (b < c ? b : c);
}

int trimax(int a, int b, int c) {
  return (a > b) ? (a > c ? a : c) : (b > c ? b : c);
}

int main(void) {

  Point points[3];
  
  printf("Enter the points of the triangle [x1, y1], [x2, y2], [x3, y3]");
  int *dumb = (int *)points;
  for (int ndx = 0; ndx < 9; ndx++) {
    scanf("%i", dumb++);
  }
  
  int minX = trimin(points[0].x, points[1].x, points[2].x);
  int minY = trimin(points[0].y, points[1].y, points[2].y);
  
  int maxX = trimax(points[0].x, points[1].x, points[2].x);
  int maxY = trimax(points[0].y, points[1].y, points[2].y);
  
  // make a color
  color_t clr;

  clr.r = 0.5;
  clr.g = 0.5;
  clr.b = 0.9;

  // make a 640x480 image (allocates buffer on the heap)
  Image img(640, 480);
  char **cagePixels;
  cagePixels = new char*[gimp_image.height];
  for (int ndx = 0; ndx < gimp_image.height; ndx++) {
    cagePixels[ndx] = new char[gimp_image.width * 3];
  }
  
//  memcpy(*cagePixels, gimp_image.pixel_data, gimp_image.width * gimp_image.height * 3);

  // set a square to be the color above
  for (int i=minX; i < maxX; i++) {
    for (int j=minY; j < maxY; j++) {
      clr.r = (double) cagePixels[j % gimp_image.height][(i % gimp_image.width)*3] / 255.0;
      clr.g = (double) cagePixels[j % gimp_image.height][(i % gimp_image.width)*3 + 1] / 255.0;
      clr.b = (double) cagePixels[j % gimp_image.height][(i % gimp_image.width)*3 + 2] / 255.0;

      img.pixel(i, j, clr);
    }
  }

  // write the targa file to disk
  img.WriteTga((char *)"awesome.tga", true); 
  // true to scale to max color, false to clamp to 1.0

  return 0;
}

