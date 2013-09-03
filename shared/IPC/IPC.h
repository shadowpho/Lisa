#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/un.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static const char* IPC_version = IPC_VERSION;

int IPC_init();
int IPC_listen(int recvPort, uint8_t local);
int IPC_close();
int IPC_recv(uint8_t* buff, uint32_t copied, uint32_t max_len);
int IPC_send(int ip, int port, int message, uint8_t* buff, uint32_t len);

const char* get_version();


