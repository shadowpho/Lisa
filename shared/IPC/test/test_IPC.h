#include <dlfcn.h>


static char IPC_LIBRARY_PATH[] = "../IPC.so.0.0.1";

int load_lib(char* path);

int resolve_syms();

int close_lib();
