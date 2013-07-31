#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/un.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static float IPC_version = IPC_VERSION;

int IPC_init(int listenNum,int sendNum);
int IPC_close();
int IPC_peek(int* mess, int* len);
int IPC_recv(char* buff, int len);
int IPC_send(int program, int message, char* buff, int len);

float get_version();


