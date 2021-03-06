//Author: Mahesh Gautam
//Class: CS 315 Fall 2014
//Exercise: Lab02
//Description:This Program uses two different functions to generate two 
//different Images, one generates a checkerboard and the other draws a
//Seirpinski Image based on points provided by end-user. To see the desired 
//triangular Image, the Input points should be
//P0 = (171, 34) X = (128,5), Y = (5,251), Z = (251,251) 

#include "EasyBMP.h"
#include "EasyBMP.cpp"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

//This function generates a 256 * 256 Checkerboard
void GenerateRedBlack(BMP & output)
{
  //boolean set to Red
  bool isRed = true;
  
  for (int i = 0; i < 256; i++)
    {
      for (int j = 0; j < 256; j++)
	{
	  //Set Color Pixel for Red and black 
	  if (j%32 == 0)
	    isRed = !isRed;
	  if (isRed == true)
	    {
	      output(i,j)->Red = 255;
	      output(i,j)->Green = 0;
	      output(i,j)->Blue = 0;
	    }
	  else
	    {
	      output(i,j)->Red = 0;
	      output(i,j)->Green = 0;
	      output(i,j)->Blue = 0;
	    }
	}
      if(i%32 == 0)
	isRed = !isRed;
    }
  return;
}

//This function draws an Image based upon the midpoints of the vertices
//and one extra point provided by the end user.
void GenerateTriangle(BMP & output, int x1, int x2, int y1, int y2, int z1, int z2, int px, int py)
{
  //find width and height
  int row = output.TellWidth();
  int col = output.TellHeight();
  //Make the Entire Image to White
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      {
	output(i,j)->Red = 255;
	output(i,j)->Green = 255;
	output(i,j)->Blue = 255;
      }
  int Edge;
  int midx;
  int midy;
  //use time to generate random numbers so they are truly random
  srand(time(NULL));
  //Find midpoints from the point to the Edge and color them Red
  for (int i = 0; i < 10000; i++)
    {
      output(px, py)->Red = 255;
      output(px, py)->Green = 0;
      output(px, py)->Blue = 0;
      Edge = rand()%3;
      if (Edge == 0)
	{
	  midx = (px + x1)/2;
	  midy = (py + x2)/2;
	}
      else if (Edge == 1)
	{
	  midx = (px + y1)/2;
	  midy = (py + y2)/2;
	}
      else if (Edge == 2)
	{
	  midx = (px + z1)/2;
	  midy = (py + z2)/2;
	}
      px = midx;
      py = midy;
    }
  return;
}

//main function
int main()
{
  //Declare BMP Image variable for both functions and set their properties
  BMP sierpinski;
  BMP cbRedBlack;
  sierpinski.SetSize(256,256);
  sierpinski.SetBitDepth(32);
  cbRedBlack.SetBitDepth(32);
  cbRedBlack.SetSize(256, 256);
  GenerateRedBlack(cbRedBlack);
  //print to file
  cbRedBlack.WriteToFile("board.bmp");
  int x1, x2, y1, y2, z1, z2, px, py;
  //Ask end user for x and y points of the vertices and the point they select
  cout << "Please Enter threee vertices of the triangle and a point inside "<< endl;
  cout <<"the triangle in the order of x1, x2, y1, y2, z1, z2, px, py"<< endl;
  cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2 >> px >> py;
  //call to the function generating  an Image based on the midpoints of the vertices
  //and the point given by the user 
  GenerateTriangle(sierpinski, x1, x2, y1, y2, z1, z2, px, py);
  //print to file
  sierpinski.WriteToFile("sierpinski.bmp");
  return 0;
} 
