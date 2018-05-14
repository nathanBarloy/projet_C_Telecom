#include "sys/ClientRunner.h"
#include <String/AutoString.h>
#include "sys/ClientRequest.h"
#include "sys/ClientRequests.h"
#include "utils/Connexion.h"
#include "utils/JSONShortcut.h"
#include "sys/ClientRunnerContinue.h"
int main(int argc, char** argv, char** envp)
{
	if(argc >= 2)
	{
		initClient();
		Connexion_t connexion = newConnexion(argv[1]);//Adresse du serveur
		//prints(connexion, autoString("Bonjour tout le monde !"));


		/*JSONObject_t machin = JSONObject_new();
		JSONObject_set(machin, autoString("lol"), JSONString_new(autoString("Bonjour")));
		JSONObject_set(machin, autoString("lol2"), JSONInt_new(18));
		printf("%s\n", cStringValueOf(machin, "lol"));
		printf("%d\n", ValueOf(machin, "lol2", int));
		JSONObject_delete(machin);*/

		if(!serverExists(connexion))
		{
			printf("Aucun serveur n'a été trouvé a l'adresse: %s\n", cString(connexion->addr_s));
		}
		else
		{
			/*JSONObject_t o = serverGetFilms(connexion);
			if(o)
			{
				printf("%s\n", cString(JSONObject_asString(o, 0)));
				JSONObject_delete(o);
			}
			else
			{
				printf("Erreur de recuperation de la BDD.\n");
			}*/
			int r = clientRunner(connexion);
		}
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
