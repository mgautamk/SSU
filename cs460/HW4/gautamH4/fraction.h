//************************************************************************************
//Estimated time spent ~ 7 hours
//File: fraction.h
//Assignment: Homework 4
//Author: Mahesh Gautam
//Date: Spring 2016
//Description: This program takes in a input file containing fractions via command line
//argument, sorts them, reduces them, calculates their sum, and prints the sum and the
//sorted fractions in the same order as they came in i.e (whole, numerator/denominator)
//**************************************************************************************
#ifndef FRACTION_H_
#define FRACTION_H_

#include <stdbool.h>
#include <stdio.h>
//struct to hold numerator, denominator
typedef struct {
  long long numerator;
  long long denominator;
} fraction;

bool fraction_init(FILE *fp, fraction *f); //to initialize our fractions
void fraction_add(fraction *f1, const fraction *f2); //to add fractions
void fraction_print(const fraction *f); //to print fractions in the same order as they came in
long long fraction_gcd(long long a, long long b); //greatest common divisor
int fraction_compare(const void *lhs, const void *rhs); //comparison of fractions based on their natural value


#endif
