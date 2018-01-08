#include<iostream>
#include<cmath>
#include<vector>
#include<stdlib.h>

using namespace std;

int insertionSort(vector<int> arr)
{
  int i, j, temp;
  int comp = 0;

  for (i = 1; i < arr.size(); i++)
    {
      j = i;
      while (j > 0 && arr[j - 1] > arr[j]) 
	{
	  ++comp;
	  temp = arr[j];
	  arr[j] = arr[j - 1];
	  arr[j-1] = temp;
	  j--;
	}
    }
  return comp;
}

int main ()
{

  int total = 0;
  int temp;
  vector<int> vect;
  vector<int> comparision;
  srand(time(NULL));
  for (int i = 1; i <= 10; i++)
    {
      cout << i * 10 << "Size" << "\r\n";
      for (int j = 0; j < 1000; j++)
	{
	  for (int k = 0; k < i * 10; k++)
	    {
	      vect.push_back(rand()%(i * 10) + 1);
	    }
	  temp = insertionSort(vect);
	  comparision.push_back(temp);
	  cout << temp << "\xr\n";
	  vect.clear();
	    }
    }
}
