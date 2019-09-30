#Copyright 2014-Present Hacker Combat Authors
#This file is part of the Hacker Combat library.
#The Hacker Combat Protocol is free software: you can redistribute it and/or modify
#it under the terms of the GNU Lesser General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#The Hacker Combat Protocol is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#GNU Lesser General Public License for more details.
#You should have received a copy of the GNU Lesser General Public License
#along with the Hacker Combat Protocol library. If not, see <http://www.gnu.org/licenses/>.
#mosuitto
CC = g++
IFLAG = -I
LFLAG = -L
TUTLOC = libs/tut-framework-master/include
JSONLOC = libs/ -L/usr/local/Cellar/jsoncpp/0.10.5/lib/ -Llibs/jsoncpp-src-0.5.0/buildscons/linux-gcc-4.2.1/src/lib_json -Llibs/jsoncpp-src-0.5.0/libs/linux-gcc-4.2.1 #-ljsoncpp -ljson_linux-gcc-4.4.3_libmt
W = #-Wall
V = #-v
##-ljson_linux-gcc-4.1.2_libmt
#$(IFLAG)$(JSONLOC)
%.o: %.c
	$(CC) -c -o $@ $<
MainGame: MainGame.cpp	Tests.cpp
	$(CC) $(V) -std=gnu++0x $(W) -o $@ $^ $(IFLAG)$(TUTLOC) -I./libs/jsoncpp/include/ -L./libs/jsoncpp/libs/ -ljsoncpp
	#./$@
	#./$@ test
	#rm ./$@
play: MainGame.cpp	Tests.cpp
	$(CC) -std=gnu++0x $(W) -o $@ $^ $(IFLAG)$(TUTLOC)
	./$@ $@
	rm ./$@
.PHONY: clean
