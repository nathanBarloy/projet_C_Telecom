#include "ClientHandler.h"
#include "../utils/Client.h"
#include <sys/types.h>
#include <sys/socket.h>
#include "Requests.h"
void* clientHandler(void* arg)
{
	Client client = (Client) arg;
	lock(client);
	//printf("Thread pour client (%d)\n", client->fd);
	size_t r = 0;
	char l[2];
	l[1] = 0;
	String_t request = newString();
	while(1)
	{
		r = recv(client->fd, l, 1, MSG_NOSIGNAL);
		if(r == 1)
		{
			if(l[0] == 0)
			{
				JSONObject_t req = JSONParser_parseString(request);
				RequestAnswer rep = 0;
				RequestQuery q = newRequestQuery(0, req);
				if(req != 0)
				{
					rep = execRequest(client, q);
				}
				else
				{
					rep = RequestAnswerError(q,0,4, autoString("Protocole invalide, la requête n'est pas en JSON."));
				}
				q = freeRequestQuery(q);
				req = JSONObject_delete(req);
				String_t data = JSONObject_asString(rep->obj, 0);//autoString, pas besoin de free
				r = send(client->fd, cString(data), sizeOfString(data), MSG_NOSIGNAL);
				if(r != sizeOfString(data))
				{
					printf("Erreur d'envoi de réponse au client %d, %ld != %ld\n", client->fd, sizeOfString(data), r);
				}
				r = send(client->fd, l + 1, 1, MSG_NOSIGNAL);//Envoi du 0
				if(r != 1)
				{
					printf("Erreur d'envoi de réponse au client %d, %ld != %ld\n", client->fd, 1l, r);
				}
			}
			else
			{
				concatString(request, autoString(l));
			}
		}
		else
		{
			break;
		}
	}
	fString(request);
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
