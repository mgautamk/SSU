#!/usr/bin/python

g=7
p=19

def main():
    areIn = []
    for i in range (1,p):
        generated = (g**i) %p
        print(g, '^', i, '=', generated)
        areIn.append(generated)
        
    areIn.sort()
    print areIn
        
main()
