#include "Requests.h"
#include "../utils/JSONCheck.h"

Map_t getRequestsMap()
{
	Map_t r = newMap();
	//Insérer ici les associations
	setMap(r, autoString("prints"), (void*) ServerRequest_prints);
	setMap(r, autoString("exists"), (void*) ServerRequest_exists);
	//Fin des associations
	return r;
}


//Génération de JSON
JSONObject_t newJSONRequestAnswer(int id, int code, String_t error, JSONObject_t content)
{
	JSONObject_t r = JSONObject_new();
	JSONObject_set(r, autoString("Id"), JSONInt_new(id));
	JSONObject_set(r, autoString("Code"), JSONInt_new(code));
	JSONObject_set(r, autoString("Error"), JSONString_new(error));
	JSONObject_set(r, autoString("Answer"), content);
	return r;
}


//Execution
RequestAnswer execRequest(Client client, RequestQuery request)
{
	lock(client);
	lock(client->bdd);
	if(client->bdd->requests == 0)
	{
		client->bdd->requests = getRequestsMap();
	}
	String_t requestType = JSONObject_stringValueOf(request->obj, autoString("Type"));
	RequestAnswer(*ret)(Client, RequestQuery) = (RequestAnswer(*)(Client, RequestQuery))getMap(client->bdd->requests, requestType);
	unlock(client->bdd);
	unlock(client);
	if(ret != 0)
	{
		JSONString_t sid_s = JSONObject_getString(request->obj, autoString("Sid"));
		if(sid_s != 0)//Si la requête contient bien un champ Sid
		{
			JSONObject_t sid = BDD_getSid(client->bdd, sid_s);
			if(sid != 0)//Si ce champ correspond a une session, l'utilisateur est connecté
			{
				lock(client->bdd);
				request->sid = JSONObject_stringValueOf(sid, autoString("sid"));
				unlock(client->bdd);
				request->connected = 1;
				request->session = sid;
			}
			else//Sinon l'utilisateur est anonyme, pas de session associée
			{
				request->sid = 0;
				request->connected = 0;
				request->session = 0;
			}
		}
		return ret(client, request);
	}
	return newRequestAnswer(3, newJSONRequestAnswer(request->id, 3, autoConcatNString(2, "Invalid request: ", cString(requestType)), JSONObject_new()));
}

//Requêtes
RequestAnswer ServerRequest_prints(Client client, RequestQuery request)
{

	RequestQuery(request,query);
	RequestObject(request,query,"message",message);
	lock(client);
	printf("Prints from Client %2d: \"%s\"\n", client->fd, cString(JSONObject_stringValue(message)));
	unlock(client);
	return RequestAnswerOk(request,0);
}

RequestAnswer ServerRequest_RegisterUser(Client client, RequestQuery request)
{
	RequestQuery(request, user);
	if(JSONObject_getType(user) == OBJECT)
	{
		if(JSON_checkUser(user, true))
		{

		}
	}
	//Err
}
RequestAnswer ServerRequest_exists(Client client, RequestQuery request)
{
	return RequestAnswerOk(request,0);
}
