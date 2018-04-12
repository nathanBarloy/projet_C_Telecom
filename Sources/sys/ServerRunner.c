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
	//Création de socket
	int server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if(server_fd == -1)
	{
		printf("Erreur, impossible de construire le socket.\n");
		global_serverRunnerContinue(1, 0);
	}
	//Réutilisation de port
	int reuseaddr = 1;
	if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&reuseaddr,sizeof(reuseaddr)) ==-1)
	{
		printf("Erreur, impossible de définir les paramètres du socket.\n");
		global_serverRunnerContinue(1, 0);
	}
	//Récupération de l'IP locale de l'ordi (demande au système)
	const char* hostname=0;
	const char* portname="10000";
	struct addrinfo hints;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_INET;//IPV4
	hints.ai_socktype = SOCK_STREAM;//Socket de flux, pour TCP
	hints.ai_protocol=0;//protocole, 0 = n'importe quel protocole géré par AF_INET (IPV4)
	hints.ai_flags=AI_PASSIVE|AI_ADDRCONFIG;
	struct addrinfo* res=0;
	int err=getaddrinfo(0,portname,&hints,&res);
	if(err != 0)
	{
	    printf("Impossible de résoudre l'adresse locale, erreur: %d\n", err);
	    global_serverRunnerContinue(1, 0);
	}
	//Bind
	if(bind(server_fd,res->ai_addr,res->ai_addrlen) == -1)
	{
    		printf("Erreur, impossible d'utiliser l'adresse IP/Port du PC.\n");
		global_serverRunnerContinue(1, 0);
	}
	freeaddrinfo(res);
	if (listen(server_fd,SOMAXCONN)) {
		printf("Impossible d'écouter le port. Erreur: %d. (errno)\n", errno);
		global_serverRunnerContinue(1, 0);
	}
	while(global_serverRunnerContinue(0, 0))
	{
		int session_fd = accept(server_fd, 0, 0);
		if(session_fd == -1)
		{
			if(errno != EAGAIN)
			{
				printf("Warning: Une erreur est survenue lors de l'acceptation de la connexion. Errno: %d\n", errno);
			}
		}
		else
		{
			printf("Nouveau client: connexion acceptée. (%d)\n", session_fd);
		}
		usleep(10000);
	}
	printf("Arrêt du serveur...\n");
	close(server_fd);
	return 0;
}
