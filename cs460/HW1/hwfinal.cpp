/* ********************************************************************************
Author: Mahesh Gautam
Class: CS 460 Programming Langauges
Instructor: Dr. Tia Watts
Assignment: HomeWork 1
Time taken Estiamte: 5 hours approximately 
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

//declare class and objects
class Fraction {
public:
  Fraction(string inputString);
  bool operator<(Fraction other) const;
  void printFraction() const;
private:
  int wholeNumber;
  int numerator;
  int denominator;
  int productSign; //keep track of negative numbers
  double value;  //for sorting purpose
  int hcf(int x, int y) const;  //highest common factorial
  void reduceFraction(); 
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

  if (numerator < 0 || wholeNumber < 0){
    productSign = -1;
    wholeNumber = abs(wholeNumber);
    numerator = abs(numerator);
  }//end if
  else {
    productSign = 1;
  }

  //call reduceFraction function to reduce fractions
  reduceFraction();

  //update value for comparison and sorting purpose
  value = (wholeNumber + (double(numerator) / denominator))* productSign;
}

//less than operator so we can use sort
bool Fraction::operator<(Fraction other) const {
  return value < other.value;
}

//Euclid's algorithm - taken from wikipedia
//This function retruns the highest common factorial
int Fraction::hcf(int x, int y) const {
  if (y == 0) return x;
  else return hcf(y, x % y);
}


//function to reduce the fraction to lowest terms
void Fraction::reduceFraction(){
  int improperWhole;
  if(numerator >= denominator) {

    improperWhole = numerator / denominator;
    numerator = numerator % denominator;

    wholeNumber += improperWhole;
  }

  int divisor = hcf(denominator, numerator);
  numerator /= divisor;
  denominator /= divisor;
}

//print in the same order as they came in
void Fraction::printFraction() const{
  int printWhole;
  int printNumerator;

  if (wholeNumber == 0){
    printWhole = wholeNumber;
    printNumerator = numerator * productSign;
  }
  else { //if whole is zero
    printWhole = wholeNumber * productSign;
    printNumerator = numerator;
  }
  //print numers and divisor sign  
  cout << printWhole << " " << printNumerator << "/" << denominator << endl;
}

//main function, takes in a input file via command line
//checks if the file is good, sorts reduced fractions and
//prints them out
int main(int argc, char* argv[]){
  //declare fraction vector under Fraction class
  vector<Fraction> fractions;

  if (argc <= 1){
    cout << "No FileName Entered! Exiting..." << endl;
    return -1;
  }

  ifstream infile(argv[1]); //open file

  if(infile.is_open() && infile.good()){//if file open and good
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

  infile.close(); //close file
    return 0;
}
