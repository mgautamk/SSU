#!/usr/bin/python
#Fractions.py

import sys
import fileinput
from fractions import Fraction


def main(argv):
    infile = fileinput.input()
    fractions = []
    for line in infile:
        whole = line.split(" ")[0]
        frac = line.split(" ")[1]
        whole = int(whole)
        frac = Fraction(frac)
        if whole < 0 or frac.numerator < 0:
            sign = -1
        else:
            sign = 1
        whole = abs(whole)
        frac = abs(frac)
        fractions.append((whole + frac) * sign)
    infile.close()
    return fractions

def PrintFractions(fractions):
    for f in fractions:
        if f.numerator > 0:
            sign = 1
        else:
            sign = -1
        n = abs(f.numerator)
        d = abs(f.denominator)
        whole = n //d
        numerator = n % d
        
        print ("{} {}/{}".format(whole, numer, d))



        
if __name__ == "__main__":
        main(sys.argv[1:])
