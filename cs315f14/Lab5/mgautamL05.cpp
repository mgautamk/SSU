//*********************************************************************************
//Author:Mahesh Gautam
//Class: CS315 Fall 2014
//Instructor: Dr. Bala Ravikumar
//Assignment: Lab05
//Description: This program takes a string Input from end user, builds the list and
//prints all the keys in the list with their depth.Then it takes two Integer values
//j and k from end user and changes the j-th term of the list to k, and finally it 
//prints the updated list
//********************************************************************************
#include <iostream>
#include<string>
#include "node.cpp"
#include "stack.cpp"
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void token(string str, vector<string>& T)
{//This function runs though each character from the string and pushes
  //digits and brackets into a vector of strings
  string token;
  int idx;
  int str_size = str.size();
  char buffer[20];
  for (int i = 0; i < str_size; i++)
    {
     if(str[i] == '[')
	{
	  T.push_back("[");
	}//end if
     else if(str[i] == ']')
       {
	 T.push_back("]");
       }// end else if
      
      int idx = 0;
      while (i < str_size && isdigit(str[i]) || str[i] == '-')
	{
	  buffer[idx] = str[i];
	  ++i;
	  ++idx;
	}

      if(idx > 0)
	{
	  buffer[idx] = '\0';
	  T.push_back(string(buffer));
	  --i;
	}
    }
}

Node* convert(vector<string>& T)
{//This function inputs an array of tokens and outputs a nested list
  //containing the tokens in T
  Stack S;
  int token_size = T.size();
  for (int k = 0; k < token_size; k++)
    {
      if(T[k] == "[")
	{
	  S.Push(new Node(NULL, NULL));
	}// end if
      else if(T[k] == "]")
	{
	  Node * n = new Node(S.Pop(), NULL);
	  while(S.Top()->isNumber() || S.Top()->getDown() != NULL)
	    {
	      n = new Node(S.Pop(), n);
	    }// end while
	  S.Pop();
	  S.Push(n);
	}// end else if
      else
	{
	  S.Push(new Node(atoi(T[k].c_str())));
	}// end else
    }// end for
  return S.Pop();
}// end convert



int main()
{//main function calles other two functions after asking end user
  //for the input of strings then prints out the updated list
  string input;
  cout <<"Please Enter a list of strings:" << endl;
  getline(cin,input);
  vector<string> T;
  token(input, T);
  Node* N = convert(T);
  N->print(0);
  cout << endl;
  int j,k;
  cout <<"Please Enter two numbers: First number as the position "<< endl;
  cout <<"and second number as the key to be updated" <<endl;
  cin >> j >> k;
  N->update(j,k);
  cout <<"Your Updated List:"<<endl;
  N->print(0);
  cout << endl;
  return 0;
} 
