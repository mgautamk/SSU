#include "fraction.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <math.h>

using namespace std;
//default constructor
Fraction::Fraction() {
    numerator = 0;
    denominator = 1;
    V = true;
}
//constructor for int, int , int
Fraction::Fraction(int w, int n, int d) {
  whole = w;
  numerator = n;
  denominator = d;
  bool negative = false;

  if (w < 0) {
    negative = true;
    w = -w;
  }
  else if (n < 0) {
    negative = true;
    n = -n;
  }
  
  //check if valid 
  if (isValid() == true)
    {
      reduce();     
      n += w * d;
      w = 0;
      if (negative) n = -n;
      whole = w;
      numerator = n;
      denominator = d;
    }
}
//constructor for int, int
Fraction::Fraction (int n, int d) {
  numerator = n;
  denominator = d;
  bool negative = false;

  if (n < 0) {
    negative = true;
    n = -n;
  }

  if (isValid() == true)
    {
      reduce();
      if (negative) n = -n;
      numerator = n;
      denominator = d;
    }
}
//Implementation of float to fraction
Fraction::Fraction(float f) {
  whole = int(f);
  float tempNumber = f - whole;
  stringstream ss;
  ss << tempNumber;
  string s = ss.str();
  int size = s.length() -2;

  long long int power = pow(10, size);
  long long int tempNumerator = tempNumber * power;
  numerator = tempNumerator;
  denominator = pow(10,size);
  //get rid of this cout before submitting
  cout << whole << " " << numerator << "/" << denominator << endl;  //for debug only
}
int count_bits( unsigned num){
  unsigned count = 0;
  while(num!=0){
    count++;
    num >>= 1;
  }
  return count;

}


//Check if the fractions are valid
bool Fraction::isValid() {
  V = true;
  if(count_bits(abs(whole)) >= 31 || count_bits(abs(numerator)) >= 31 || count_bits(abs(denominator)) >= 31){
    V = false;
    return false;
  }
  
  else if (denominator == 0) {
      V = false;
      // cout << "Divide by Zero" << endl;
    return false;
    
  }
  else if (denominator < 0) {
      V = false;
      // cout << "Denominator cannot be less than zero" << endl;
    return false;
  }
  else if (numerator < 0 && whole < 0)
    return false;
  V = true;
  return true;

}
//Implementation of Input operator
istream & operator >> (istream &input, Fraction &f) {
	
	int wholeNumber, numerator, denominator;
	char divisorSign;
	input >> wholeNumber >> numerator >> divisorSign >> denominator;
  	bool isNegative = false;
	
	if (wholeNumber < 0) {
		isNegative = true;
		wholeNumber = -wholeNumber;
	}
	else if (numerator < 0){
		isNegative = true;
		numerator = -numerator;
	}
	f.numerator = numerator;
	f.denominator = denominator;
	
	if(!input.fail() && f.isValid() == true) {
		f.numerator = numerator;
		f.denominator = denominator;
		
		f.reduce();
		
		f.numerator += wholeNumber * f.denominator;
		
		if (isNegative) f.numerator = -f.numerator;
	}
	return input;
}

//Implementation of output operator
ostream & operator << (ostream &output, const Fraction &f) {

  int wholePrint;
  int numeratorPrint;
  Fraction tempf = f;
  if (tempf.isValid() == true) {
  
  wholePrint = f.numerator / f.denominator;
  numeratorPrint = f.numerator % f.denominator;

  }
  /*
  else {
    //  f = Fraction(0,0,1);
    }*/
  
  if (wholePrint < 0 && numeratorPrint < 0) {
    numeratorPrint = -numeratorPrint;
  }

  output << wholePrint << " " << numeratorPrint << "/" << f.denominator;
  return output;                                          
 
}

//less than operator to order fractions based on their value
bool Fraction:: operator < (const Fraction &other) const {
	return numerator * other.denominator < other.numerator * denominator;
}

//greater than operator to order fractions based on their value
bool Fraction:: operator > (const Fraction &other) const {
	return numerator * other.denominator > other.numerator * denominator;
}

//Implementation of == operator to check equality
bool Fraction:: operator == (const Fraction &other) const {
  return numerator * other.denominator == other.numerator * denominator;
}

//Implementation of != operator
bool Fraction:: operator != (const Fraction &other) const {
  return numerator * other.denominator != other.numerator * denominator;
}

//Implementation <= operator to check less than or equal to
bool Fraction:: operator <= (const Fraction &other) const {
  return numerator * other.denominator <= other.numerator * denominator;
}

//Implementation of >= operator
bool Fraction:: operator >= (const Fraction &other) const {
  return numerator * other.denominator >= other.numerator * denominator;
}

//Implementation of + operator
Fraction Fraction:: operator + (const Fraction &rhs) const {
  Fraction Sum = Fraction();
  if ( (*this).Valid() == false || rhs.Valid() == false) {
    Sum = *this;
    if (rhs.Valid() == false)
      Sum = rhs;
    Sum.V = false;
    return Sum;
  }
  Sum.numerator = (numerator * rhs.denominator) + (rhs.numerator * denominator);
  Sum.denominator = denominator * rhs.denominator;
  Sum.reduce();
  return Sum;
}

//Implementation of -
Fraction Fraction:: operator - (const Fraction &rhs) const {
  Fraction Difference = Fraction();
  Difference.numerator = (numerator * rhs.denominator) - (rhs.numerator * denominator);
  Difference.denominator = denominator * rhs.denominator;
  Difference.reduce();
  return Difference;
}

//Implementation of multiplication *
Fraction Fraction:: operator * (const Fraction &rhs) const {
  Fraction Product = Fraction();
  Product.numerator = (numerator * rhs.numerator);
  Product.denominator = denominator * rhs.denominator;
  Product.reduce();
  return Product;
}

//Implementation of divide
Fraction Fraction:: operator / (const Fraction &rhs) const {
  Fraction Divide = Fraction();
  int sign = 1;
  if(rhs.numerator < 0)
    sign = -1;
  int tempnumo, tempdeno;
  tempnumo = rhs.denominator;
  tempdeno = rhs.numerator;
  Divide.numerator = (numerator * tempnumo) * sign;
  Divide.denominator = denominator * tempdeno;
  Divide.reduce();
  Divide.denominator = abs(Divide.denominator);
  return Divide;
}
//Implement div equal
Fraction Fraction::operator /= (const Fraction &rhs) {
  Fraction tempDiv = Fraction(1,0,1);
  tempDiv = *this / rhs;
  // tempDiv.reduce();
  tempDiv.denominator = abs(tempDiv.denominator);
  tempDiv.reduce();
  *this = tempDiv;
  return *this;
}

//Implementation of  plus equal operator
Fraction Fraction::operator += (const Fraction &rhs) {
  
  if ( (*this).Valid() == false || rhs.Valid() == false) {
    if (rhs.Valid() == false)
      *this = rhs;
    (*this).V = false;
    return *this;
  }
  
  numerator = (numerator * rhs.denominator) + (rhs.numerator * denominator);
    denominator *= rhs.denominator;
    reduce();
    return *this;
} 

//Implementation of  minus equal operator
Fraction Fraction::operator -= (const Fraction &rhs) {
  // numerator = ((numerator * rhs.denominator) - (rhs.numerator * denominator));
  // denominator *= rhs.denominator;
    *this = *this - rhs; 
    reduce();
    return *this;
}
//Implementation of multiply equal operator
Fraction Fraction::operator *= (const Fraction &rhs) {
  numerator = (numerator * rhs.numerator);
  denominator *= rhs.denominator;
  reduce();
  return *this;
}

// function to reduce the fraction by using gcd
void Fraction::reduce() {
   int divisor = gcd(denominator, abs(numerator)); 
   numerator /= divisor;
  denominator /= divisor;
  /* if (denominator == 0) {
    denominator = 1;
    numerator = 0;
    whole = 0;
    }*/ 
}

//use this to reduce Division fractions 
void Fraction::reduceDivisions() {
  // int divisor = gcd(abs(denominator), numerator); //this works
  int divisor = gcd(denominator, numerator);
  numerator /= divisor;
  denominator /= divisor;
  denominator = abs(denominator);
}

// uses Euclid's algorithm from wiki to find the greatest common divisor
long long Fraction::gcd(unsigned long long a, unsigned long long b) const {

    while (b != 0) {
        long long oldA = a;
        a = b;
        b = oldA % b;
    }
    long long retvalue = a;
    if (retvalue == 0) {
      retvalue = 1;
    }
    return retvalue;
    // return a == 0?1 :a;
}
