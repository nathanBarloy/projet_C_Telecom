#include "ClientHandler.h"
#include "../utils/Client.h"
#include <sys/types.h>
#include <sys/socket.h>
#include "Requests.h"
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
void* clientHandler(void* arg)
{
	Client client = (Client) arg;
	//printf("Thread pour client (%d)\n", client->fd);
	int r = 0;
	char l[2];
	l[1] = 0;
	String_t request = newString();
	while(global_serverRunnerContinue(0,0))
	{
		lock(client);
		r = recv(client->fd, l, 1, MSG_NOSIGNAL);
		unlock(client);
		printf("Running... %d\n", r);
		if(r > 0)
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
				lock(client);
				r = send(client->fd, cString(data), sizeOfString(data), MSG_NOSIGNAL);
				unlock(client);
				if(r != sizeOfString(data))
				{
					lock(client);
					printf("Erreur d'envoi de réponse au client %d, %ld != %ld\n", client->fd, sizeOfString(data), r);
					unlock(client);
				}
				lock(client);
				r = send(client->fd, l + 1, 1, MSG_NOSIGNAL);//Envoi du 0
				unlock(client);
				if(r != 1)
				{
					lock(client);
					printf("Erreur d'envoi de réponse au client %d, %d != %d\n", client->fd, 1, r);
					unlock(client);
				}
			}
			else
			{
				concatString(request, autoString(l));
			}
		}
		else if(r < 0)
		{
			if(errno != EAGAIN && errno != EWOULDBLOCK)
			{
				printf("BREAK\n");
				break;
			}
			else
			{
				perror("Recv Wait...");
				usleep(10000);
			}
		}
		else//r = 0
		{
			printf("DISCONNECT %d !\n", r);
			break;
		}
	}
	fString(request);
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
	unlock(client);
	freeClient(client);
}
