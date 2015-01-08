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

typedef struct Point {
    int x, y, z;
} point;

int trimin(int a, int b, int c) {
  return (a < b) ? (a < c ? a : c) : (b < c ? b : c);
}

int trimax(int a, int b, int c) {
  return (a > b) ? (a > c ? a : c) : (b > c ? b : c);
}

double determinant(Point a, Point b, Point c) {
  return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

Point newPoint(int x, int y, int z) {
  Point result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
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
  
  color_t clr0, clr1, clr2;
  clr0.r = 1;
  clr0.b = 0;
  clr0.g = 0;
  
  clr1.r = 0;
  clr1.b = 1;
  clr1.g = 0;
  
  clr2.r = 0;
  clr2.b = 0;
  clr2.g = 1;

  // make a 640x480 image (allocates buffer on the heap)
  Image img(640, 480);
//  char **cagePixels;
//  cagePixels = new char*[gimp_image.height];
//  for (int ndx = 0; ndx < gimp_image.height; ndx++) {
//    cagePixels[ndx] = new char[gimp_image.width * 3];
//  }
  
//  memcpy(*cagePixels, gimp_image.pixel_data, gimp_image.width * gimp_image.height * 3);

  // set a square to be the color above
  double totTriangleArea = determinant(points[0], points[1], points[2]);
  if (totTriangleArea < 0) {
    Point temp = points[0];
    points[0] = points[1];
    points[1] = temp;
    
    totTriangleArea = determinant(points[0], points[1], points[2]);
  }
  
  for (int i=minX; i < maxX; i++) {
    for (int j=minY; j < maxY; j++) {

      Point currPoint = newPoint(i, j, 0);
      double alpha = determinant(currPoint, points[1], points[2]);
      double beta = determinant(currPoint, points[2], points[0]);
      double gamma = determinant(currPoint, points[0], points[1]);
      
      if (alpha < 0 || beta < 0 || gamma < 0) {
        continue;
      }
      
      alpha /= totTriangleArea;
      beta /= totTriangleArea;
      gamma /= totTriangleArea;
      
      clr.r = (alpha * clr0.r) + (beta * clr1.r) + (gamma * clr2.r);
      clr.b = (alpha * clr0.b) + (beta * clr1.b) + (gamma * clr2.b);
      clr.g = (alpha * clr0.g) + (beta * clr1.g) + (gamma * clr2.g);
      
      img.pixel(i, j, clr);
    }
  }

  // write the targa file to disk
  img.WriteTga((char *)"awesome.tga", true); 
  // true to scale to max color, false to clamp to 1.0

  return 0;
}

