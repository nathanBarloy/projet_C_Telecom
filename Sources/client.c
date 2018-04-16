#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <String/AutoString.h>
#include "sys/ClientRunner.h"
#include <fcntl.h>
#include <strings.h>

int main(int argc, char** argv, char** envp)
{
	int ret = 0;
	if(argc >= 2)
	{
		const char* addr_s = argv[1];
		struct sockaddr_in serverSockAddr;
		struct hostent *serverHostEnt = gethostbyname(addr_s);
		long hostAddr =  inet_addr(addr_s);
		if(serverHostEnt == 0 || hostAddr == 0)
		{
			printf("Impossible de déterminer l'adresse de destination: %s\n", addr_s);
			ret = -1;
			goto client_main_end;
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
			ret = -1;
			goto client_main_end;
		}
		if(!connect(sock, (struct sockaddr*) &serverSockAddr, sizeof(struct sockaddr_in)))
		{
			{//Bloquant
				int flags = fcntl(sock, F_GETFL, 0);
				fcntl(sock, F_SETFL, flags ^ O_NONBLOCK);
			}
			printf("Connexion au serveur réussie.\n");
			ClientSock_t clientSock = newClientSock(sock);
			ret = clientRunner(clientSock);
			close(sock);
			printf("Connexion terminée.\n");
		}
		else
		{
			printf("Echec de connexion au serveur: %s:10000\n", addr_s);
			ret = -1;
		}
	}
	else
	{
		printf("Usage: client [server_ip]\n");
	}
client_main_end:
	freeAutoString();
	return ret;
}
