#!/usr/bin/python
#Fractions.py
import sys
from fractions import Fraction

def ReadFractions(filename):
    fractions = []
    with open(filename) as f:
	lines = f.read().splitlines()
	for line in lines:
	    whole, frac = line.split()
	    frac = Fraction(frac)
	    whole = int(whole)
            
            sign = -1 if whole < 0 or frac.numerator < 0 else 1
	    whole = abs(whole)
	    frac = abs(frac)
            
            fractions.append((whole + frac) * sign)
            
    return fractions
        
        
def SortFractions(fractions):
    fractions.sort()
    
    
def PrintFractions(fractions):
    for f in fractions:
        sign = 1 if f.numerator > 0 else -1
	n = abs(f.numerator)
	d = abs(f.denominator)
	whole = n // d
	numer = n % d
        
        if whole != 0:
	    whole *= sign
	else:
	    numer *= sign
            
        print("{} {}/{}".format(whole, numer, d))

        
def main():
    fractions = ReadFractions(sys.argv[1])
    SortFractions(fractions)
    PrintFractions(fractions)
    
main()
