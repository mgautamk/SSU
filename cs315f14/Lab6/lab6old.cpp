#include <iostream>
#include <string>
#include "EasyBMP.cpp"
#include "EasyBMP.h"
#include <stdlib.h>
#include "queue.cpp"
#include <cmath>
#include <vector>

using namespace std;

void SetColor(RGBApixel * pic, RGBApixel* shit)
{
  pic->Red = shit->Red;
  pic->Green = shit->Green;
  pic->Blue = shit->Blue;
  return;
}

bool IsForeground(RGBApixel* foreground, RGBApixel* background, RGBApixel* pixel)
{
  int fd = abs(foreground->Red - pixel->Red) + abs(foreground->Green - pixel->Green) + abs(foreground->Blue - pixel->Blue);
  int bd = abs(background->Red - pixel->Red) + abs(background->Green - pixel->Green) + abs(background->Blue - pixel->Blue);
  return fd < bd;
}

RGBApixel* GetColor(int red, int green, int blue)
{
  RGBApixel* color = new RGBApixel();
  color->Red = red;
  color->Green = green;
  color->Blue = blue;
  return color;
}

RGBApixel* GetColor(string color)
{
  if (color == "Black") return GetColor(0, 0, 0);
  else if (color == "Green") return GetColor(0, 255, 0);
  else if (color == "White") return GetColor(255, 255, 255);
  else if (color == "Silver") return GetColor(192, 192, 192);
  else if (color == "Gray") return GetColor(128, 128, 128);
  else if (color == "Yellow") return GetColor(255, 255, 0);
  else if (color == "Fuchsia") return GetColor(255, 0, 255);
  else if (color == "Red") return GetColor(255, 0, 0);
  else if (color == "Maroon") return GetColor(128, 0, 0);
  else if (color == "Lime") return GetColor(0, 255, 0);
  else if (color == "Olive") return GetColor(128, 128, 0);
  else if (color == "Green") return GetColor(0, 128, 0);
  else if (color == "Purple") return GetColor(128, 0, 128);
  else if (color == "Aqua") return GetColor(0, 255, 255);
  else if (color == "Teal") return GetColor(0, 128, 128);
  else if (color == "Blue") return GetColor(0, 0, 255);
  else if (color == "Navy") return GetColor(0, 0, 128);

  else return NULL;
}

struct Rectangle
{
  int left, right, top, bottom;
};

void label(BMP & image, int xlow, int xhigh, int ylow, int yhigh, RGBApixel* c1, RGBApixel* c2, RGBApixel* c3, RGBApixel* c4)
{
  //update the Image by labeling
  int count = 0;
  int minx, miny, maxx, maxy;
  bool* visited = new bool[image.TellWidth() * image.TellHeight()];
  queue Q;
  bool firstvisited= true;

  RGBApixel* foreground = GetColor("foreground");
  RGBApixel* background = GetColor("background");
  
  vector<Rectangle> letters;

  image.SetBitDepth(8);
  for (int col = xlow; col < xhigh; col++)
    {
      for (int row = ylow; row < yhigh; row++)
	{
          int idx = col + row * image.TellWidth();
	  visited[idx] = false;
	  
	  if(!IsForeground(foreground, background, image(col, row)))
	    {
	      SetColor(image(col, row), c1);
	    }
	  else
	    {
	      SetColor(image(col, row), c2);
	    }
	}
    }

  //ylow = xlow = 0;
  //xhigh = yhigh = 160;

  for (int row = ylow; row < yhigh; row++)
    {
      for (int col = xlow; col < xhigh; col++)
	{
          int idx = col + row * image.TellWidth(); 
	  if (!visited[idx] && IsForeground(foreground, background, image(col,row)))// = c2
	    {
	      count++;
	      minx = col; 
	      maxx = col; 
	      miny = row;
	      maxy = row;
	      Q.insert(new point(col,row));
	      while(!Q.isEmpty())
		{
		  point p = Q.del();
		  int x1 = p.getx();
		  int y1 = p.gety();

		  int idx1 = x1 + y1 * image.TellWidth();

		  if (visited[idx1] || !IsForeground(foreground, background, image(x1, y1)))
		    continue;
		  visited[idx1] = true;
		  //cout << x1 << " " << y1 << endl;

		  SetColor(image(x1, y1), c3);
		  
		  if (x1 < minx)
		    minx = x1;
		  if (y1 < miny)
		    miny = y1;
		  if (x1 > maxx)
		    maxx = x1;
		  if (y1 > maxy)
		    maxy = y1;
		  //for each neighbor
		  //cout << ylow << " " << y1 << " " << yhigh << endl;
		  if (y1 < (yhigh - 1)) Q.insert(new point(x1, y1 + 1));
		  if (x1 > xlow) Q.insert(new point(x1 - 1, y1));
		  if (x1 < (xhigh - 1)) Q.insert(new point(x1 + 1, y1));
		  if (y1 > ylow) Q.insert(new point(x1, y1 - 1));	
		}//end while
	      
	      cout << minx << " " << maxx << " " << miny << " " << maxy << endl;
	      Rectangle letter;
	      letter.left = minx;
	      letter.right = maxx;
	      letter.top = miny;
	      letter.bottom = maxy;
	      letters.push_back(letter);
	    }//end if
	}//end for   
    }
  
  for(int i = 0; i < letters.size(); ++i)
    {
      for (int rcol = letters[i].left; rcol < letters[i].right; rcol++)
	{
	  SetColor(image(rcol, letters[i].top), c4);
	  SetColor(image(rcol, letters[i].bottom), c4);
	}
      for (int rrow = letters[i].top; rrow < letters[i].bottom; rrow++)
	{
	  SetColor(image(letters[i].left, rrow), c4);
	  SetColor(image(letters[i].right, rrow), c4);
	} //end for
      
    }
}

int main(int argc, char *argv[])
{
  //Read in the Image
  BMP Img;
  string background;
  string foreground;
  string processed;
  string bounding;

  //Read the Image
  Img.ReadFromFile(argv[1]);

  //Ask for user Input for c1, c2, c3, c4
  cout << "Please specify the Background Color:" <<endl;
  cin >> background;
  cout << "Please specify the Foreground Color:" <<endl;
  cin >> foreground;
  cout << "Please specify the Color to which the foreground is to be changed:" << endl;
  cin >> processed;
  cout << "Please specify the Color of the bounding box:" << endl;
  cin >> bounding;

  RGBApixel* c1, c2, c3, c4;
  c1 = GetColor(background);
  c2 = GetColor(foreground);
  c3 = GetColor(processed);
  c4 = GetColor(bounding);

  //call label
  label(Img, 0, Img.TellWidth(), 0, Img.TellHeight());
  Img.WriteToFile(argv[2]);
  return 0;
}


