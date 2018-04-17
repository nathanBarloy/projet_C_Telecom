#include "ClientRunner.h"
#include <stdlib.h>
#include <JSONAll.h>
#include <String/String.h>
int clientRunner()
{
	signal(2, signal_clientRunner);
	signal(15, signal_clientRunner);
	initClient();
	while(global_clientRunnerContinue(0, 0))
	{
		usleep(10000);
	}
	return 0;
}
int global_clientRunnerContinue(int set, int nvalue)
{
	static int init = 1;
	static pthread_mutex_t m;
	if(init)
	{
		init = 0;
		pthread_mutex_init(&m, 0);
	}
	pthread_mutex_lock(&m);
	static int value = 0;
	if(set)
	{
		value = nvalue;
	}
	int r = value;
	pthread_mutex_unlock(&m);
	return r;
}
void signal_clientRunner(int signal)
{
	if(signal == 2 || signal == 15)
	{
		global_clientRunnerContinue(1, 0);
		printf("\n");
	}
}
void initClient()
{
	global_clientRunnerContinue(1, 1);
}
