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
  void reduceFraction();
private:
  int wholeNumber;
  int numerator;
  int denominator;
  double value;  //for sorting purpose
  int hcf(int x, int y) const;  //highest common factorial
 
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

  //declare temp to keep track of sign multiplier
  int tempsign = 1;


  long long int tempw = wholeNumber;
  long long int tempn = numerator;
  // long long int tempd = denominator;
  
  if (wholeNumber < 0 || numerator < 0) {
    tempsign = -1;
     tempw = abs(tempw);
     tempn = abs(tempn);
  }
  else {
    tempsign = 1;
  }

  //call reduce
  reduceFraction();
  cout << wholeNumber << " " << numerator << " " << denominator << "||";
  //update value for comparison and sorting purpose
  value = (tempw + (double(tempn) / denominator)) * tempsign;
  // value *= tempsign;
}

//less than operator so we can use sort
bool Fraction::operator<(Fraction other) const {
  return value < other.value;
}

//Euclid's algorithm - taken from wikipedia
//This function retruns the highest common factorial or gcd 
  int Fraction::hcf(int x, int y) const {
  if (y == 0) return x;
  else return hcf(y, x % y);
}


void Fraction::reduceFraction() {
  if (numerator > denominator) {
    int tn = (wholeNumber * denominator) + numerator;
    int tw = (tn / denominator );
    tn = tn % denominator;

    numerator = tn;
    wholeNumber = tw;
  }
  if(denominator == 1)
    {
      wholeNumber += numerator;
      numerator = 0;
	
    }
  int divisor = hcf(denominator, numerator);  
  numerator /=  divisor;
  denominator /= divisor;
  } 

//print in the same order as they came in
void Fraction::printFraction() const{
  int Sign;
  if (numerator < 0 || wholeNumber < 0)
    Sign = -1;
  else 
    Sign = 1;
  

  int printWhole;
  int printNumerator;

  if (wholeNumber == 0){
    printWhole = wholeNumber;
    printNumerator = numerator * Sign;
  }
  else { //if whole is not zero
    printWhole = wholeNumber * Sign;
    printNumerator = numerator;
  }
  //cout << "w:" << wholeNumber << numerator << denominator << "||";
  //print numbers and divisor sign
  cout << endl;
  cout << printWhole << " " << printNumerator << "/" << denominator << endl;
}

//main function, takes in a input file via command line
//checks if the file is good, sorts reduced fractions and
//prints them out
int main(int argc, char* argv[]){
  //declare fraction vector under Fraction class
  vector<Fraction> fractions;
  fractions.reserve(500); //allocate space to increase performance

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
