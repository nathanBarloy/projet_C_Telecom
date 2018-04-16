#include "Requests.h"

Map_t getRequestsMap()
{
	Map_t r = newMap();
	//Insérer ici les associations
	setMap(r, autoString("prints"), (void*) prints);
	//Fin des associations
	return r;
}
//Construction/destruction
RequestAnswer newRequestAnswer(int code, JSONObject_t obj)
{
	RequestAnswer r = (RequestAnswer) malloc(sizeof(struct RequestAnswer));
	r->code = code;
	r->obj = obj;
	return r;
}
RequestAnswer freeRequestAnswer(RequestAnswer r)
{
	if(r->obj != 0)
	{
		r->obj = JSONObject_delete(r->obj);
	}
	free(r);
	return 0;
}
RequestQuery newRequestQuery(int id, JSONObject_t obj)
{
	RequestQuery r = (RequestQuery) malloc(sizeof(struct RequestQuery));
	r->id = id;
	r->obj = obj;
	return r;
}
RequestQuery freeRequestQuery(RequestQuery r)
{
	if(r->obj != 0)
	{
		r->obj = JSONObject_delete(r->obj);
	}
	free(r);
	return 0;
}

//Génération de JSON
JSONObject_t newJSONRequestAnswer(int id, int code, String_t error, JSONObject_t content)
{
	JSONObject_t r = JSONObject_new();
	JSONObject_set(r, autoString("id"), JSONInt_new(id));
	JSONObject_set(r, autoString("code"), JSONInt_new(code));
	JSONObject_set(r, autoString("error"), JSONString_new(error));
	JSONObject_set(r, autoString("answer"), content);
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
		return ret(client, request);
	}
	return newRequestAnswer(3, newJSONRequestAnswer(request->id, 3, autoConcatNString(2, "Invalid request: ", cString(requestType)), JSONObject_new()));
}

//Requêtes
RequestAnswer prints(Client client, RequestQuery request)
{

	RequestQuery(request,query);
	RequestObject(request,query,"message",message);
	lock(client);
	printf("Prints from Client %2d: \"%s\"\n", client->fd, cString(JSONObject_stringValue(message)));
	unlock(client);
	return RequestAnswerOk(request,0);
}
