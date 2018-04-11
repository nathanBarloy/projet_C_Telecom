#include "ServerRunner.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <signal.h>
int global_serverRunnerContinue(int set, int nvalue)
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
void signal_serverRunner(int signal)
{
	if(signal == 2 || signal == 15)
	{
		global_serverRunnerContinue(1, 0);
		printf("\n");
	}
}
int serverRunner(BDD bdd)
{
	printf("Démarrage du serveur...\n");
	global_serverRunnerContinue(1, 1);
	signal(2, signal_serverRunner);
	signal(15, signal_serverRunner);
	while(global_serverRunnerContinue(0, 0))
	{
		usleep(10000);
	}
	printf("Arrêt du serveur...\n");
	return 0;
}
