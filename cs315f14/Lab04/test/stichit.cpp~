#include <iostream>
#include "EasyBMP.cpp"
#include "EasyBMP.h"
#include <cmath>
#include <string>

using namespace std;

// Filenames for input and output
const string INFILENAMES [16] = {"img1.bmp", "img2.bmp", "img3.bmp",
				  "img4.bmp", "img5.bmp", "img6.bmp", "img7.bmp", "img8.bmp",
				  "img9.bmp", "img10.bmp", "img11.bmp", "img12.bmp",
				  "img13.bmp", "img14.bmp", "img15.bmp", "img16.bmp"};


int rowMatch (BMP& UseTop, BMP& UseBottom )
{ // Compares the top edge of UseTop to the bottom edge of UseBottom.
  // Assumes UseTop and UseBottom are squares of same size
  // score obtained by adding the difference between color components
  int width = UseTop.TellWidth();
  int height = UseTop.TellHeight();
  int NSscore = 0;
  for (int i = 0; i < height; i++)
    {
      RGBApixel* top = UseTop(i, 0);
      RGBApixel* bottom = UseBottom(i, height-1);
      NSscore += abs(top->Red - bottom->Red) + abs(top->Green - bottom->Green) + abs(top->Blue - bottom->Blue);
    }
  return NSscore;
}

int columnMatch ( BMP& UseRight, BMP& UseLeft )
{
  // Compares the right edge of UseRight to the left edge of UseLeft.
  // Assumes UseRight and UseLeft are squares of same size
  // score obtained by adding the difference between color components
  // similar to the rowMatch
  int width = UseRight.TellWidth();
  int height = UseLeft.TellHeight();
  int EWscore = 0;
  for (int i = 0; i < width; i++)
    {
      RGBApixel* right = UseRight(width-1, i);
      RGBApixel* left = UseLeft(0, i);
      EWscore += abs(right->Red - left->Red) + abs(right->Green - left->Green) + abs(right->Blue - left->Blue);
    }
  return EWscore; 
}

void finalScore (BMP images[16], int  score[2][16][16]) {
  // uses the rowMatch and columnMatch to create scores
  // score[0][i][j] is the EAST SCORE and score[1][i][j] is the NORTH SCORE
  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 16; j++)
      {
	if (i != j)
	  {
	    score[1][i][j] = rowMatch(images[i], images[j]);
	    score[0][i][j] = columnMatch(images[i], images[j]);
	  }
      }
}

int findNorthWest(int score[2][16][16]) {
  // finds the North West tile by adding the best North and West scores for each tile and
  // choosing the one that maximizes the score
  int highestSumOfMinimums = 0;
  bool firstTotal = true;
  int idx;
  for (int i = 0; i < 16; i++)
    {
      bool firstEast = true;
      bool firstNorth = true;
      int lowestEast;
      int lowestNorth;
      for (int j = 0; j < 16; j++)
	{
	  if (i == j)
	    continue;
	  int east = score[0][j][i];
	  int north = score[1][i][j];
	  if(firstEast || (east < lowestEast))
	    {
	      lowestEast = east;
	      firstEast = false;
	    }
	  if(firstNorth || (north < lowestNorth))
	    {
	      lowestNorth = north;
	      firstNorth = false;
	    }
	}
      int current = lowestNorth + lowestEast;
      if(firstTotal || current > highestSumOfMinimums)
	{
	  highestSumOfMinimums = current;
	  idx = i;
	  firstTotal = false;
	}
    }
  return idx;
}

int findEastNeighbor(int score[2][16][16], int tile, bool remaining[16]) {
  // for a given tile, find its eastern neighbor among the remaining ones
  // remaining[j] is true for tiles that have not yet been placed in the final image
  long long int lowestScore = 999999999999;
  int ImageNumber = -1;
  for (int i = 0; i < 16; i++)
    {
      if (tile == i)
	continue;
      if((lowestScore > score[0][tile][i] || ImageNumber < 0) && remaining[i])
	{
	  lowestScore = score[0][tile][i];
	  ImageNumber = i;
	}
    }
  if (ImageNumber >= 0)
    remaining[ImageNumber] = false;
  return ImageNumber;
}


int findSouthNeighbor(int score[2][16][16], int tile, bool remaining[16]) {
  // for a given tile, find its southern neighbor, among the remaining ones
  // remaining[j] is true for tiles that have not yet been selected for placement
  // similar to findEastNeighbor
  long long int lowestScore = 999999999999;
  int ImageNumber = -2;
  for (int i = 0; i < 16; i++)
    {
      if (tile == i)
	continue;
      if((lowestScore > score[1][i][tile] || ImageNumber < 0) && remaining[i]);
      {
	lowestScore = score[1][i][tile];
	ImageNumber = i;
      }
    }
  if ( ImageNumber >= 0)
    remaining[ImageNumber] = false;
  return ImageNumber;
}

void copy(BMP & InImg, BMP & OutImg, int i, int j) {
  // copy image to larger final picture so that the InImg is placed in row i, column j of OutImg
  int inheight = InImg.TellHeight();
  int inwidth = InImg.TellWidth();
  int Imagelength = OutImg.TellWidth()/4;
  int Cx; //position of Image in X axis
  int Cy; //position of Image in Y axis
  if (i == 1)
    Cx = 0;
  else 
    Cx = (i-1) * Imagelength;  
  
  if (j == 1)
    Cy = 0;
  else
    Cy = (j-1) * Imagelength;
  RangedPixelToPixelCopy(InImg, 0, inwidth, inheight, 0, OutImg, Cx, Cy);
  
}

void greedy(int score[2][16][16], BMP InImg[16], BMP & OutImg) {
  //greedy algorithm to put the image together
  bool remaining[16];
  int ImgNum;
  int rowcount = 0;
  for (int i = 0; i < 16; i++)
    {
      remaining[i] = true;
    }
  for (int j = 1; j <= 4; j++)
    {
      for (int k = 1; k <= 4; k++)
	{
	  if (j == 1 && k == 1)
	    {
	      ImgNum = findNorthWest(score);
	      copy(InImg[ImgNum], OutImg, k, j);
	      rowcount = ImgNum;
	    }
	  //cout << ImgNum << endl;
	  if (k > 1)
	    {
	      ImgNum = findEastNeighbor(score, ImgNum, remaining);
	      copy(InImg[ImgNum], OutImg, k, j);
	    }
	  else if (k == 1 && j != 1)
	    {
	      ImgNum = findSouthNeighbor(score, rowcount, remaining);
	      copy(InImg[ImgNum], OutImg, k, j);
	      rowcount = ImgNum;
	    }
	}
    }
}

int main()
{
  BMP InImg[16], OutImg; // vector of input images and output image
  int score [2][16][16] ;       // holds EAST and NORTH scores
  for( int i=0; i<16; ++i ) // Read in the sub-images
    InImg[i].ReadFromFile( INFILENAMES[i].c_str());
  int subsize = InImg[0].TellWidth();
  OutImg.SetSize( 4*subsize, 4*subsize ); // Set size of output image
  finalScore(InImg, score);
  greedy( score, InImg, OutImg);
  /*
  bool remaining[16];
  for (int i =0; i < 16; ++i)
    remaining[i] = false;
  int first = findNorthWest(score);
  int second = findSouthNeighbor(score, first, remaining);
  cout << second << endl;
  cout << score[1][15][12] << endl;
  copy(InImg[first], OutImg, 1, 1);
  copy(InImg[second], OutImg, 1, 2);
*/
  OutImg.WriteToFile("output.bmp");
  return 0;
}
