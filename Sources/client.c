#include "sys/ClientRunner.h"
#include <String/AutoString.h>
#include "sys/ClientRequest.h"
#include "sys/ClientRequests.h"
int main(int argc, char** argv, char** envp)
{
	if(argc >= 2)
	{
		initClient();
		const char* addr_s = argv[1];//Adresse du serveur
		prints(addr_s, autoString("Bonjour tout le monde !"));
	}
	else
	{
		printf("Usage: client [server_ip]\n");
	}
	freeAutoString();
	return 0;
}
