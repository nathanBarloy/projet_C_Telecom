#include "sys/ClientRunner.h"
#include <String/AutoString.h>
#include "sys/ClientRequest.h"
#include "sys/ClientRequests.h"
#include "utils/Connexion.h"
int main(int argc, char** argv, char** envp)
{
	if(argc >= 2)
	{
		initClient();
		Connexion_t connexion = newConnexion(argv[1]);//Adresse du serveur
		prints(connexion, autoString("Bonjour tout le monde !"));

		//Fin
		connexion = freeConnexion(connexion);
	}
	else
	{
		printf("Usage: client [server_ip]\n");
	}
	freeAutoString();
	return 0;
}
