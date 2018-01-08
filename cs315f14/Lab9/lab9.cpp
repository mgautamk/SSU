//*******************************************************************************
//Author: Mahesh Gautam
//Class: CS 315 
//Professor: Dr. Bala RaviKumar
//Assignment: lab 09
//Description: This program takes a Peg Solitare board 7 * 7 and finds the 
//solution to the board using no hashing, single hashing, and double hashing.
//This program also calculates the time taken to solve the board for each method
//hence giving an Idea to the user about affecttiveness of each method.
//********************************************************************************** 
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<sstream>
#include "Common.cpp"


using namespace std;

//Declaring a struct Move as public
struct Move
{
  long long board;
  int start;
  int mid;
  int finish;
};


//fucntion to check if the peg is in the board
bool isPeg(long long board, int index)
{
  return (board & ((long long)1 << index)) != 0;
}

//function to set the peg
void setPeg(long long& board, int index)
{
  board |= (long long)1 << index;
}

//function to clear the peg
void clearPeg(long long& board, int index)
{
  board&= ~((long long)1 << index);
}

//boolean function to check if a position is valid
bool validpos(int idx)
{
  if (idx < 0 || idx > 48)
    return false;
  int col = idx % 7;
  int row = idx / 7;
  bool colcorner = col < 2 || col >= 5;
  bool rowcorner = row < 2 || row >= 5;
  return !(colcorner && rowcorner);
}

//add moves if valid, pass by reference for moves
void addifvalid(long long board,vector<Move> &moves, int start, int mid, int finish)
{
  if (validpos(start) != true || validpos(mid) != true || validpos(finish) != true)
    {
      return;
    }

  if (isPeg(board, start) && isPeg(board, mid) && isPeg(board, finish) != true)
    {
      long long newboard = board;
      clearPeg(newboard, start);
      clearPeg(newboard, mid);
      setPeg(newboard, finish);
      Move m;
      m.board = newboard;
      m.start = start;
      m.mid = mid;
      m.finish = finish;
      moves.push_back(m);
    }
}

//function to find all valid possible moves
void findmoves(long long board, vector<Move> &moves)
{
  for (int i = 0; i < 49; i++)
    {
      int col = i % 7;
      int row = i/7;
      if (col < 5)
	addifvalid(board, moves, i, i+1, i +2);
      if (col > 1)
	addifvalid(board, moves, i, i-1, i -2);
      if (row < 5)
	addifvalid(board, moves, i, i+7, i + 2 * 7);
      if (row > 1)
	addifvalid(board, moves, i, i-7, i - 2 * 7);
    }
}

//true if board is solved
bool solved(long long board)
{
  int count = 0;
  for (int i = 0; i < 49; i++)
    {
      count += (validpos(i)) && isPeg(board, i) ? 1: 0;
    }
  return count == 1;
}

//function to see if the board can be solved or not                                         
bool solve (long long board, vector<Move> &solution)
{
  if (solved(board))
    return true;

  vector<Move> currentMoves;
  findmoves(board, currentMoves);

  for(auto m:currentMoves)
    {
      if(solve(m.board, solution))
	{
	  solution.insert(solution.begin(), m);
	  return true;
	}
    }
  return false;
}

//hsolve function for single hash
bool hsolve (long long board, vector<Move> &solution, HashTable<long long> &H, vector<int> &probes)
{
  int num_probes = 0;
  if (solved(board))
    return true;
  //add hash check and return false if in the hash
  vector<Move> currentMoves;
  findmoves(board, currentMoves);

  for (auto m:currentMoves)
    {
      if (!H.contains(m.board, num_probes))
        {
          if (hsolve(m.board, solution, H, probes))
            {
              solution.insert(solution.begin(), m);
              return true;
            }
          else
            H.insert(m.board, num_probes); //add currentboard to the hash
        }
      //  cout <<num_probes << endl;
      probes.push_back(num_probes);
    }
  return false;
}
//hsolve function for DoubleHash
bool hsolve (long long board, vector<Move> &solution, DoubleHashTable<long long> &H, vector<int> &probes)
{
  int num_probes = 0;
  if (solved(board))
    return true;
  //add hash check and return false if in the hash
  vector<Move> currentMoves;
  findmoves(board, currentMoves);

  for (auto m:currentMoves)
    {
      if (!H.contains(m.board, num_probes))
	{
	  if (hsolve(m.board, solution, H, probes))
	    {
	      solution.insert(solution.begin(), m);
	      return true;
	    }
	  else
	    H.insert(m.board, num_probes); //add currentboard to the hash
	}
      //      cout << num_probes << endl;
      probes.push_back(num_probes);
    }
  return false;
}
	       

//function to print the table
void printTable (long long board)
{
  for (int i = 0; i < 7; i++)
    {
      for (int j = 0; j < 7; j++)
	{
          int idx = i * 7 + j;
	  if (validpos(idx) != true)
	    cout << " ";
	  else if (isPeg(board, idx))
	    cout << 'x';
	  else 
	    cout << '-';
	}
      cout << endl;
    }
}
//build the board
long long buildboard(string filename)
{
  ifstream infile;
  infile.open(filename);
  int posn;
  int length;
  std::string line;
  long long board = 0;
  if(infile.is_open())
    {
      while(std::getline(infile, line))
        {
          length = line.size();
          for (int i = 0; i < length; i++)
            {
              if(ispunct(line[i]))
                {
                  line.erase(i--, 1);
                  length = line.size();
                }
            }
	  std::istringstream iss(line);
          while (iss >> posn)
            {
	       int x = posn%7;
	       int y = posn/7;
              setPeg(board, posn);
              cout << posn << " ";
            }//end while
        }//end while
    }//end if
  cout <<endl;
  infile.close();
  printTable(board);
  return board;
}
//main function
int main(int argc, char* argv[])
{
  double finish_time;
  double start_time;
  double time;
  vector<Move> moves;
  long long board = 0;
  vector<int> probes;
  int options1;
  char options = 0;
  string filename;
  do
    {
      float total_probes;
      cout << "Please select (1) No Hashning (2) Single Hashing (3) Double Hashing (4) Quit" <<endl;
      cin >> options; options1 = options-'0';
      if (options1 < 4)
	{
	  cout <<"Please give a filename:"<<endl;
	  cin>> filename;
	  board = buildboard(filename);
	}
      if (options1 == 1)
	{
	  start_time = clock();
	  if(solve(board, moves))
	    {
	      for(auto m: moves)
		{
		  cout << m.start << " " << m.mid << " " << m.finish << endl;
		  // printTable(m.board);
		}
	      cout << "Solved!" << endl;
	    }
	  else
	    cout << "We cannot solve this board." << endl;
	  cout << endl;
	  finish_time = clock();
	  time = (double)(finish_time - start_time)/CLOCKS_PER_SEC;
	  cout <<"Time take for No Hashing:" << time << endl;
	}//end if when display == 1
      else if (options1 == 2)
	{//single hashing
	  HashTable<long long> hashtable;
	  start_time = clock();
	  total_probes = 0;
	  if(hsolve(board, moves, hashtable, probes))
	    {
	      for(auto m: moves)
		{
		  cout << m.start << " " << m.mid << " " << m.finish << endl;
		  // printTable(m.board);
		}
	      cout << "Solved!" << endl;
	    }
	  else
	    cout << "We cannot solve this board." << endl;
	  cout << endl;
	  finish_time = clock();
	  time = (double)(finish_time - start_time)/CLOCKS_PER_SEC;
	  cout <<"Time taken using Single Hashing:" << time << endl;
	  for (int i = 0; i < probes.size(); i++)
	    total_probes += probes[i];
	  cout <<"Average number of Probes: " << total_probes/probes.size() <<endl;
	  cout <<"(Total probes: "<< total_probes << "   " <<"Probes Size: "<< probes.size() << ")" <<endl;
	}//end if when display =2
      else if (options1 ==3)
	{//double hashing
	  DoubleHashTable<long long> dhashtable;
	  total_probes = 0;
	  start_time = clock();
	  if (hsolve(board, moves, dhashtable, probes))
	    {
	      for(auto m: moves)
		{
		  cout << m.start << " " << m.mid << " " << m.finish << endl;
		  // printTable(m.board);
		}
	      cout << "Solved!" << endl;
	    }
	  else
	    cout << "We cannot solve this board." << endl;
	  cout << endl;
	  finish_time = clock();
	  time = (double)(finish_time - start_time)/CLOCKS_PER_SEC;
	  cout <<"Time taken using Double Hashing:" << time << endl;
	  for (int i = 0; i < probes.size(); i++)
	    total_probes += probes[i];
	  cout <<"Average number of Probes: " <<total_probes/probes.size() << endl;
	  cout << "(Total probes: "<<total_probes <<"   " <<"Probes Size: "<< probes.size() <<")"<< endl;
	}//end if when display = 3
      else if (options1 == 4)
	return 0;
      else 
	cout <<"Please enter a number between 1 and 4"<<endl;
      moves.clear();
      probes.clear();
    }
  while ((options1 != 4) || isalpha(options)); //while cond for do while loop
  return 0;
}//end main
