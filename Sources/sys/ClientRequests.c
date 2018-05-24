#include "ClientRequests.h"
#include "ClientRequest.h"
#include "ClientRunnerContinue.h"
#include <unistd.h>
#include "../utils/JSONShortcut.h"
void prints(Connexion_t connexion, String_t message)
{
	JSONObject_t obj = JSONObject_new();
	JSONObject_set(obj, autoString("message"), JSONString_new(message));
	//printf("%s\n", cString(JSONObject_asString(obj, 0)));
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("prints"), obj));
	RequestAnswer a = clientRequest(connexion, q);
	freeRequestQuery(q);
	if(a != 0)
	{
		freeRequestAnswer(a);
	}
}
RequestAnswer Client_RegisterUser(Connexion_t connexion, JSONObject_t user)
{
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("registerUser"), user));
	RequestAnswer a = clientRequest(connexion, q);
	freeRequestQuery(q);
	return a;
}
RequestAnswer Client_Login(Connexion_t connexion, JSONObject_t data)
{
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("login"), data));
	RequestAnswer a = clientRequest(connexion, q);
	freeRequestQuery(q);
	return a;
}
RequestAnswer Client_Logout(Connexion_t connexion)
{
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("logout"), JSONObject_new()));
	RequestAnswer a = clientRequest(connexion, q);
	freeRequestQuery(q);
	return a;
}
bool serverExists(Connexion_t connexion)
{
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("exists"), JSONObject_new()));
	RequestAnswer a = clientRequest(connexion, q);
	bool exists = false;
	if(a != 0)
	{
		if(a->code == 0)
		{
			exists = true;
		}
		freeRequestAnswer(a);
	}
	freeRequestQuery(q);
	return exists;
}

JSONObject_t serverGetFilms(Connexion_t connexion)
{
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("getFilms"), JSONObject_new()));
	RequestAnswer a = clientRequest(connexion, q);
	freeRequestQuery(q);
	if(a != 0)
	{
		JSONObject_t answer = JSONObject_get(a->obj, AS("Answer"));
		JSONObject_remove(a->obj, AS("Answer"), false);
		freeRequestAnswer(a);
		return answer;
	}
	return 0;
}

JSONObject_t serverGetUsers(Connexion_t connexion)
{
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("getUsers"), JSONObject_new()));
	RequestAnswer a = clientRequest(connexion, q);
	freeRequestQuery(q);
	if(a != 0)
	{
		JSONObject_t answer = JSONObject_get(a->obj, AS("Answer"));
		JSONObject_remove(a->obj, AS("Answer"), false);
		freeRequestAnswer(a);
		return answer;
	}
	return 0;
}
JSONObject_t serverGetFilmById(Connexion_t connexion, int id)
{
	JSONObject_t obj = JSONObject_new();
	JSONObject_set(obj, AS("Id"), JSONInt_new(id));
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("getFilmById"), obj));
	RequestAnswer a = clientRequest(connexion, q);
	freeRequestQuery(q);
	if(a != 0)
	{
		JSONObject_t ans = JSONObject_get(a->obj, AS("Answer"));
		if(JSONObject_getType(ans) == OBJECT)
		{
			JSONObject_t film = JSONObject_getCopy(ans);
			freeRequestAnswer(a);
			return film;
		}
		freeRequestAnswer(a);
	}
	return 0;
}
JSONObject_t serverGetDistanceBetween(Connexion_t connexion, int id1, int id2)
{
	JSONObject_t obj = JSONObject_new();
	JSONObject_set(obj, AS("Id1"), JSONInt_new(id1));
	JSONObject_set(obj, AS("Id2"), JSONInt_new(id2));
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("getDistanceBetween"), obj));
	RequestAnswer a = clientRequest(connexion, q);
	freeRequestQuery(q);
	if(a != 0)
	{
		JSONObject_t ans = JSONObject_get(a->obj, AS("Answer"));
		if(JSONObject_getType(ans) == OBJECT)
		{
			JSONObject_t distance = JSONObject_getCopy(ans);
			freeRequestAnswer(a);
			return distance;
		}
		freeRequestAnswer(a);
	}
	return 0;
}
JSONArray_t serverGetFilmRecommendation(Connexion_t connexion, int id)
{
	JSONObject_t obj = JSONObject_new();
	JSONObject_set(obj, AS("Id"), JSONInt_new(id));
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("getFilmRecommendation"), obj));
	RequestAnswer a = clientRequest(connexion, q);
	freeRequestQuery(q);
	if(a != 0)
	{
		JSONObject_t ans = JSONObject_get(a->obj, AS("Answer"));
		if(JSONObject_getType(ans) == ARRAY)
		{
			JSONObject_t liste = JSONObject_getCopy(ans);
			freeRequestAnswer(a);
			return liste;
		}
		freeRequestAnswer(a);
	}
	return 0;
}
