
static float IPC_version = IPC_VERSION;

int init_com(int listenNum);
int peek(int* mess, int* len);
int recieve(char* buff, int len);

int send(int program, int message, char* buff, int len);

float get_version();


