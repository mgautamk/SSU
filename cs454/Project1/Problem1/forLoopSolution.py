#!/usr/bin/python

import sys

def main(n=None):
    if n == None:
        n = raw_input("Please input the size of the board (0-1000): ")
    a = [0] * ( int(n) + 1 )
    a[1] = 1 # Size of 1 black tile
    a[2] = 2 # two black, one red 
    a[3] = 4 # Black/red, red/black, green, 3 black
    a[4] = 8 # red/red, red/black/black, 
             # black/black/red, black/red/black, 
             # green/black, black/green, blue, 4 black 

    if int(n) < 0 or int(n) > 1000:
        sys.exit(1)
    
    for i in range( 5, int(n)+1 ):
        a[i] = a[i - 1] + a[i - 2] + a[i - 3] + a[i - 4]
    
    total = a[-1]
    print "Solution for forLoopSolution: \t\t" + str(total)

if __name__ == "__main__":
    main()
