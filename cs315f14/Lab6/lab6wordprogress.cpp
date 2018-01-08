//*******************************************************************************************************************
//Author: Mahesh Gautam
//Class: CS 315
//Assignment : Lab06
//Description: 
//*******************************************************************************************************************
#include <iostream>
#include <string>
#include "EasyBMP.cpp"
#include "EasyBMP.h"
#include <stdlib.h>
#include "queue.cpp"
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

//Define a struct for datatype color
struct color{
  int r;
  int g;
  int b;
};

//Setcolor to assign rgb
void SetColor(RGBApixel * pic, color pix)
{
  pic->Red = pix.r;
  pic->Green = pix.g;
  pic->Blue = pix.b;
  return;
}

//boolean to determine if the color is foreground
bool IsForeground(color foreground, color background, RGBApixel* pixel)
{
  int fd = abs(foreground.r - pixel->Red) + abs(foreground.g - pixel->Green) + abs(foreground.b - pixel->Blue);
  int bd = abs(background.r - pixel->Red) + abs(background.g - pixel->Green) + abs(background.b - pixel->Blue);
  return fd < bd;
}

//assigning numerical values to rgb colors
color GetColor(int red, int green, int blue)
{
  color color;
  color.r = red;
  color.g = green;
  color.b = blue;
  return color;
}

//Assign values for each color that might be provided
color GetColor(string color)
{
  if (color == "black") return GetColor(0, 0, 0);
  else if (color == "green") return GetColor(0, 255, 0);
  else if (color == "white") return GetColor(255, 255, 255);
  else if (color == "silver") return GetColor(192, 192, 192);
  else if (color == "gray") return GetColor(128, 128, 128);
  else if (color == "yellow") return GetColor(255, 255, 0);
  else if (color == "fuchsia") return GetColor(255, 0, 255);
  else if (color == "red") return GetColor(255, 0, 0);
  else if (color == "maroon") return GetColor(128, 0, 0);
  else if (color == "lime") return GetColor(0, 255, 0);
  else if (color == "olive") return GetColor(128, 128, 0);
  else if (color == "green") return GetColor(0, 128, 0);
  else if (color == "purple") return GetColor(128, 0, 128);
  else if (color == "aqua") return GetColor(0, 255, 255);
  else if (color == "teal") return GetColor(0, 128, 128);
  else if (color == "blue") return GetColor(0, 0, 255);
  else if (color == "navy") return GetColor(0, 0, 128);

  else{//to handle case where invalid color is given
    cout << "Please pick a valid color." <<endl;
  }
}

//defining a struct to store dimensions
struct Rectangle
{
  int left, right, top, bottom;
};


void orderLetter(vector<Rectangle> & line)
{
 int j; 
 Rectangle temp; 
 for (int i = 1; i < line.size(); ++i)
   { 
     temp = line[i]; 
     j = i - 1; 
     while (j >= 0 && line[j].left > temp.left)
       {
	 line[j+1] = line[j];
	 j = j -1; 
       }// end while; 
     line[j+1] = temp; 
   }//end for 
}// end orderLetter


//function label which will preprocess the Image and also do the counting for letters, words, etc
void label(BMP & image, int xlow, int xhigh, int ylow, int yhigh, color c1, color c2, color c3, color c4)
{
  //update the Image by labeling                                                                                                  
  int count = 0;
  int minx, miny, maxx, maxy;
  bool* visited = new bool[image.TellWidth() * image.TellHeight()];
  queue Q;
  bool firstvisited= true;
  int averageWidth = 0;
  int wordCount = 0;
  vector<Rectangle> letters;

  image.SetBitDepth(8);
  for (int col = xlow; col < xhigh; col++)
    {
      for (int row = ylow; row < yhigh; row++)
        {
          int idx = col + row * image.TellWidth();
          visited[idx] = false;

          if(!IsForeground(c2, c1, image(col, row)))
            {
              SetColor(image(col, row), c1);
            }
          else
            {
              SetColor(image(col, row), c2);
            }
        }
    }
  int letterWidths = 0;
  for (int row = ylow; row < yhigh; row++)
    {
      for (int col = xlow; col < xhigh; col++)
        {
          int idx = col + row * image.TellWidth();
          if (!visited[idx] && IsForeground(c2, c1, image(col,row)))// = c2                                                       
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
		  if(visited[idx1] || (!IsForeground(c2, c1, image(x1,y1))))
                    continue;
                  visited[idx1] = true;
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
                  if (y1 < (yhigh - 1)) Q.insert(new point(x1, y1 + 1));
                  if (x1 > xlow) Q.insert(new point(x1 - 1, y1));
                  if (x1 < (xhigh - 1)) Q.insert(new point(x1 + 1, y1));
                  if (y1 > ylow) Q.insert(new point(x1, y1 - 1));
                }//end while
	      //letterWidths += maxx-minx;
              Rectangle letter;
              letter.left = minx;
              letter.right = maxx;
              letter.top = miny;
              letter.bottom = maxy;
	      averageWidth += (maxx - minx);
              letters.push_back(letter);
            }//end if                                                                                                             
        }//end for                                                                                                                
    }

  //Draw the bounding box
  int lines = 1;
  if(letters.size() == 0)
    {
      lines = 0;
    }
  for(int i = 0; i < letters.size(); ++i)
    {
      //lettersOnLine.push_back(letters[i].left);
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

  vector <Rectangle> line;
  averageWidth = averageWidth/letters.size();
  for (int i = 0; i < letters.size(); i++)
    {
      line.push_back(letters[i]);
      if (i < (letters.size()-1))
	{
	  if (letters[i].bottom < letters[i+1].top)
	    {
	      orderLetter(line);
	      lines++;
	      wordCount++;
	    }
	  if (((line[i].left - line[i+1].right) > averageWidth/10))
	    {
	      wordCount++;
	      line.clear();
	    }
	}
    }
  //print out number of lines, letters, and words 
  cout << "Number of Words:" << wordCount << endl;
  cout << "Number of Lines: " << lines << endl;
  cout << "Number of Letters: " << count << endl;
  //return count;
}//end label


//main 
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

  int xlow, xhigh, ylow, yhigh;
  string choice;
  color c1, c2, c3, c4;
 retry: // for invalid inputs
  cout << "Would you like to enter the region of the input image and colors? (Y OR N): ";
  getline(cin,choice);
  
  int k = 0;
  while (choice[k])
    {
      choice[k] = toupper(choice[k]);
      k++;
    }
  cout << "You chose: " << choice << endl;
  
  if (choice == "Y")
    {
      cout << "Enter the xlow input: " << endl;
      cin >> xlow;
      cout << "Enter the ylow input: " << endl;
      cin >> ylow;
      cout << "Enter the xhigh input: " << endl;
      cin >> xhigh;
      cout << "Enter the yhigh input: " << endl;
      cin >> yhigh;
      
      //Ask for user Input for c1, c2, c3, c4                                                                                         
      cout << "Please specify the Background Color:" <<endl;
      cin >> background;
      cout << "Please specify the Foreground Color:" <<endl;
      cin >> foreground;
      cout << "Please specify the Color to which the foreground is to be changed:" << endl;
      cin >> processed;
      cout << "Please specify the Color of the bounding box:" << endl;
      cin >> bounding;
    
      //      color c1, c2, c3, c4;
      c1 = GetColor(background);
      c2 = GetColor(foreground);
      c3 = GetColor(processed);
      c4 = GetColor(bounding);
    }
  else if (choice == "N")
    {
      xlow = 0;
      ylow = 0;
      xhigh = Img.TellWidth() -1;
      yhigh = Img.TellHeight() - 1;
      c1 = GetColor("white");
      c2 = GetColor("black");
      c3 = GetColor("green");
      c4 = GetColor("red");
    }

  //call label                                                                                                                    
  label(Img, 0, Img.TellWidth(), 0, Img.TellHeight(), c1, c2, c3, c4);
 
  //write to file
 Img.WriteToFile(argv[2]);
  
  return 0;
}

