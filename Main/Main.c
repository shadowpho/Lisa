#include "Main.h"


int main(int charc, char* argv)
{
	printf("Starting Main!\n");
	int ex_val = scheduler();
	printf("Exiting, exit value=%d",ex_val);
	return ex_val;
}

int scheduler()
{
	for(;;)
	{
		//to-do
		sleep(1);
	}
	return -99; //XXX -- redot the constants
}
