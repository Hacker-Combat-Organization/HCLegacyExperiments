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

import socket
import threading

bind_ip = "0.0.0.0"
bind_port = 9999

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind((bind_ip, bind_port)) #1

server.listen(5) #2

print "[*] Listening on %s:%d" % (bind_ip, bind_port)

#client handling threading
def handle_client(client_socket): #3

	#print out what client sends 
	request = client_socket.recv(1024)

	print"[*] Received: %s" % request

	#send back a packet
	client_socket.send("ACK!")

	client_socket.close()

while True:

	client, addr = server.accept() #4

	print "[*] Accepted connection from: %s:%d" % (addr[0], addr[1])

	#spin up our client thread to handle incoming data 
	client_handler = threading.Thread(target=handle_client, args=(client,))
	client_handler.start() #5
