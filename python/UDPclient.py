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

target_host = os.getenv(IP, 0.0.0.0)
target_port = os.getenv(PORT, 8080)

#create a socket object
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#send data
client.sendto("AAABBBCCC", (target_host, target_port))

#receive data
data, addr = client.recvfrom(4096)

print data