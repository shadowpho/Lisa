CC = gcc
CFLAGS = -rdynamic -ldl -g -c -Wall
VERSION = -DIPC_VERSION=0.1

all: test_IPC

test_IPC: test_IPC.o
	$(CC) $(VERSION) test_IPC.o -o test_IPC 
test_IPC.o: test_IPC.c test_IPC.h
	$(CC) $(CFLAGS) $(VERSION) test_IPC.c 
clean:
	rm -rf *.o test_IPC
