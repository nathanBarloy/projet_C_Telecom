#include "ClientHandler.h"
#include "../utils/Client.h"
void* clientHandler(void* arg)
{
	Client client = (Client) arg;
	lock(client);
	printf("Thread pour client (%d)\n", client->fd);
	unlock(client);
	clientHandlerClose(client);
	return 0;//Ne pas récupérer la valeur, pas de pthread_exit(0)
}
void clientHandlerClose(Client client)
{
	lock(client);
	lock(client->bdd);
	printf("Déconnexion du client: %d\n", client->fd);
	size_t c = 0;
	while(c < sizeOfVector(client->bdd->clients))
	{
		if(client == (Client) getFromVector(client->bdd->clients, c))
		{
			eraseOnVector(client->bdd->clients, c);
			break;
		}
		++c;
	}
	unlock(client->bdd);
	freeClient(client);
}
