#include "test_IPC.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char * dl_error;
#define FUN_DLSYM(ret,name) do\
    {(*(ret**)(&name)=dlsym(test_handle,#name));\
        dl_error = dlerror();\
        if(dl_error!=NULL)\
        {\
            printf("DL_ERROR: %s\n",dl_error);\
            return -1;\
        }\
        if(name==NULL) return -1;\
    printf("loaded %s,addr %p\n",#name,(int*)name);\
    }while(0);

void static *test_handle;

//functions
int (*IPC_init)(int, int) = NULL;
int (*IPC_close)(void) = NULL;
int (*IPC_peek)(int*, int*) = NULL;
int (*IPC_recv)(char*,int) = NULL;
int (*IPC_send)(int,int,char*,int)= NULL;

const char* (*get_version)() = NULL;


int load_lib(char* path)
{

    test_handle = dlopen(IPC_LIBRARY_PATH,RTLD_LAZY|RTLD_LOCAL);
    if(!test_handle)
    {
        printf("%s\n",dlerror());
        return -1;
    }
    return 0;
}

//could be re-written
int resolve_syms()
{
    FUN_DLSYM(int, IPC_init);
    FUN_DLSYM(int, IPC_close);
    FUN_DLSYM(int, IPC_peek);
    FUN_DLSYM(int, IPC_recv);
    FUN_DLSYM(int, IPC_send);
    FUN_DLSYM(char*, get_version);

    return 0;
}

int close_lib()
{
    int status = IPC_close();
    dlclose(test_handle);
    if(status!=0) {
        perror("closing");
        return -1;
    }
    return 0;
}

#define CHECK_ERROR(var,fun_str) do{\
    printf("%s = %d\n",fun_str,var);\
    if((var)!=0){printf("Error at line: %d, error:\n",__LINE__);perror(fun_str);return -1;}\
    }while(0);

int main(int argv, char* argc[])
{
    int status = load_lib(IPC_LIBRARY_PATH);
    CHECK_ERROR(status,"load library");

    status = resolve_syms();
    CHECK_ERROR(status,"resolve symbols");

    printf("Library version tested: %s\n", get_version());

    status = IPC_init(478,479);
    CHECK_ERROR(status,"init ipc");

    status = IPC_send(0, 0, NULL, 0);
    CHECK_ERROR(status,"send");

    status = IPC_peek(NULL, NULL);
    CHECK_ERROR(status,"peek");

    status = IPC_recv(NULL, 0);
    CHECK_ERROR(status,"recv");

    status = close_lib();
    CHECK_ERROR(status,"close lib");

    printf("%s","ALL GOOD!!!\n");
    return 0;
}
