#!/usr/bin/python
import sys
import getopt
from Queue import *

transition_table = [] 

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "x:s:")
    except getopt.GetoptError as err:
        print str(err)
        usage()
    if len(opts) != 2:
        usage()
    x = opts[0][1]
    s = opts[1][1].split(",")

    for i in range(int(x)):
        t = [ i ]
        for symbol in s:
            t.append(delta(i, symbol, x))
        global transition_table
        transition_table.append(t)
    BFS(int(x), s)

def BFS(x, s):
    visited = [False] * x
    parent = [0] * x
    symbols = [0] * x
    q = Queue()
    q.put(0)
    while (True):
        out = q.get()
        for symbol in s:
            next = delta(out, symbol, x)
            if not visited[next]:
                visited[next] = True
                parent[next] = out;
                symbols[next] = symbol;
                if ( next == 0 ):
                    get_solution(symbols, parent)
                    sys.exit(0)
                q.put(next)

def get_solution(symbols, parent):
    current = 0
    string = [symbols[current]]
    current = parent[current]
    while (current != 0):
        string.append(symbols[current])
        current = parent[current]
    string.reverse()
    output = ''
    for num in string:
        output += num
    print output 

def print_table():
    global transition_table
    for row in transition_table:
        print row

def delta(state, symbol, x):
    return (int(state)*10 + int(symbol)) % int(x)

def usage():
    print "./problem2.py [-x] X-Value [-s] Results set"
    print "Example:"
    print "./problem2.py -x 381 -s 4,7"
    sys.exit(2)

if __name__ == "__main__":
    main()
