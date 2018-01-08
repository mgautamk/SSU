#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>

using namespace std;

class Fraction
{
        public:
                Fraction ();    //done
                Fraction (int, int, int);   //done
                Fraction (float);   //todo
                bool Valid () const; //todo
		int Whole() const {   //done
		  return whole;
		};
		int Numerator() const {    //done
		  return numerator;
		};
		int Denominator() const {  //done
		  return denominator;
		};
		
		//long long numerator, denominator, whole;  //done
                bool operator == (const Fraction &) const;
                bool operator != (const Fraction &) const;
                bool operator < (const Fraction &) const;  //done 
                bool operator <= (const Fraction &) const;
                bool operator > (const Fraction &) const;   //done
                bool operator >= (const Fraction &) const;
                Fraction operator + (const Fraction &) const;   //done
                Fraction operator - (const Fraction &) const;   //done
                Fraction operator * (const Fraction &) const;   //todo
                Fraction operator / (const Fraction &) const;   //todo
                Fraction operator += (const Fraction &); 	//done
                Fraction operator -= (const Fraction &);        //done
                Fraction operator *= (const Fraction &);
                Fraction operator /= (const Fraction &);
                friend ostream & operator << (ostream &, const Fraction &);  //done
                friend istream & operator >> (istream &, Fraction &);   //done
        private:
		long long whole, numerator, denominator;
        	void reduce();	//done
        	int gcd(long long a, long long b)const;	//done
};

#endif
