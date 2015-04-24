#!/bin/sh

OPT=-O2
#TEST=-DTEST
DEBUG=-g -DDEBUG 
THRIFT_PATH=/usr/local


CFLAGS=-std=c++11 -Wall -Wno-format -fPIC $(OPT) $(DEBUG) $(TEST)

CC=g++
LIBS = -lthrift
INCLUDE_PATH = -I $(THRIFT_PATH)/include/ -I $(THRIFT_PATH)/include/thrift/
LIB_PATH = -L$(THRIFT_PATH)/lib/

OBJS=SmartSync.o smartSync_types.o smartSync_constants.o file.o md5.o checksum.o package.o search.o
OBJSERVER=SmartSync_server.o
OBJCLIENT=SmartSync_client.o



all: server client

server: $(OBJS) $(OBJSERVER)
	$(CC) -o server.exec $^ $(CFLAGS) $(LIBS) $(LIB_PATH)
	
client: $(OBJS) $(OBJCLIENT)
	$(CC) -o client.exec $^ $(CFLAGS) $(LIBS) $(LIB_PATH)
	
%.o: %.cpp
	$(CC) $(INCLUDE_PATH) -c $(CFLAGS) -o $@ $^

clean:
	rm -f *.o server.exec client.exec

rebuild: clean all



