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
		RequestAnswer req = prints(addr_s, autoString("Bonjour tout le monde !"));
		if(req != 0)
		{
			printf("Req != 0\n");
		}
		else
		{
			printf("Req == 0\n");
		}
	}
	else
	{
		printf("Usage: client [server_ip]\n");
	}
	freeAutoString();
	return 0;
}
