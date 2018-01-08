//************************************************************************************
//Estimated time spent ~ 7 hours
//File: quicksort.h
//Assignment: Homework 4
//Author: Mahesh Gautam
//Date: Spring 2016
//Description: This program takes in a input file containing fractions via command line
//argument, sorts them, reduces them, calculates their sum, and prints the sum and the
//sorted fractions in the same order as they came in i.e (whole, numerator/denominator)
//**************************************************************************************
#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include "fraction.h"

typedef int(*compare_func)(const void*, const void*);
void quicksort(void *left, void *right, int typeSize, compare_func comp);
void fraction_quicksort(fraction *array, int left, int right);
void fraction_insertionsort(fraction *array, int left, int right);

#endif

