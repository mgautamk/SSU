//************************************************************************************
//Estimated time spent ~ 7 hours
//File: vector.h
//Assignment: Homework 4
//Author: Mahesh Gautam
//Date: Spring 2016
//Description: This program takes in a input file containing fractions via command line
//argument, sorts them, reduces them, calculates their sum, and prints the sum and the
//sorted fractions in the same order as they came in i.e (whole, numerator/denominator)
//**************************************************************************************
#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <string.h>

typedef struct {
  void *data;
  int typeSize;
  int capacity;
  int count;
} vector;

vector *vector_new(int typeSize);
void vector_grow(vector *v);
void *vector_get(vector *v, int index);
void vector_copy_item(vector *v, void* dest, int index);
int vector_count(vector *v);
void vector_pushback(vector *v, void *data);


#endif
