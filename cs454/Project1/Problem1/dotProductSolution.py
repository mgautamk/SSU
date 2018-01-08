#!/usr/bin/python

import sys

product = [ 0, 0, 0, 1 ]

def main(n=None):
    if (n == None):
        n = raw_input("Please input the size of the board (0-1000): ")

    if int(n) < 0 or int(n) > 1000:
        sys.exit(1)
    
    for i in range( 1+3, int(n) + 1 + 3):
        product.append(product[i-1] + product[i-2] +
                       product[i-3] + product[i-4])

    print "Solution for dot product: \t\t" + str(product[int(n)+3])

if __name__ == "__main__":
    main()
