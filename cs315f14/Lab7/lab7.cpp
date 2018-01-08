//****************************************************************************************
//Author: Mahesh Gautam
//Class: CS 315 Fall 2014
//Instructor: Dr. Bala RaviKumar
//Description: This program builds AVL tree and Binary search Tree using a text file
//provided by the end user. It calculates the time taken to build each tree so the user 
//knows the effectiveness of using one vs the other in different situations. It also allows
//end user to search for a specific word in the index or save the index to a file.
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

//boolean function that returns true for each punctutions except for '
bool Ispunct(char c){
  if (ispunct(c)){
    if (c == '\'')
      return false;
    return true;
  }
  else
    return false;
}

//function bldTree to build AVL Tree and Binary Search Tree
void buildTree(char file[], AvlTree<string> &AVL, BinarySearchTree<string> &BST)
{
  ifstream txtfile;
  string word;
  string line;
  int wordcount = 0;
  int linecount= 0;
  int distinctwords = 0;
 
  //Insert in AVL Tree
  double finish_time;
  double start_time = clock();//capture the clock time 
  double time;
  txtfile.open(file);
  while (getline(txtfile, line))
    {
      linecount++;
      istringstream iss(line);
      while (iss >> word)
	{
	  wordcount++;
	  if(!(AVL.contains(word)))
	    distinctwords++;
	  int len = word.size();
	  for (int i = 0; i < len; i++)
	    {
	      if(Ispunct(word[i]))
		{
		  word.erase(i--, 1);
		  len = word.size();
		}
	    }
	  AVL.insert(word, linecount);
	}
    }
  finish_time = clock(); //recapture the time 
  time = (double)(finish_time - start_time)/CLOCKS_PER_SEC;
  txtfile.close();//close the file 
  cout <<"Total number of words: " << wordcount << endl;
  cout <<"Total number of distinct words:" << distinctwords<< endl;
  cout <<"Time taken to build index using AVL: " << time << endl;
  cout << endl;
  linecount = 0;
  wordcount = 0;
  distinctwords = 0;
  
  txtfile.open(file);//reopen file
  //Insert in BST Tree
  start_time = clock();
  while (getline(txtfile, line))//read each line
    {
      linecount++;
      istringstream iss(line);
      while (iss >> word) //read each word
	{
	  wordcount++;
	  if(!(BST.contains(word)))
	    distinctwords++;
	  int length = word.size();
	  //filter out punctuations 
	  for (int j = 0; j < length; j++)
	    {
	      if(Ispunct(word[j]))
		{
		  word.erase(j--, 1);
		  length = word.size();
		}
	    }
	  BST.insert(word, linecount);
	}
    }
  finish_time = clock(); //recapture time
  time = (double)(finish_time - start_time)/CLOCKS_PER_SEC;
  txtfile.close();//close the file
  cout <<"Total number of words: " << wordcount << endl;
  cout <<"Total number of distinct words:" << distinctwords << endl;
  cout <<"Time taken to build index using BST is " << time <<endl;
  cout << endl; 
}

//main function
int main(int argc, char* argv[])
{
  char file;
  AvlTree<string> AVL;
  BinarySearchTree<string> BST;
  //  ofstream redirect_file("index.txt");
  string word;
  int linecount;
  //call buildTree
  buildTree(argv[1],AVL, BST);
  int options1;
  char options = 0;
  do
    {
      cout << "Options (1) Display index, (2) search, (3) save index, (4) quit " << endl;
      cin >> options;options1 = options-'0';
      if (options1 ==  1)//Display to screen
	{
	  //Display the AVL Tree  Index
	  cout << "Printing AVL Tree: " <<endl;
	  cout <<"--------------------------------------------------------------"<< endl;
	  AVL.printTree();
	  
	  //Display the BST Tree Index
	  cout <<"Printing BST Tree: " <<endl;
	  cout <<"--------------------------------------------------------------"<< endl;
	  BST.printTree();
	}
      else if(options1 == 2) //Search and return string with line number
	{
	  //ask for word to search
	  cout <<"Search word: ";
	  cin >> word;
	  AVL.printsearch(AVL.search(word, AVL.GetRoot()));
	}
      
      else if (options1 == 3)//Redirection to a output file
	{
	  string filename;
	  cout <<"Enter the Filename: ";
	  cin >> filename;
	  ofstream redirect_file(filename);
	  //save output buffer to cout
	  streambuf * strm_buffer = cout.rdbuf();
	  
	  //redirect output into file
	  cout.rdbuf(redirect_file.rdbuf());
	  
	  //call print funciton
	  cout <<"------------------AVL TREE INDEX----------------------------------" << endl;
	  AVL.printTree();
	  cout << "*****************************************************************" << endl;
	  cout <<"------------------BST TREE INDEX----------------------------------" <<endl;
	  BST.printTree();
	  
	  //restore old buffer
	  cout.rdbuf(strm_buffer);
	  cout <<"Saved" <<endl;
	}
      else if (options1 == 4)
	return 1;
      else 
	{
	  cout <<"Please Enter a number between 1 and 4:" <<endl;
	}
    }
  while((options1 != 4) || isalpha(options));//while condition for do while 
  return 0;
}//end main

