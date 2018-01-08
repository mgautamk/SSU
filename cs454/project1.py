#!/usr/bin/python
#**********************************************************************************************
#Autor: Mahesh Gautam
#Class: CS 454
#Instructor: Dr. Bala RaviKumar
#Assignment: Project 1, Question 1
#Fall 2016
#Description: Using a combination of black square tiles and oblong tiles chosen from: red tiles
#measuring two units, green tiles measuring three units, and blue tiles measuring four
#units, it is possible to tile a row measuring five units in length in exactly fifteen
#different ways. This program takes an Integer Input between 0 and 1000 i.e. 'N' and
#outputs the exact number of tiling a 1 by N block.
#***********************************************************************************************
#Ask user for a number between 0 and 1000
x = input("Please enter an Integer between 0 and 1000\n")
if x < 0 or x > 1000:
    print"Invalid number: Please pick a number that is in the range of 0 and 1000!\n"
    quit();

ways, n = [1, 2, 4, 8], x

while len(ways) < n:
    ways += [sum(ways[-4:])]

print "Size of N =", n, ""
print "Number of Tilings for N:", ways[-1]
