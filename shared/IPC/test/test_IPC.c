#include "test_IPC.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int load_lib(char* path)
{
    return -1;
}

int resolve_syms()
{
    return -1;
}

int close_lib()
{
    return -1;
}

int main(int argv, char* argc[])
{
    int status = load_lib(IPC_LIBRARY_PATH);
    printf("Library loaded! Return = %i\n",status);
    assert(status != -1);

    status = resolve_syms();
    printf("Resolving symbols! Return = %i\n",status);
    assert(status != -1);

       
    status = close_lib();
    printf("Closinglibrary! Return = %i\n",status);
    assert(status != -1);


    return -1;
}
