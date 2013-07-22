CC = gcc
CFLAGS = -fPIC -g -c -Wall
VERSION = -DIPC_VERSION=0.1

all: IPC

IPC: IPC.o
	$(CC) $(VERSION) -shared -Wl,-soname,IPC.so.1 -o IPC.so.0.0.1 IPC.o -lc
IPC.o: IPC.c IPC.h
	$(CC) $(CFLAGS) $(VERSION) IPC.c
clean:
	rm -rf *.o IPC.so.*
