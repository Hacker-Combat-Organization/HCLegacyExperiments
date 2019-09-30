'''
Copyright 2014-Present Hacker Combat Authors
This file is part of the Hacker Combat library.
The Hacker Combat Protocol is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
The Hacker Combat Protocol is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public License
along with the Hacker Combat Protocol library. If not, see <http://www.gnu.org/licenses/>.
'''

import sys
import socket
import threading

def server_loop(local_host, local_port, remote_host, remote_port, receive_first):

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        server.bind((local_host, local_port))
    except:
            print"[!!] Failed to listen on: %s:%d" % (local_host,
            local_port)
            print"[!!] Check for other listening sockets or correct permissions."
            sys.exit(0)
            print "[*] Listening on %s:%d" % (local_host, local_port)

            server.listen(5)

            while True:
                client_socket, addr = server.accept()

                #print out the local conn
                print "[==>] Received incoming connection from %s:%d" %
                (addr[0], addr[1])

                #start thread for remote host
                proxy_thread = threading.Thread(target=proxy_handler,
                args= (client_socket,remote_host,remote_port,receive_first))

                proxy_thread.start()

def proxy_handler(client_socket, remote_host, remote_port, receive_first):

    #connect to remote
    remote_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    remote_socket.connect((remote_host, remoteport))

    #recv data from remote
    if receive_first:

            remote_buffer = receive_from(remote_socket)
            hexdump(remote_buffer)

            #send to response handler
            remote_buffer = response_handler(remote_buffer)

            if len (remote_buffer):
                print "[<==] Sending %d bytes to local." % len(remote_buffer)
                client_socket.send(remote_buffer)




    while True:
            #read from local
            local_buffer = receive_from(client_socket)

            if len(local_buffer):

                print"[==>] Received %d bytes from local." len(local_buffer)
                hexdump(local_buffer)
            
                local_buffer = request_handler(local_buffer)
                
                remote_socket.send(local_buffer)
                print "[==>] Sent to remote."
                
                remote_buffer = receive_from(remote_socket)
                
            if len(remote_buffer):
                print "[<==] Received %d from remote." % len(remote_buffer)
                hexdump(remote_buffer)
                
                remote_buffer = response_handler(remote_buffer)
                
                client_socket.send(remote_buffer)
                
                print"[<==] sent to local."
            #check for lack of data and close
            if not len(local_buffer) or not len(remote_buffer):
                client_socket.close()
                remote_socket.close()
                print"No more datas. All connections closed."
                
                break

def hexdump(src, length=16):
    result = []
    digits = 4 if isinstance(src, unicode) else 2
    for i in xrange(0, len(src), length):
        s = src[i:i+length]
        hexa = b ' '.join(["%0*X" % (digits, ord(x)) for x in s])
        text = b''.join([x if 0x20 <= ord(x) <0x7F else b '.' for x in s])
        result.append(b"%04X %-*s %s" % (i,length*(digits + 1), hexa, text))
    print b'\n'.join(result)
    
def receive_from(connection):
    
    buffer = ""
    
    #set 2 second timeout depending on target adjust as needed.
    connection.settimeout(2)
    
        try:
            #read into buffer until done
            while True:
                data = connection.recv(4096)
                
                if not data:
                    break
                buffer += data
                
        except:
        pass
        return buffer

def request_handler(buffer):
    #|*****************************************|
    #|Welcome to the packet manipulation ZONE! |
    #|*****************************************|
    
    return buffer
                
def response_handler(buffer):
    #|*****************************************|
    #|Welcome to the packet manipulation ZONE! |
    #|*****************************************|
    return buffer
def main():
    #[1:] everything after script name up to 5 args
    if len(sys.argv[1:]) != 5:
        print """Usage: ./tcpProxy.py [localhost] [localport] [remotehost]
        [remote port] [receive_first]"""
        print "Example: ./tcpProxy.py 127.0.0.1 1337 10.12.132.1 1337 True"
        sys.exit(0)
    #set up local listening port
    local_host = sys.argv[1]
    local_port = int(sys.argv[2])
    #remote target
    remote_host = sys.argv[3]
    remote_port = int(sys.argv[4])

    #tell proxy to connect and recv
    #before sending to remote
    receive_first = sys.argv[5]

    if "True" in receive_first:
        receive_first = True
    else:
        receive_first = False
    #turn up listener
    server_loop(local_host,local_port,remote_host,remote_port,receive_first)

main()
