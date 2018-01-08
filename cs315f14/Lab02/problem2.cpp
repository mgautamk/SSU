#include "EasyBMP.h"
#include "EasyBMP.cpp"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

void GenerateTriangle(BMP & output, int x1, int x2, int y1, int y2, int z1, int z2, int px, int py)
{
  int row = output.TellWidth();
  int col = output.TellHeight();
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
  srand(time(NULL));
  for (int i = 0; i < 1000000; i++)
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

int main()
{
  BMP sierpinski;
  sierpinski.SetSize(256,256);
  sierpinski.SetBitDepth(32);
  int x1, x2, y1, y2, z1, z2, px, py;
  cout << "Please Enter threee vertices of the triangle and a point inside "<< endl;
  cout <<"the triangle in the order of x1, x2, y1, y2, z1, z2, px, py"<< endl;
  cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2 >> px >> py;
  GenerateTriangle(sierpinski, x1, x2, y1, y2, z1, z2, px, py);
  sierpinski.WriteToFile("sierpinski.bmp");
  return 0;
} 
