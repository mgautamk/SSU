//****************************************************************************************
//Author: Mahesh Gautam
//Assignment: Lab08
//Class: CS 315 Fall 2014
//Instructor: Dr. Bala RaviKumar
//Description: This program builds AVL tree and Binary search Tree using a text file
//provided by the end user. It calculates the Rank of each keys in the file and outputs 
//it into a file maitaining the size . It also finds the keys for each rank and outputs 
//the keys to another file as they are being deleted. Each Tree type will have two output
//files out1.txt and out2.txt after running the program
//****************************************************************************************
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include "AVLTree.h"
#include "BinarySearchTree.h"
#include <string>
#include <time.h>

using namespace std;

//function bldTree to build Binary Search Tree
void buildBsTree(char file[], BinarySearchTree<int> &BST)
{

  ifstream infile;
  infile.open(file);
  int numbers;
  int ranks;
  //declare a file to redirect output to
  ofstream redirect_file("BSTout1.txt");
  //save output buffer to cout
  streambuf * strm_buffer = cout.rdbuf();
  //redirect output into a file
  cout.rdbuf(redirect_file.rdbuf()); 
  while (infile >> numbers)
    {
      BST.insert(numbers);
      cout << BST.RankOfKey(numbers) << endl;

    }
  //restore old buffer                                                                             
  cout.rdbuf(strm_buffer);
  //close the infile
  infile.close();
}

//function to build AVL tree
void buildAvlTree(char file[], AvlTree<int> &AVL)
{
  ifstream infile;
  //opne the file again
  infile.open(file);
  int numbers;
  int ranks;

  //declare a file to redirect output to
  ofstream redirect_file_avl("AVLout1.txt");
  //save output buffer to cout
  streambuf * strm_buffer = cout.rdbuf();
  //redirect output into a file
  cout.rdbuf(redirect_file_avl.rdbuf());
  while(infile >> numbers)
    {
      AVL.insert(numbers);
      cout << AVL.RankOfKey(numbers) << endl;
    }
  //restore old buffer
  cout.rdbuf(strm_buffer);
  //close the infile
  infile.close();
}
//main function
int main(int argc, char* argv[])
{
  char file;
  AvlTree<int> AVL;
  BinarySearchTree<int> BST;
  int rank;
  int display1;
  char display;
  do
    {
      cout <<"(1) AVL Tree (2) BST (3) Quit"<< endl;
      cin>> display; display1 = display -'0';
      if (display1 ==1)
	{
	  buildAvlTree(argv[1], AVL);
	  ofstream redirect_file("AVLout2.txt"); //save output buffer                                                                              
	  streambuf * strm_buffer = cout.rdbuf();                                              
	  cout.rdbuf(redirect_file.rdbuf());	//redirect output to a file
	  int size = AVL.size();
	  while(size/2 != 0)
	    {
	      int key = AVL.KeyOfRank(size/2);
	      size--;
	      cout << key << endl;
	      AVL.remove(key);
	    }
	  cout.rdbuf(strm_buffer);//restore old buffer
	  cout <<"Saved to AVLout1.txt" << endl;
	  cout <<"Saved to AVLout2.txt" <<endl;
	}
      else if (display1 == 2)
	{
	  buildBsTree(argv[1], BST);
	  ofstream redirect_file_avl("BSTout2.txt");
	  streambuf * strm_buffer = cout.rdbuf();
	  cout.rdbuf(redirect_file_avl.rdbuf());//redirect output to file
	  int Bsize = BST.size();
	  while(Bsize/2 != 0)
	    {
	      int Bkey = BST.KeyOfRank(Bsize/2);
	      Bsize--;
	      cout << Bkey << endl;
	      BST.remove(Bkey);
	    }
	  cout.rdbuf(strm_buffer);//restore old buffer
	  cout <<"Saved to BSTout1.txt" << endl;
          cout <<"Saved to BSTout2.txt" <<endl;
	}
      else if (display1 == 3)
	return 0;
      else
	{
	  cout <<"Please Enter 1, 2 or 3" << endl;
	}
    }//end do 
  while((display != 3) || isalpha(display));//while condition for do while
    return 0;
}//end main



