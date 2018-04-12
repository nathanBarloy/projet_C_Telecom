#include "Client.h"

Client newClient(int fd, BDD bdd)
{
	Client client = (Client) malloc(sizeof(struct Client));
	client->fd = fd;
	client->bdd = bdd;
	pthread_mutex_init(&client->mutex, 0);
	return client;
}

Client freeClient(Client client)//NE DOIT PAS FREE LA BDD
{
	if(client->fd != -1)
	{
		close(client->fd);
	}
	free(client);
	return 0;
}

void freeClient2(void* ptr)
{
	Client client = (Client)(ptr);
	freeClient(client);
}
