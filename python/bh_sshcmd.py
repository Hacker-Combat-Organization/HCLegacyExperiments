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

import threading
import paramiko#ssh client http://www.paramiko.org
import subprocess

def ssh_command(ip, user, passwd, command):
        client = paramiko.SSHClient()
        #client.load_host_keys('/home/user/.ssh/known_hosts')
        client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        client.connect(ip, username=user, password=passwd)
        ssh_session = client.get_transport().open_session()
        if ssh_session.active:
            ssh_session.exec_command(command)
            print ssh_session.recv(1024)
        return
    
#ssh_command('192.168.100.100', 'dude', 1337hax0r', 'id')