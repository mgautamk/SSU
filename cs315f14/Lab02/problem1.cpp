#include "EasyBMP.h"
#include "EasyBMP.cpp"
#include <iostream>


using namespace std;

void GenerateRedBlack(BMP & output)
{
  //boolean set to Red
  bool isRed = true;
  for (int i = 0; i < 256; i++)
    {
      for (int j = 0; j < 256; j++)	
	{
	  if (i%32 == 0)
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

int main()
{
  BMP cbRedBlack;
  cbRedBlack.SetSize(256, 256);
  cbRedBlack.SetBitDepth(32);
  GenerateRedBlack(cbRedBlack);
  cbRedBlack.WriteToFile("board.bmp");
  return 0;
}


