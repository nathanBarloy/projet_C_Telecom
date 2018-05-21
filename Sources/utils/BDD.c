#include "BDD.h"
#include <Vector/Vector.h>
#include "Client.h"
#include "JSONShortcut.h"
#include "Replace.h"
#include "JSONCheck.h"
BDD BDD_load()
{
	JSONParser_setExitOnException(false);
	JSONObject_t bdd = JSONObject_new();

	//Films
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

	//Sessions
	JSONObject_set(bdd, autoString("Sessions"), JSONObject_new());

	//Users sample (pearson_correlation tests)
	JSONArray_t users_sample = JSONParser_parseFile("data/users_sample.json");
	JSONObject_set(bdd, autoString("Users_sample"), users_sample);


	//Distances entre 2 films
	JSONObject_set(bdd, autoString("Distances"), JSONObject_new());
	BDD s = BDD_new();
	s->json = bdd;
	return s;
}
BDD BDD_new()
{
	BDD bdd = (BDD) malloc(sizeof(struct BDD));
	bdd->json = 0;
	pthread_mutex_init(&bdd->mutex, 0);
	bdd->clients = 0;
	bdd->requests = 0;
	return bdd;
}
BDD BDD_free(BDD bdd)
{
	pthread_mutex_lock(&bdd->mutex);
	JSONObject_delete(bdd->json);
	if(bdd->clients != 0)
	{
		freeVectorWithPtr(bdd->clients, freeClient2);
	}
	if(bdd->requests != 0)
	{
		freeMap(bdd->requests);
	}
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
	JSONObject_t backup = JSONParser_parseFile("data/backup.json");
	if(backup == 0)
	{
		backup = JSONObject_new();
	}
	JSONInt_t backupNumber = JSONObject_get(backup, AS("Id"));
	if(backupNumber == 0 || JSONObject_getType(backupNumber) != INT)
	{
		backupNumber = JSONInt_new(0);
	}
	JSONInt_set(backupNumber, JSONInt_get(backupNumber) + 1);
	JSONObject_set(backup, AS("Id"), backupNumber);
	JSONParser_saveFile(backup, "data/backup.json");
	char buf[100];
	sprintf(buf, "data/bd_backup_%6d.json", JSONInt_get(backupNumber));
	replace(buf, ' ', '0');
	JSONParser_saveFile(BDD_Films(bk), buf);
	sprintf(buf, "data/users_backup_%6d.json", JSONInt_get(backupNumber));
	replace(buf, ' ', '0');
	JSONParser_saveFile(BDD_Users(bk), buf);
	backupNumber = 0;
	backup = JSONObject_delete(backup);
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
JSONObject_t BDD_getSid(BDD bdd, String_t sid)
{
	lock(bdd);
	JSONObject_t session = JSONObject_get(bdd->json, sid);
	unlock(bdd);
	return 0;
}
JSONArray_t BDD_Users_sample(BDD bdd)
{
	return JSONObject_get(bdd->json, autoString("Users_sample"));
}
