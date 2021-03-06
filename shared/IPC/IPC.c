#include "IPC.h"

int static MASTER_LISTEN_SOCKET = 0;
int static MASTER_SEND_SOCKET = 0;

int static MASTER_LISTEN_PORT=0;
int static MASTER_SEND_PORT=0;

struct sockaddr_un addr;
struct sockaddr_un send_addr;

int IPC_init(int listenNum,int sendNum)
{
    const char CON_PRE[] = "IPC_";

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
    sprintf(buff, "%d",MASTER_LISTEN_PORT);
    strncpy(addr.sun_path -1 +(sizeof(CON_PRE)), buff, 33);
    //
    IPC_close(); //attempt to unlink!
    //
    //bind recv port
    if( bind(MASTER_LISTEN_SOCKET, (struct sockaddr*) &addr, sizeof(addr.sun_path) -1))
            return -1;

    memcpy(&send_addr,&addr,sizeof(struct sockaddr_un));
    sprintf(buff, "%d",MASTER_SEND_PORT);
    strncpy(send_addr.sun_path - 1 + (sizeof(CON_PRE)), buff, 33);
    free(buff);

    printf("Recv Socket addr: %s\n",addr.sun_path);
    printf("Send Socket addr: %s\n",send_addr.sun_path);
    return 0;
}

int IPC_close()
{
    int i = unlink(send_addr.sun_path);
    i &= unlink(addr.sun_path);
    if(i!=0)
        return -1;
    return 0;
}
int IPC_peek(int* mess, int* len)
{
//    int status = accept(
    return -1;
}

int IPC_recv(char* buff, int len)
{

    return -1;
}

//XXX -- make connect to other people
int IPC_send(int port, int message, char* buff, int len)
{
    int status = connect(MASTER_SEND_SOCKET, &addr, sizeof(send_addr));
    if(status == -1)
        return -1;
//    write();
    status = close(MASTER_SEND_SOCKET);
    if(status == -1)
        return -1;
    return 0;
}

const char* get_version()
{
    return IPC_version;
}


