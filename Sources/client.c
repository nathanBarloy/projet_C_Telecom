#include "sys/ClientRunner.h"
#include <String/AutoString.h>
#include "sys/ClientRequest.h"

int main(int argc, char** argv, char** envp)
{
	if(argc >= 2)
	{
		const char* addr_s = argv[1];//Adresse du serveur
	}
	else
	{
		printf("Usage: client [server_ip]\n");
	}
	freeAutoString();
	return 0;
}
