#include "BDD.h"

BDD BDD_load()
{
	JSONParser_setExitOnException(false);
	JSONObject_t bdd = JSONObject_new();
	JSONArray_t films = JSONParser_parseFile("data/bd.json");
	if(films == 0)
	{
		films = JSONArray_new();
	}
	JSONObject_set(bdd, autoString("Films"), films);
	JSONArray_t users = JSONParser_parseFile("data/users.json");
	if(users == 0)
	{
		users = JSONArray_new();
	}
	JSONObject_set(bdd, autoString("Users"), users);
	BDD s = BDD_new();
	s->json = bdd;
	return s;
}
BDD BDD_new()
{
	BDD bdd = (BDD) malloc(sizeof(struct BDD));
	bdd->json = 0;
	pthread_mutex_init(&bdd->mutex, 0);
	return bdd;
}
BDD BDD_free(BDD bdd)
{
	pthread_mutex_lock(&bdd->mutex);
	JSONObject_delete(bdd->json);
	pthread_mutex_unlock(&bdd->mutex);
	free(bdd);
	return 0;
}
int BDD_save(BDD bdd)
{
	//Backup
	BDD bk = BDD_load();
	//printf("Films: %p - %p\n", BDD_Films(bk), JSONObject_getArray(bk->json, autoString("Films")));
	//printf("Films:\n%s\nUsers:\n%s\n", cString(JSONObject_asString(BDD_Films(bk), 0)), cString(JSONObject_asString(BDD_Users(bk), 0)));
	JSONParser_saveFile(BDD_Films(bk), "data/bd_backup.json");
	JSONParser_saveFile(BDD_Users(bk), "data/users_backup.json");
	BDD_free(bk);
	//save
	lock(bdd);
	int r = JSONParser_saveFile(BDD_Films(bdd), "data/bd.json");
	r = JSONParser_saveFile(BDD_Users(bdd),"data/users.json") && r;
	unlock(bdd);
	return r;
}
JSONArray_t BDD_Users(BDD bdd)
{
	return JSONObject_get(bdd->json, autoString("Users"));
}
JSONArray_t BDD_Films(BDD bdd)
{
	return JSONObject_get(bdd->json, autoString("Films"));
}
