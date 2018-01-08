x#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include "EasyBMP.h"
#include "EasyBMP.cpp"


using namespace std;

struct Frame{
  BMP & image;
  int num;
};

void SetColor(RGBApixel* pix, int Red, int Green, int Blue){
  pix->Red = Red;
  pix->Green = Green;
  pix->Blue = Blue;
  return;
}

void clean_canvas(BMP & img){
  for (int y = 0; y < img.TellHeight(); ++y)
    for (int x = 0; x < img.TellWidth(); ++x){
      SetColor(img(x, y), 255, 255, 255);
    }
}

int random_num(int n){
  int num = rand()%n;
  return num;
}

bool draw_line( BMP& img, int len, int pos, int * keys ){
  if (len > img.TellWidth() || img(1, pos)->Red == 0){
    return false;
  }
  else{
    int color = 0;
    for (int i = 1; i <= len; ++i){
      SetColor( img(i, pos), color, color, color);
    }
    keys[pos/2] = len;
  }
  return true;
  }

bool draw_line( BMP& img, int len, int pos ){
  if (len > img.TellWidth() || img(1, pos)->Red == 0){
    return false;
  }
  else{
    int color = 0;
    for (int i = 1; i <= len; ++i){
      SetColor( img(i, pos), color, color, color);
    }
  }
  return true;
}

char* str_char_conv(string str){
  char* a = new char[str.size()+1];
  a[str.size()] = 0;
  memcpy( a, str.c_str(), str.size() );
  return a;
}


template <typename array>
void print_array(BMP & img, array A){
  img.SetSize( 20*3+2, 20*2+2 );
  clean_canvas(img);
  for (int i = 0; i < A.size(); ++i){
    draw_line(img, A[i], i*2);
  }
}
  
      
void startRandImage(BMP& img, int k, int * A){
  img.SetSize( k*3+2, k*2+2 );
  for (int x = 0; x< img.TellWidth(); ++x)
    for (int y = 0; y < img.TellHeight(); ++y)
      SetColor( img(x,y), 255, 255, 255);
  for (int i = 1; i <= k; ++i){
    while( !draw_line(img, i*3, random_num(k)*2, A));
  }
}

inline int leftChild( int i )
{
  return 2 * i + 1;
}


void percDown( vector<int> & a, int i, int n )
{
  int child;
  int tmp;

  for( tmp = std::move( a[ i ] ); leftChild( i ) < n; i = child )
    {
      child = leftChild( i );
      if( child != n - 1 && a[ child ] < a[ child + 1 ] )
        ++child;
      if( tmp < a[ child ] )
        a[ i ] = std::move( a[ child ] );
      else
        break;
    }
  a[ i ] = std::move( tmp );
}



void heapsort( vector<int> & a, int& itr, vector<Frame> & images )
{
  BMP img;
  for( int i = a.size( ) / 2 - 1; i >= 0; --i )  /* buildHeap */
    percDown( a, i, a.size( ) );
  for( int j = a.size( ) - 1; j > 0; --j )
    {
      itr++;
      img.SetSize( 20*3+2, 20*2+2 );
      std::swap( a[ 0 ], a[ j ] ); /* deleteMax */
      clean_canvas(img);
      print_array(img, a);
      string filename = "out";
      string extension = ".bmp";

      ostringstream convert;
      convert << itr;
      string str_itr = convert.str();
      if (str_itr.size() < 4)
	for (int i = 0; i < 4 - str_itr.size(); ++i)
	  str_itr = "0" + str_itr;

      filename+= str_itr;
      filename+= extension;
      char *file = (char*)filename.c_str();
      img.WriteToFile(file);
      
      Frame temp = {.image = img, .num = itr};
      images.push_back(temp);
      percDown( a, 0, j );
    }
}


int main(){
  system("make");
  srand(time(NULL));
  BMP img;
  int itr = 1;
  int num_keys;
  cout <<"How many Keys:" <<endl;
  cin >> num_keys;
  int keys[num_keys];
  vector<int> array;
  vector<Frame> images;
  startRandImage(img, num_keys, keys);
  for (int i = 0; i < num_keys; ++i)
    array.push_back(keys[i]);
  print_array(img, array);
  img.WriteToFile("out001.bmp");
  Frame first = {.image = img, .num = 1};
  images.push_back(first);
  heapsort(array, itr, images);
  cout << images.size() << endl;

  clean_canvas(img);
  int i;
  //  int num_frames;
  // cout <<"How many fps (Frames Per Second)"<<endl;
  //  cin >> num_frames;
  int end_frame;
  end_frame = images.size();
  char str[80];
  char buffer[4];
  sprintf(str, "./EasyBMPtoAVI -filebase out0 -start 1 -end %d -rescale p350 -output out.avi", end_frame);
  //  itoa(end_frame, buffer, 10);
  //strcpy(str, "./EasyBMPtoAVI -filebase out0 -start 1 -end ");
  //strcat(str, buffer);
  //strcat(str, " -rescale p350 -output out.avi");
  
  system(str);
  //"./EasyBMPtoAVI -filebase out0 -start 1 -end " + end_frame + " -rescale p350 -output out.avi");
  
}
