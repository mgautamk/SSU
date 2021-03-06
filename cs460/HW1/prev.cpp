/* ********************************************************************************
Author: Mahesh Gautam
Class: CS 460 Programming Langauges
Instructor: Dr. Tia Watts
Assignment: HomeWork 1
Desctiption: This program takes fractions from a input file as a whole number, 
numerator, and denominator each seperated by spaces and each fraction seperated 
by new lines, sorts them in a reduced fraction format and prints them to a console. 
***********************************************************************************/
#include <iostream> //input output
#include <fstream> //file stream
#include <sstream> //string stream
#include <string>  //string
#include <stdlib.h> //abs value
#include <vector> //vector
#include <algorithm> //sort

using namespace std;

class Fraction {
public:
  Fraction(string inputString);
  bool operator<(Fraction other) const;
  void printFraction() const;
private:
  int wholeNumber;
  int numerator;
  int denominator;
  double value;
};

Fraction::Fraction(string inputString){

  //read numbers into a stream
  stringstream fractionStream;
  fractionStream << inputString;

  //initialize
  fractionStream >> wholeNumber;
  fractionStream >> numerator;

  char divisorSign;
  fractionStream >> divisorSign;

  fractionStream >> denominator;

  //numerator = ((wholeNumber)/abs(wholeNumber)) * numerator;
  //  wholeNumber = abs(wholeNumber);

  value = ((wholeNumber) + (double(numerator) / (denominator)));
}

//fractions order based on value
bool Fraction::operator<(Fraction other) const {
  return value < other.value;
}

//print in the same order as they came in
void Fraction::printFraction() const{
  
  cout << wholeNumber << " " << numerator << "/" << denominator << endl;
}

int main(int argc, char* argv[]){
  //declare fraction vector under Fraction class
  vector<Fraction> fractions;

  if (argc > 1){
    cout << "argv[1] = " << argv[1] << endl;
  }
  else {
    cout << "No FileName Entered! Exiting..." << endl;
    return -1;
  }

  ifstream infile(argv[1]); //open file

  if(infile.is_open() && infile.good()){
      string line;
      while(getline(infile, line)){
	fractions.push_back(Fraction(line));
      }//end while

      //sort
      sort(fractions.begin(), fractions.end());

      for (vector<Fraction>::iterator i =fractions.begin();
	   i != fractions.end(); i++){
	i->printFraction();
      }//end of for loop
      
    }//end of if
    else {
      cout << "Failed to open file..";
    } //end else

    infile.close();
    return 0;
}
