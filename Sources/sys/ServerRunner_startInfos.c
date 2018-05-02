#include "ServerRunner.h"
#include "../utils/JSONShortcut.h"
void startInfos(BDD bdd)
{
	printf("Vérification d'intégrité de la base de données...\n");
	JSONArray_t users = BDD_Users(bdd), films = BDD_Films(bdd);
	unsigned int c = 0, size = JSONArray_size(films);
	printf("Films chargés (%u):\n", size);
	JSONObject_t tmp = 0;
	while(c < size)
	{
		tmp = JSONArray_get(films, c);
		//printf("%s\n", cString(JSONObject_asString(tmp, 1)));//DEBUG
		printf("\t- E#%3u: ", c);
		if(BDD_checkFilm(tmp))
		{
			printf("OK: ");
			printf("\"%s\"\n", cStringValueOf(tmp, "Title"));
		}
		else
		{
			printf("FORMAT INVALIDE.\n");
			printf("%s\n", cString(JSONObject_asString(tmp, 2)));
			JSONArray_removeIndex(films, c, true);
			--c;
			size = JSONArray_size(films);
			printf("\t → Supprimé.\n");
			//printf("NewSize: %u\n", size);//DEBUG
		}
		++c;
	}

	c = 0;
	size = JSONArray_size(users);
	printf("Utilisateurs chargés (%u):\n", size);
	while(c < size)
	{
		tmp = JSONArray_get(users, c);
		printf("\t- E#%3u: ", c);
		if(BDD_checkUser(tmp))
		{
			printf("OK: ");
			printf("\"%s\" / (\"%s\", \"%s\")\n", cStringValueOf(tmp, "Login"), cStringValueOf(tmp, "FirstName"), cStringValueOf(tmp, "Name"));
		}
		else
		{
			printf("FORMAT INVALIDE.\n");
			printf("%s\n", cString(JSONObject_asString(tmp, 2)));
			JSONArray_removeIndex(users, c, true);
			--c;
			size = JSONArray_size(users);
			printf("\t → Supprimé.\n");
		}
		++c;
	}
	printf("Intégrité vérifiée:\n");
	printf("\t- Nombre total de films: %u\n", JSONArray_size(films));
	printf("\t- Nombre total d'utilisateurs': %u\n", JSONArray_size(users));
	printf("Fin de vérification d'intégrité.\n");
}
