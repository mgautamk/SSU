//************************************************************************************
//Estimated time spent ~ 7 hours
//File: quicksort.c
//Assignment: Homework 4
//Author: Mahesh Gautam
//Date: Spring 2016
//Description: This program takes in a input file containing fractions via command line
//argument, sorts them, reduces them, calculates their sum, and prints the sum and the
//sorted fractions in the same order as they came in i.e (whole, numerator/denominator)
//**************************************************************************************
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"
#include "fraction.h"

//set threashold for selection sort
const int SELECTION_SORT_MAX = 20;

//This function uses quicksort algorithm to sort the fractions
void quicksort(void *left, void *right, int typeSize, compare_func comp) {

  void *middle = left + (((right - left) / typeSize) / 2) * typeSize;
  void *pivot = malloc(typeSize); //use malloc to allocate memory
  memcpy(pivot, middle, typeSize);

  void *i = left;
  void *j = right;

  void *temp = malloc(typeSize);

  while (i <= j) {
    while (comp(i, pivot) < 0) i += typeSize;
    while (comp(j, pivot) > 0) j -= typeSize;

    if ( i <= j) {
      memcpy(temp, i, typeSize);
      memcpy(i, j, typeSize);
      memcpy(j, temp, typeSize);

      i += typeSize;
      j -= typeSize;
    }
  }

  free(temp);
  free(pivot);

  if (left < j) quicksort(left, j, typeSize, comp);
  if (i < right) quicksort(i, right, typeSize, comp);
}

//This function uses quicksort above to sort our fractions
void fraction_quicksort(fraction *array, int left, int right) {
  fraction pivot = array[(right + left) /2];
  int i = left;
  int j = right;

  while (i <= j) {
    //keep count of left and right fractions bening sorted
    while ((array[i].numerator * pivot.denominator - pivot.numerator * array[i].denominator) < 0) ++i;
    while ((array[j].numerator * pivot.denominator - pivot.numerator * array[j].denominator) > 0) --j;

    if (i <= j) {
      fraction temp = array[i];
      array[i] = array[j];
      array[j] = temp;
      ++i;
      --j;
    }
  }

  if (left < j) {
    if (j - left < SELECTION_SORT_MAX) {
      fraction_insertionsort(array, left, j); //call insertion if less than threshold i.e 20
    }
    else {
      fraction_quicksort(array, left, j); //call quicksort otherwise
    }
  }

  if (i < right) {
    if (right - i < SELECTION_SORT_MAX) {
      fraction_insertionsort(array, i, right); //call insertion if less than threshold i.e 20
    }
    else {
      fraction_quicksort(array, i, right); //call  quicksort otherwise
    }
  }
}
//This function uses insertion sort to sort our fractions, this only gets called if there are
//less than 20 (our threshold) fractions 
void fraction_insertionsort(fraction *array, int left, int right) {
  int i = left + 1;
  while (i <= right) {
    fraction f = array[i];
    int j = i;
    while (j > left && (array[j-1].numerator * f.denominator - f.numerator * array[j-1].denominator) > 0) {
      array[j] = array[j-1];
      --j;
    }
    array[j] = f;
    ++i;
  }
}

