#include "fraction.h"
#include <iostream>     // cin, cout
#include <fstream>
#include <vector>       // vector
#include <algorithm>    // sort
#include "SetLimits.h"

using namespace std;

string printValid(bool V) {
  string pv;
  if (V == true)
    pv = " (valid)";
  else if (V == false)
    pv =  " (invalid)";
  else
    pv = " (valid)";
  return pv;
}

int main(int argc, char* argv[]) {
  //declare and reserve plenty of space
  vector<Fraction> fractions;
  fractions.reserve(50000);
  SetLimits();
  //exit if no filename entered
  if (argc <= 1) {
    cout << "No fileName entered, exiting.....!" << endl;
    return -1;
  }
    // open fraction file
    ifstream fractionFile(argv[1]);

    // exit if file was unable to open
    if (!fractionFile.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }


    
    // create all the fractions
    Fraction fractionSum = Fraction(0,0,1);
    Fraction fractionProd = Fraction(1,0,1);
    Fraction fraction;

    if (fractionFile.is_open() && fractionFile.good()) {

    while (fractionFile >> fraction) {
      //      if (fraction.Valid()) { 
        fractions.push_back(fraction); 
        fractionSum += fraction;
	//	fractionProd *= fraction;
	// }
    }
    cout << "vector size " << fractions.size() << endl;
    //Initialize first fraction to first in vector and use minusequals
    Fraction fractionDiff = fractions[0];
    //    for (int i = 0; i < fractions.size() - 1; i++) {
      //  fractionDiff -= fractions[i+1];
    // }
    
    //Initialize first fraction to the first in vector and use Divide 
    Fraction fractionDiv = fractions[0];
    //    for (int i = 0; i < fractions.size() - 1; i++) {
      // if (fraction.Valid())
	//	fractionDiv /= fractions[i+1];
	//      else
	//	fractionDiv = Fraction(1, 0, 1);
    //	    }
    cout << "Before Sorting " <<endl;
    cout << "The sum of the fractions is: " << fractionSum << printValid(fractionSum.Valid()) << "\n";
    //    cout << "The difference of the fractions is: " << fractionDiff <<printValid(fractionDiff.Valid()) << "\n";
    //  cout << "The Product of the fractions is: " << fractionProd << printValid(fractionProd.Valid()) <<"\n";
    //  cout << "The Division of the fractions is: " << fractionDiv << printValid(fractionDiv.Valid()) <<"\n";
    }//close of  isgood and is_open

    // print the fractions
    for (int i = 0; i < fractions.size(); ++i) {
      cout << fractions[i] << "\n";
    }                                      
    
    //SORT THE FRACTIONS
    sort(fractions.begin(), fractions.end());

    /*
     
    //re-initialize
    fractionSum = Fraction(0,0,1);
    fractionProd = Fraction(1,0,1);

    //calculate Sum and Product
    for (int i = 0; i < fractions.size(); i++) {
      fractionSum += fractions[i];
       fractionProd *= fractions[i];
    }
    //calculate difference after sort 
    Fraction fractionDiffAfterSort = fractions[0];
    for (int i = 0; i < fractions.size() - 1; i++) {
      fractionDiffAfterSort -= fractions[i+1];

    }

    //calculate division after sort 
    Fraction fractionDivAfterSort = fractions[0];
    //put the IsValid check here as well 
    for (int i = 0; i < fractions.size() - 1; i++) {
      fractionDivAfterSort /= fractions[i+1];

    }
    //close infile
    fractionFile.close();
    cout << endl;
    cout << "After Sorting " << endl; 
    cout << "The sum of the fractions is: " << fractionSum << printValid(fractionSum.Valid()) <<"\n";
    //  cout << "The difference of the fractions is: " << fractionDiffAfterSort << printValid(fractionDiffAfterSort.Valid()) <<"\n";
    // cout << "The Product of the fractions is: " << fractionProd << printValid(fractionProd.Valid()) <<"\n";
    // cout << "The Division of the fractions is: " << fractionDivAfterSort <<printValid(fractionDivAfterSort.Valid()) << "\n";
   
    // print the fractions
    for (int i = 0; i < fractions.size(); ++i) {
        cout << fractions[i] << "\n";
    }
    */
    return 0;
}
