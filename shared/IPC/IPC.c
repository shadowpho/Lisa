#include "IPC.h"

int static MASTER_LISTEN_SOCKET = 0;
int static MASTER_SEND_SOCKET = 0;

int static MASTER_LISTEN_PORT=0;
int static MASTER_SEND_PORT=0;

int IPC_init(int listenNum,int sendNum)
{
    const char CON_PRE[] = "IPC_";
    struct sockaddr_un addr;

    MASTER_LISTEN_PORT = listenNum;
    MASTER_SEND_PORT = sendNum;

    if((MASTER_LISTEN_SOCKET = socket(AF_LOCAL, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0))==-1)
        return -1;
    if((MASTER_SEND_SOCKET =   socket(AF_LOCAL, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0))==-1)
        return -1;
    //get the sockaddr_un in right order
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family=AF_LOCAL;
    strncpy(addr.sun_path, CON_PRE,sizeof(CON_PRE));
    char * buff = malloc(33); //33 = max return size of itoa
    sprintf(buff, "%d",MASTER_LISTEN_SOCKET);
    strncpy(addr.sun_path + (sizeof(CON_PRE)), buff, 33);
    //bind recv port
    if( bind(MASTER_LISTEN_PORT, (struct sockaddr*) &addr, sizeof(addr.sun_path) -1))
            return -1;

    free(buff);
    return -1;
}

int IPC_peek(int* mess, int* len)
{
    return -1;
}

int IPC_recv(char* buff, int len)
{
    return -1;
}

int IPC_send(int program, int message, char* buff, int len)
{
    return -1;
}

float get_version()
{
    return IPC_version;
}


