#include "Client.h"

Client newClient(int fd, BDD bdd)
{
	Client client = (Client) malloc(sizeof(struct Client));
	client->fd = fd;
	client->bdd = bdd;
	return client;
}

Client freeClient(Client client)//NE DOIT PAS FREE LA BDD
{
	free(client);
	return 0;
}

void freeClient2(void* ptr)
{
	Client client = (Client)(ptr);
	free(client);
}
