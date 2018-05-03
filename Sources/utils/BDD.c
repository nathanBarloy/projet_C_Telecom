#include "BDD.h"
#include <Vector/Vector.h>
#include "Client.h"
#include "JSONShortcut.h"
#include "Replace.h"
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

	//Users
	JSONArray_t users = JSONParser_parseFile("data/users.json");
	if(users == 0)
	{
		users = JSONArray_new();
	}
	JSONObject_set(bdd, autoString("Users"), users);

	//Sessions
	JSONObject_set(bdd, autoString("Sessions"), JSONObject_new());



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
bool BDD_rightTypeOrNull(JSONObject_t obj, JSONType_t type)
{
	if(obj == 0)
	{
		return true;
	}
	else if(JSONObject_getType(obj) == NULLOBJ)
	{
		return true;
	}
	else if(JSONObject_getType(obj) == type)
	{
		return true;
	}
	return false;
}
bool BDD_checkUser(JSONObject_t user)
{
	bool validType = (JSONObject_getType(user) == OBJECT);
	if(validType)
	{
		validType = validType && BDD_rightTypeOrNull(JSONObject_get(user, AS("Id")), INT);
		validType = validType && BDD_rightTypeOrNull(JSONObject_get(user, AS("Name")), STRING);
		validType = validType && BDD_rightTypeOrNull(JSONObject_get(user, AS("FirstName")), STRING);
		validType = validType && BDD_rightTypeOrNull(JSONObject_get(user, AS("Login")), STRING);
		validType = validType && BDD_rightTypeOrNull(JSONObject_get(user, AS("Password")), STRING);
		//Ajouter les autres vérifications pour Preferences et History
	}
	return validType;
}
bool BDD_checkFilm(JSONObject_t film)
{
	bool validType = (JSONObject_getType(film) == OBJECT);
	if(validType)
	{
		validType = validType && BDD_rightTypeOrNull(JSONObject_get(film, AS("Id")), INT);
		validType = validType && BDD_rightTypeOrNull(JSONObject_get(film, AS("Duration")), INT);
		validType = validType && BDD_rightTypeOrNull(JSONObject_get(film, AS("Year")), INT);
		validType = validType && BDD_rightTypeOrNull(JSONObject_get(film, AS("Title")), STRING);
		validType = validType && BDD_rightTypeOrNull(JSONObject_get(film, AS("Type")), STRING);
		validType = validType && BDD_rightTypeOrNull(JSONObject_get(film, AS("Description")), STRING);
		validType = validType && BDD_checkBasicArray(JSONObject_get(film, AS("Actors")), STRING);
		validType = validType && BDD_checkBasicArray(JSONObject_get(film, AS("Directors")), STRING);
		validType = validType && BDD_checkBasicArray(JSONObject_get(film, AS("Genres")), STRING);
	}
	return validType;
}
bool BDD_checkBasicArray(JSONArray_t arr, JSONType_t type)
{
	size_t c = 0, size;
	bool validType = (arr != 0) && (JSONObject_getType(arr) == ARRAY);
	if(validType)
	{
		size = JSONArray_size(arr);
		while(validType && c < size)
		{
			validType = validType && (JSONObject_getType(JSONArray_get(arr, c)) == type);
			++c;
		}
	}
	return validType;
}
