#!/usr/bin/python
import fileinput
import sys
from fractions import Fraction

def ReadFractions(filename):
    fractions = []
    with open(filename) as f:
        lines = f.read().splitlines()
        for line in lines:
            whole = line.split(" ")[0]
            frac = whole.split("/")[1]
            whole = int(whole)
            frac = Fraction(frac)

            sign = -1 if whole < 0 or frac.numerator < 0 else 1
            whole = abs(whole)
            frac = abs(frac)

            fractions.append((whole + frac) * sign)
    return fractions

def main(argv):
    fractions = ReadFractions(argv)

if __name__=="__main__":
    main(sys.argv[1:])
