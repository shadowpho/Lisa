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

float (*get_version)() = NULL;


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
    FUN_DLSYM(float, get_version);

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

int main(int argv, char* argc[])
{
    int status = load_lib(IPC_LIBRARY_PATH);
    printf("Library loaded! Return = %i\n",status);
    assert(status == 0);

    status = resolve_syms();
    printf("Resolving symbols! Return = %i\n",status);
    assert(status == 0);

    status = IPC_init(478,479);
    if(status!=0)
    {
        perror("init");
        return -1;
    }


    status = close_lib();
    printf("Closinglibrary! Return = %i\n",status);
    assert(status != -1);

    printf("%s","ALL GOOD!!!\n");
    return -1;
}
