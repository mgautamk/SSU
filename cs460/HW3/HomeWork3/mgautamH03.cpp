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

    // check for proper number of command line arguments
    if (argc != 2) {
        ostream& endl = cerr << "Usage: " << argv[0] << " FILENAME" << endl;
        return 1;
    }

    // open fraction file
    ifstream fractionFile(argv[1]);
    // exit if file was unable to open
    if (!fractionFile.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    // preallocate plenty of space
    vector<Fraction> fractions;
    fractions.reserve(50000);

    Fraction temp = Fraction(1,1,2);
    Fraction temp1 = Fraction (-1,1,2);   
    Fraction result = Fraction(0,0,1);
   
    cout << "Adding these two: " << (temp + temp1) << endl;
    cout << "Substracting these two: " << (temp - temp1) << endl;
    cout << "Multiplying these two: " << (temp * temp1) << endl;
    cout << "Dividing these two: " << (temp / temp1) << endl;
    cout << "Equality: " << (temp == temp1) << endl;
    cout << "Less than or Equal: " << (temp1 <= temp) << endl;

    //check float
    //Fraction floatV = Fraction(0.33);
    
    // create all the fractions
    Fraction fractionSum = Fraction(0,0,1);
    Fraction fractionProd = Fraction(1,0,1);
    Fraction fraction;

    while (fractionFile >> fraction) {
      // if (fraction.Valid()) 
        fractions.push_back(fraction); 
        fractionSum += fraction;
	fractionProd *= fraction;
	
    }
    //Initialize first fraction to first in vector and use minusequals
    Fraction fractionDiff = fractions[0];
    for (int i = 0; i < fractions.size() - 1; i++) {
      fractionDiff -= fractions[i+1];

    }
    
    //Initialize first fraction to the first in vector and use Divide 
    Fraction fractionDiv = fractions[0];
    for (int i = 0; i < fractions.size() - 1; i++) {
      fractionDiv /= fractions[i+1];

    }
    cout << "Before Sorting " <<endl;
    cout << "The sum of the fractions is: " << fractionSum << printValid(fractionSum.Valid()) << "\n";
    cout << "The difference of the fractions is: " << fractionDiff <<printValid(fractionDiff.Valid()) << "\n";
    cout << "The Product of the fractions is: " << fractionProd << printValid(fractionProd.Valid()) <<"\n";
    cout << "The Division of the fractions is: " << fractionDiv << printValid(fractionDiv.Valid()) <<"\n";

    //printour before sort
    /*
    for (int i = 0; i < fractions.size(); i++) {
      cout << fractions[i] << endl;
    } */

    //SORT THE FRACTIONS
    sort(fractions.begin(), fractions.end());

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
    cout << "The difference of the fractions is: " << fractionDiffAfterSort << printValid(fractionDiffAfterSort.Valid()) <<"\n";
    cout << "The Product of the fractions is: " << fractionProd << printValid(fractionProd.Valid()) <<"\n";
    cout << "The Division of the fractions is: " << fractionDivAfterSort <<printValid(fractionDivAfterSort.Valid()) << "\n";
   
    // print the fractions
    for (int i = 0; i < fractions.size(); ++i) {
        cout << fractions[i] << "\n";
    }

    return 0;
}
