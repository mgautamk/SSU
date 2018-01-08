//************************************************************************************
//Estimated time spent ~ 7 hours
//File: gautamH4.c
//Assignment: Homework 4
//Author: Mahesh Gautam
//Date: Spring 2016
//Description: This program takes in a input file containing fractions via command line
//argument, sorts them, reduces them, calculates their sum, and prints the sum and the
//sorted fractions in the same order as they came in i.e (whole, numerator/denominator)
//**************************************************************************************
#include <stdio.h>
#include "vector.h"
#include "fraction.h"
#include "quicksort.h"
#include "SetLimits.h"


int main(int argc, char **argv) {

  SetLimits();  //call SetLimits
  //exit if no input file entered 
  if (argc != 2) {
    printf("Input file not provided: ");
    return 1;
  }

  FILE *fp;
  fp = fopen(argv[1], "r"); //open file

  //return if the file is empty
  if (fp == NULL) {
    printf("File empty:");
    return 1;
  }
  vector *fractions = vector_new(sizeof(fraction));  //create and allocate vector
  fraction sum;
  sum.numerator = 0;
  sum.denominator = 1; //initialize to 1 so we dont get a divide by zero

  fraction f;
  //push fractions to vector and calculate their sum as they come in
  while ( fraction_init(fp, &f) ) {
    fraction_add(&sum, &f);
    vector_pushback(fractions, &f);
  }

  //print out sum to console
  printf("The sum of the fractions is: ");
  fraction_print(&sum);
  //count total number of fractions
  int totalFractions = vector_count(fractions);
  fraction *fractionArray = fractions->data;

  //call sort 
  fraction_quicksort(fractionArray, 0, totalFractions - 1);

  //call print 
  int i = 0;
  while (i < totalFractions) {
    fraction_print(&fractionArray[i++]);
  }

  return 0; //all went well 
}
