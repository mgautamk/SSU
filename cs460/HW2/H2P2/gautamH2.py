#!/usr/bin/python
######################################################################################################
#File: gautamH02.py
#Assignment: Homework 2, Phase 2
#Author: Mahesh Gautam
#Date:Spring 2016
#Description: This program takes a input file containing fractions via command line argument,
#sorts them, reduces them and prints them out to the console. Fractions in the file are in the
#order as whole number, space, numerator/denominator.
#######################################################################################################

import sys
import fileinput
from fractions import Fraction
import fractions

#This function reads fractions with the filename provided via command line argument, it
#puts those fractions inside an array after reading them
def ReadFractions(argv):
    infile = fileinput.input()
    fractions = [] #initialize array
    for line in infile:
        wholeNumber = line.split(" ")[0]#split the first part of the fractions
        fractionNumbers = line.split(" ")[1] #second part of the fraction i.e Num/Den
        wholeNumber = int(wholeNumber)
        fractionNumbers = Fraction(fractionNumbers) #converts our fraction to Fraction class
        #set the signMultiplier to -1 if the whole number or numerator is less than zero
        if wholeNumber < 0 or fractionNumbers.numerator < 0:
            signMultiplier = -1
        else:
            signMultiplier = 1
        wholeNumber = abs(wholeNumber)
        fractionNumbers = abs(fractionNumbers)
        fractions.append((wholeNumber + fractionNumbers) * signMultiplier) #append each one
    infile.close()#close file
    return fractions

#This function uses inbuilt fraction sort to sort our fractions
def SortFractions(fractions):
    fractions.sort()
    
def PrintFractions(fractions):
    for item in fractions:
        if item.numerator > 0:
            signMultiplier = 1
        else:
            signMultiplier = -1
        numerator = abs(item.numerator)
        denominator = abs(item.denominator)
        wholeNumber = numerator //denominator
        numerator = numerator % denominator
        #take signMultipliers into consideration for when whole is zero and when its not
        if wholeNumber != 0:
            wholeNumber *= signMultiplier
        else:
            numerator *= signMultiplier 
        #print the fractions in the same order as they came in
        print (str(wholeNumber) + ' ' + str(numerator) + '/' + str(denominator))
#main function
def main():
    fractions = ReadFractions(sys.argv[1:])#argv to provide input file name as command line argument
    #call sort 
    SortFractions(fractions)
    #call print
    PrintFractions(fractions)

        
if __name__ == "__main__":
        main()
