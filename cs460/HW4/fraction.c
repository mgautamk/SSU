//************************************************************************************
//Estimated time spent ~ 7 hours
//File: fraction.c
//Assignment: Homework 4
//Author: Mahesh Gautam
//Date: Spring 2016
//Description: This program takes in a input file containing fractions via command line
//argument, sorts them, reduces them, calculates their sum, and prints the sum and the
//sorted fractions in the same order as they came in i.e (whole, numerator/denominator)
//**************************************************************************************
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"

//function to initialize fractions
bool fraction_init(FILE *fp, fraction *f) {

  int ch;
  int wholeNumber, multiplier; //multiplier is Sign multiplier
  long long numerator, denominator;

  //stop when end of file reached
  if ((ch = fgetc(fp)) == EOF) return false;

  //initialize whole, numerator, and denominator
  wholeNumber = numerator = denominator = 0;
  multiplier = 1;

  // parse wholeNumber
  if (ch == '-') multiplier = -1;
  else wholeNumber = ch - '0';
  while ( (ch = fgetc(fp)) != ' ' ) {
    wholeNumber = wholeNumber * 10 + ch - '0';
  }
  
  // parse numerator
  ch = fgetc(fp);
  if (ch == '-') multiplier = -1;
  else numerator = ch - '0';
  while ( (ch = fgetc(fp)) != '/' ) {
    numerator = numerator * 10 + ch - '0';
  }
  
  // parse denominator
  while ( (ch = fgetc(fp)) != '\n' ) {
    denominator = denominator * 10 + ch - '0';
  }


  // reduce the numerator and denominator to lowest terms
  long long divisor = fraction_gcd(denominator, numerator);
  numerator = numerator / divisor;
  denominator = denominator / divisor;

  numerator += wholeNumber * denominator;
  numerator *= multiplier;

  // set remaining member variables
  f->numerator = numerator;
  f->denominator = denominator;
  return true;  //all went well - return true
}

//find out greatest common divisor using Euclids algorithm
long long fraction_gcd(long long a, long long b) {
  while (b != 0) {
    long long oldA = a;
    a = b;
    b = oldA % b;
  }
  return a;
}

//This function adds the fraction using greaterst common divisor
void fraction_add(fraction *f1, const fraction *f2) {
  f1->numerator = (f1->numerator * f2->denominator) + (f2->numerator * f1->denominator);
  f1->denominator *= f2->denominator;
  long long divisor = fraction_gcd(f1->denominator, f1->numerator);
  f1->numerator /= divisor;
  f1->denominator /= divisor;
}

//function to print the fractions in the same order as they came in 
void fraction_print(const fraction *f) {
  int wholePrint = f->numerator / f->denominator;
  int numeratorPrint = f->numerator % f->denominator;

  //make sure whole and numerator both dont have negative sign at once
  if (wholePrint < 0 && numeratorPrint < 0) {
    numeratorPrint = -numeratorPrint;
  }
  int denominatorPrint = f->denominator;

  //take absolute value of denominator so its not negative and print everything
  printf("%d %d/%d\n", wholePrint, numeratorPrint, abs((int)f->denominator));
}

//function to compare the fraction so we can use the values to sort our fractions
int fraction_compare(const void *lhs, const void *rhs) {
  fraction *f1 = (fraction*)lhs;
  fraction *f2 = (fraction*)rhs;
  return (f1->numerator * f2-> denominator) - (f2->numerator * f1->denominator);
}
