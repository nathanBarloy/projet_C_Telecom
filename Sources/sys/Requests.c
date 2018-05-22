#include "Requests.h"
#include "../utils/JSONCheck.h"
#include "../utils/JSONShortcut.h"
#include "../utils/Date.h"
Map_t getRequestsMap()
{
	Map_t r = newMap();
	//Insérer ici les associations
	setMap(r, autoString("prints"), (void*) ServerRequest_prints);
	setMap(r, autoString("exists"), (void*) ServerRequest_exists);
	setMap(r, autoString("getFilms"), (void*) ServerRequest_getFilms);
	setMap(r, autoString("getFilm"), (void*) ServerRequest_getFilm);
	setMap(r, autoString("getUsers"), (void*) ServerRequest_getUsers);
	setMap(r, autoString("registerUser"), (void*) ServerRequest_RegisterUser);
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
	else
	{
		printf("RequestType: %s → Invalid.\n", cString(requestType));
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
	printf("Register Request....\n");
	RequestQuery(request, user);
	if(JSONObject_getType(user) == OBJECT)
	{
		if(JSONObject_get(user, AS("Login")) != 0 && JSONObject_get(user, AS("Password")) != 0)
		{
			JSONArray_t users = BDD_Users(client->bdd);
			size_t c = 0, size = JSONArray_size(users);
			bool exists = false;
			String_t login = JSONObject_stringValueOf(user, AS("Login"));
			while(c < size)
			{
				if(equalsString(login, JSONObject_stringValueOf(JSONArray_get(users, c), AS("Login"))))
				{
					exists = true;
				}
				++c;
			}
			if(!exists)
			{
				String_t pass = JSONObject_stringValueOf(user, AS("Password"));
				if(sizeOfString(pass) >= 4 && sizeOfString(login) >= 4)
				{
					JSONObject_set(user, AS("Id"), JSONInt_new(BDD_Users_maxId(client->bdd) + 1));
					JSONObject_set(user, AS("Preferences"), JSONObject_new());
					JSONObject_set(user, AS("History"), JSONObject_new());
					JSONObject_set(user, AS("Friends"), JSONArray_new());
					JSONObject_set(user, AS("Follow"), JSONArray_new());
					if(JSONObject_get(user, AS("Birth")) == 0)
					{
						Date_t date = newDate();
						JSONObject_set(user, AS("Birth"), dateToJSON(date));
						freeDate(date);
					}
					if(JSONObject_get(user, AS("Name")) == 0)
					{
						JSONObject_set(user, AS("Name"), JSONString_new(autoString("")));
					}
					if(JSONObject_get(user, AS("FirstName")) == 0)
					{
						JSONObject_set(user, AS("FirstName"), JSONString_new(autoString("")));
					}
					JSONArray_add(users, JSONObject_getCopy(user));
					printf("Sauvegarde BDD...\n");
					BDD_save(client->bdd);
					printf("BDD sauvee.\n");
					return RequestAnswerOk(request, 0);
				}
				else
				{
					printf("Register: Too short.\n");
					return RequestAnswerError(request, user, 5, AS("Trop court (login &| mdp)."));
				}
			}
			else
			{
				printf("Register: Used.\n");
				return RequestAnswerError(request, user, 5, AS("Login déjà utilisé."));
			}
		}
		else
		{
			printf("Register: Format.\n");
			return RequestAnswerError(request, user, 5, AS("Données d'utilisateur invalide, JSONObject incomplet ou format invalide."));
		}
	}
	printf("Register: Invalid.\n");
	return RequestAnswerError(request, user, 5, AS("Données d'utilisateur invalide, requiert JSONObject."));
}
RequestAnswer ServerRequest_exists(Client client, RequestQuery request)
{
	return RequestAnswerOk(request,0);
}

RequestAnswer ServerRequest_getFilms(Client client, RequestQuery request)
{
	JSONObject_t bdd = JSONObject_getCopy(BDD_Films(client->bdd));
	return RequestAnswerOk(request, bdd);
}

RequestAnswer ServerRequest_getFilm(Client client, RequestQuery request)
{
	RequestQuery(request,query);
	RequestObject(request,query,"id",id);
	JSONObject_t bdd = BDD_Films(client->bdd);
	JSONObject_t film =  0;
	size_t c = 0, size = JSONArray_size(film);
	while(c < size)
	{
		film = JSONArray_get(bdd, c);
		if(JSONInt_get(id) == JSONObject_intValueOf(film, AS("id")))
		{
			return RequestAnswerOk(request, JSONObject_getCopy(film))
		}
		++c;
	}
	return RequestAnswerOk(request, JSONNull_new());
}

RequestAnswer ServerRequest_getUsers(Client client, RequestQuery request)
{
	JSONObject_t bdd = JSONObject_getCopy(BDD_Users(client->bdd));
	return RequestAnswerOk(request, bdd);
}
