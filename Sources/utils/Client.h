#ifndef CLIENT_H
#define CLIENT_H
#include <pthread.h>
#include "BDD.h"
struct Client
{
	int fd;//File descriptor/socket
	BDD bdd;
	pthread_t thread;
	pthread_mutex_t mutex;
};
typedef struct Client* Client;

Client newClient(int fd, BDD bdd);
Client freeClient(Client client);
void freeClient2(void* ptr);
#endif
