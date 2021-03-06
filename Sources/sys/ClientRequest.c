#include "ClientRequest.h"
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <fcntl.h>
#include <strings.h>
#include <unistd.h>
#include "ClientRunnerContinue.h"
#include <errno.h>

RequestAnswer clientRequest(Connexion_t connexion, RequestQuery query)
{
	struct sockaddr_in serverSockAddr;
	struct hostent *serverHostEnt = gethostbyname(cString(connexion->addr_s));
	long hostAddr =  inet_addr(cString(connexion->addr_s));
	if(serverHostEnt == 0 || hostAddr == 0)
	{
		printf("Impossible de déterminer l'adresse de destination: %s\n", cString(connexion->addr_s));
		return 0;
	}
	serverSockAddr.sin_port = htons(10000);
	serverSockAddr.sin_family = AF_INET;
	bcopy(&hostAddr,&serverSockAddr.sin_addr,sizeof(hostAddr));
	bcopy(serverHostEnt->h_addr,&serverSockAddr.sin_addr,serverHostEnt->h_length);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	/*{//Non bloquant
		int flags = fcntl(sock, F_GETFL, 0);
		fcntl(sock, F_SETFL, flags | O_NONBLOCK);
	}*/
	if(sock < 0)
	{
		printf("Impossible d'initialiser le réseau.\n");
		return 0;
	}
	if(!connect(sock, (struct sockaddr*) &serverSockAddr, sizeof(struct sockaddr_in)))
	{
		{//Bloquant
			int flags = fcntl(sock, F_GETFL, 0);
			fcntl(sock, F_SETFL, flags ^ O_NONBLOCK);
		}
		#ifdef DEBUG
		printf("Connexion au serveur réussie.\n");
		#endif
		RequestAnswer rep = clientRequestGetAnswer(sock, query);
		close(sock);
		#ifdef DEBUG
		printf("Connexion terminée.\n");
		#endif
		return rep;
	}
	else
	{
		printf("Echec de connexion au serveur: %s:10000, %d\n", cString(connexion->addr_s), errno);
		return 0;
	}
}

RequestAnswer clientRequestGetAnswer(int sock, RequestQuery query)
{
	char l[2];
	l[1] = 0;
	String_t str = JSONObject_asString(query->obj, 0);
	int r = send(sock, cString(str), sizeOfString(str), MSG_NOSIGNAL);
	if(r == sizeOfString(str))
	{
		r = send(sock, l + 1, 1, MSG_NOSIGNAL);
		if(r == 1)
		{
			str = newString();
			JSONObject_t obj = 0;
			RequestAnswer rep = 0;
			while(global_clientRunnerContinue(0,0))
			{
				r = recv(sock, l, 1, MSG_NOSIGNAL);
				if(r > 0)
				{
					if(l[0] != 0)
					{
						//printf("%c - %d\n", l[0], (int) l[0]);
						concatString(str, autoString(l));
					}
					else
					{
						//printf("String:\n%s\n", cString(str));
						obj = JSONParser_parseString(str);
						if(obj != 0)
						{
							#ifdef DEBUG
							//printf("Answer: %s\n", cString(JSONObject_asString(obj, 0)));//A activer pour voir les réponses
							#endif
							int code = 0;
							if(JSONObject_get(obj, autoString("Code")) != 0)
							{
								code = JSONObject_intValueOf(obj, autoString("Code"));
							}
							rep = newRequestAnswer(code, obj);
						}
						else
						{
							//Format de données invalide
							printf("ClientRequest: Invalid data for answer.\n");
						}
						break;
					}
				}
				else if(r < 0)
				{
					if(errno != EAGAIN && errno != EWOULDBLOCK)
					{
						//Erreur quelconque
						break;
					}
					else
					{
						usleep(10000);
					}
				}
				else//r = 0
				{
					//Connexion interrompue
					break;
				}
			}
			fString(str);
			return rep;
		}
		else
		{
			//Echec de transmission des informations
			return 0;
		}
	}
	else
	{
		//Echec de transmission des informations
		return 0;
	}
}
