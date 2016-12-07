#CC     =       cc
CC      =       gcc
ROOT    =       /ilab/ilab_users/ge82/Asst2
FLAGS   =       -g -Wall
COMPILE =       $(CC) $(FLAGS)

all:    server clientlib

server:         netserverfile.c 
		$(COMPILE)  -pthread -o netserverfile netserverfile.c

clientlib:			libnetfiles.c libnetfiles.h
		$(COMPILE) -c libnetfiles libnetfiles.c
		
clean:
		rm -rf  netserverfile libnetfiles