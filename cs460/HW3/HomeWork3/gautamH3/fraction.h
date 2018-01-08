#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>

using namespace std;

class Fraction
{
        public:
                Fraction ();    //done
		Fraction (int, int); //done
                Fraction (int, int, int);   //done
                Fraction (float);   //done
                bool Valid () const {
		  return V;
		};
		int Whole() const {   //done
		  return whole;
		};
		int Numerator() const {    //done
		  return numerator;
		};
		int Denominator() const {  //done
		  return denominator;
		};
                bool operator == (const Fraction &) const; //done
		bool operator != (const Fraction &) const; //done
                bool operator < (const Fraction &) const;  //done 
                bool operator <= (const Fraction &) const;  //done
                bool operator > (const Fraction &) const;   //done
                bool operator >= (const Fraction &) const;  //done
                Fraction operator + (const Fraction &) const;   //done
                Fraction operator - (const Fraction &) const;   //done
                Fraction operator * (const Fraction &) const;   //done
                Fraction operator / (const Fraction &) const;   //done
                Fraction operator += (const Fraction &); 	//done
                Fraction operator -= (const Fraction &);        //done
                Fraction operator *= (const Fraction &);        //done
                Fraction operator /= (const Fraction &);         //done
                friend ostream & operator << (ostream &, const Fraction &);  //done
                friend istream & operator >> (istream &, Fraction &);   //done
        private:
		long long  whole, numerator, denominator;  //done
        	void reduce();	//done
		void reduceDivisions(); //done
        	long long gcd(unsigned long long a, unsigned long long b)const;	//done
		bool V;
		bool isValid();
};

#endif
