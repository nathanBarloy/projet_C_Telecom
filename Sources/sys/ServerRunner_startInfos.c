#include "ServerRunner.h"
#include "../utils/JSONShortcut.h"
void startInfos(BDD bdd)
{
	JSONArray_t users = BDD_Users(bdd), films = BDD_Films(bdd);
	size_t c = 0, size = JSONArray_size(films);
	printf("Films chargés (%ld):\n", size);
	JSONObject_t tmp = 0;
	while(c < size)
	{
		tmp = JSONArray_get(films, c);
		printf("\t- \"%s\"\n", cStringValueOf(tmp, "Title"));
		++c;
	}
	c = 0;
	size = JSONArray_size(users);
	printf("Utilisateurs chargés (%ld):\n", size);
	while(c < size)
	{
		tmp = JSONArray_get(users, c);
		printf("\t- \"%s\" / (\"%s\", \"%s\")\n", cStringValueOf(tmp, "Login"), cStringValueOf(tmp, "FirstName"), cStringValueOf(tmp, "Name"));
		++c;
	}
}
