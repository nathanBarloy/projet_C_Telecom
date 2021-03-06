#include "Requests.h"
#include "../utils/JSONCheck.h"
#include "../utils/JSONShortcut.h"
#include "../utils/Date.h"
#include "../utils/Distance.h"

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
	setMap(r, autoString("getFilmById"), (void*) ServerRequest_getFilmById);
	setMap(r, autoString("getDistanceBetween"), (void*) ServerRequest_getDistanceBetween);
	setMap(r, autoString("getFilmRecommendation"), (void*) ServerRequest_getFilmRecommendation);
	setMap(r, autoString("login"), (void*) ServerRequest_login);
	setMap(r, autoString("logout"), (void*) ServerRequest_logout);
	setMap(r, autoString("getFilmsOrderedByRank"), (void*) ServerRequest_getFilmOrderedByRank);
	setMap(r, autoString("setFilmRateOfUser"), (void*) ServerRequest_setFilmRateOfUser);
	setMap(r, autoString("getUserRates"), (void*) ServerRequest_getUserRates);
	setMap(r, autoString("getCollaborativeRecommendation"), (void*) ServerRequest_getCollaborativeRecommendation);
	setMap(r, autoString("getRandRecommendation"), (void*) ServerRequest_getRandRecommendation);
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
		printf("Sid: %s\n", (sid_s != 0) ? cString(JSONString_get(sid_s)) : "(null)");
		if(sid_s != 0)//Si la requête contient bien un champ Sid
		{
			lock(client->bdd);
			JSONObject_t sid = BDD_getSessionById(client->bdd, JSONString_get(sid_s));
			unlock(client->bdd);
			if(sid != 0)//Si ce champ correspond a une session, l'utilisateur est connecté
			{
				request->sid = JSONObject_stringValue(sid_s);
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
	lock(client->bdd);
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
					unlock(client->bdd);
					BDD_save(client->bdd);
					printf("BDD sauvee.\n");
					return RequestAnswerOk(request, 0);
				}
				else
				{
					printf("Register: Too short.\n");
					unlock(client->bdd);
					return RequestAnswerError(request, 0, 5, AS("Trop court (login &| mdp)."));
				}
			}
			else
			{
				printf("Register: Used.\n");
				unlock(client->bdd);
				return RequestAnswerError(request, 0, 5, AS("Login déjà utilisé."));
			}
		}
		else
		{
			printf("Register: Format.\n");
			unlock(client->bdd);
			return RequestAnswerError(request, 0, 5, AS("Données d'utilisateur invalide, JSONObject incomplet ou format invalide."));
		}
	}
	printf("Register: Invalid.\n");
	unlock(client->bdd);
	return RequestAnswerError(request, 0, 5, AS("Données d'utilisateur invalide, requiert JSONObject."));
}
RequestAnswer ServerRequest_login(Client client, RequestQuery request)
{
	printf("Login...\n");
	RequestQuery(request, user);
	lock(client->bdd);
	if(JSONObject_getType(user) == OBJECT)
	{
		if(JSONObject_get(user, AS("Login")) != 0 && JSONObject_get(user, AS("Password")) != 0)
		{
			AutoString_t login = JSONObject_stringValueOf(user, AS("Login")), password = JSONObject_stringValueOf(user, AS("Password"));
			JSONObject_t u = BDD_getUserByLogin(client->bdd, login);
			if(u != 0)
			{
				if(equalsString(JSONObject_stringValueOf(u, AS("Password")), password))
				{
					JSONObject_t sess = JSONObject_new();
					JSONInt_t i = JSONInt_new(0);
					String_t sid = newString();
					size_t c = 0;
					while(sizeOfString(sid) == 0 || BDD_getSessionById(client->bdd, sid) != 0)
					{
						emptyString(sid);
						c = 0;
						while(c < 30)
						{
							JSONInt_set(i, rand() % 10);
							concatString(sid, JSONInt_asString(i, 0));
							++c;
						}
					}
					JSONInt_delete(i);
					JSONObject_set(sess, AS("SessionId"), JSONString_new(sid));
					fString(sid);
					JSONObject_set(sess, AS("UserId"), JSONObject_getCopy(JSONObject_get(u, AS("Id"))));
					JSONArray_add(BDD_Sessions(client->bdd), sess);
					printf("NewSession:\n%s\n", cString(JSONObject_asString(sess, 0)));
					JSONObject_t s = JSONObject_getCopy(sess);
					JSONObject_set(s, AS("User"), JSONObject_getCopy(u));
					unlock(client->bdd);
					return RequestAnswerOk(request, s);
				}
				else
				{
					unlock(client->bdd);
					return RequestAnswerError(request, 0, 5, AS("Mot de passe invalide."));
				}
			}
			else
			{
				unlock(client->bdd);
				return RequestAnswerError(request, 0, 5, AS("Login inconnu."));
			}
		}
		else
		{
			unlock(client->bdd);
			return RequestAnswerError(request, 0, 5, AS("Format de données invalide."));
		}
	}
	unlock(client->bdd);
	return RequestAnswerError(request, 0, 5, AS("Données d'utilisateur invalide, requiert JSONObject."));
}
RequestAnswer ServerRequest_logout(Client client, RequestQuery request)
{
	lock(client->bdd);
	printf("Logout...%s\n", (request->sid != 0 ? cString(request->sid) : ""));
	if(request->sid != 0)
	{
		JSONObject_t s = BDD_getSessionById(client->bdd, request->sid);
		if(s != 0)
		{
			printf("%s\n", cString(JSONObject_asString(s, 0)));
			JSONObject_delete(s);
			printf("Logout ok.\n");
			unlock(client->bdd);
			return RequestAnswerOk(request, 0);
		}
		printf("Error, sid is unknown.\n");
	}
	else
	{
		printf("Error, sid is null.\n");
	}
	unlock(client->bdd);
	return RequestAnswerError(request, 0, 5, AS("Session innexistante."));
}
RequestAnswer ServerRequest_exists(Client client, RequestQuery request)
{
	return RequestAnswerOk(request,0);
}

RequestAnswer ServerRequest_getFilms(Client client, RequestQuery request)
{
	lock(client->bdd);
	JSONObject_t bdd = JSONObject_getCopy(BDD_Films(client->bdd));
	unlock(client->bdd);
	return RequestAnswerOk(request, bdd);
}

RequestAnswer ServerRequest_getFilm(Client client, RequestQuery request)
{
	RequestQuery(request,query);
	RequestObject(request,query,"id",id);
	lock(client->bdd);
	JSONObject_t bdd = BDD_Films(client->bdd);
	JSONObject_t film =  0;
	size_t c = 0, size = JSONArray_size(film);
	while(c < size)
	{
		film = JSONArray_get(bdd, c);
		if(JSONInt_get(id) == JSONObject_intValueOf(film, AS("id")))
		{
			unlock(client->bdd);
			return RequestAnswerOk(request, JSONObject_getCopy(film))
		}
		++c;
	}
	unlock(client->bdd);
	return RequestAnswerOk(request, JSONNull_new());
}

RequestAnswer ServerRequest_getUsers(Client client, RequestQuery request)
{
	lock(client->bdd);
	JSONObject_t bdd = JSONObject_getCopy(BDD_Users(client->bdd));
	unlock(client->bdd);
	return RequestAnswerOk(request, bdd);
}

RequestAnswer ServerRequest_getFilmById(Client client, RequestQuery request)
{
	RequestQuery(request, query);
	lock(client->bdd);
	int id = JSONObject_intValueOf(query, AS("Id"));
	JSONObject_t film = BDD_getFilmById(client->bdd, id);
	if(film == 0)
	{
		unlock(client->bdd);
		return RequestAnswerOk(request, JSONNull_new());
	}
	JSONObject_t film2 = JSONObject_getCopy(film);
	unlock(client->bdd);
	return RequestAnswerOk(request, film2);
}
RequestAnswer ServerRequest_getDistanceBetween(Client client, RequestQuery request)
{
	RequestQuery(request, query);
	RequestObject(request, query, "Id1", id1);
	RequestObject(request, query, "Id2", id2);
	lock(client->bdd);
	JSONObject_t ret = JSONObject_new();
	if(JSONObject_getType(id1) == INT && JSONObject_getType(id2) == INT)
	{
		int iid1 = JSONInt_get(id1), iid2 = JSONInt_get(id2);
		double d = distance_film(client->bdd, iid1, iid2);
		JSONObject_set(ret, AS("Distance"), JSONDouble_new(d));
	}
	else
	{
		JSONObject_set(ret, AS("Distance"), JSONDouble_new(-1.0));
	}
	unlock(client->bdd);
	return RequestAnswerOk(request, ret);
}
RequestAnswer ServerRequest_getFilmRecommendation(Client client, RequestQuery request)
{
	RequestQuery(request, query);
	RequestObject(request, query, "Id", id);
	lock(client->bdd);
	if(JSONObject_getType(id) == INT)
	{
		JSONArray_t liste = liste_recommandation(client->bdd, JSONInt_get(id));
		unlock(client->bdd);
		return RequestAnswerOk(request, liste);
	}
	unlock(client->bdd);
	return RequestAnswerOk(request, JSONNull_new());
}
RequestAnswer ServerRequest_getFilmOrderedByRank(Client client, RequestQuery request)
{
	lock(client->bdd);
	JSONObject_t films = JSONObject_getCopy(BDD_getFilmsOrderedByRank(client->bdd));
	unlock(client->bdd);
	return RequestAnswerOk(request, films);
}
RequestAnswer ServerRequest_getCollaborativeRecommendation(Client client, RequestQuery request)
{
	RequestQuery(request, query);
	RequestObject(request, query, "Id", id);
	lock(client->bdd);
	if(JSONObject_getType(id) == INT)
	{
		int uid = JSONInt_get(id);
		JSONArray_t films = collaborative_recommendation(client->bdd, uid);
		if(JSONArray_size(films) == 0)
		{
			unlock(client->bdd);
			JSONArray_delete(films);
			return RequestAnswerOk(request, JSONArray_new());
		}
		JSONArray_t ten_first = JSONArray_new();
		int i;
		int size = JSONArray_size(films);
		//printf("size : %d\n", size);
		for(i=1 ; i<13 ; i++)
		{
			//printf("Voilà !\n");
			JSONArray_add(ten_first, JSONObject_getCopy(JSONArray_get(films, size-i)));
		}
		unlock(client->bdd);
		JSONArray_delete(films);
		return RequestAnswerOk(request, ten_first);
	}
	unlock(client->bdd);
	return RequestAnswerError(request, 0, 5, AS("Impossible de récupérer l'id de l'utilisateur"));
}
RequestAnswer ServerRequest_getRandRecommendation(Client client, RequestQuery request)
{
	lock(client->bdd);
	JSONArray_t films = RandomReco(client->bdd);
	unlock(client->bdd);
	return RequestAnswerOk(request, films);
}
RequestAnswer ServerRequest_setFilmRateOfUser(Client client, RequestQuery request)
{
	printf("lancement ServerRequest_setFilmRateOfUser\n");
	RequestQuery(request, query);
	RequestObject(request, query, "FilmId", film_id);
	RequestObject(request, query, "Value", value);
	lock(client->bdd);
	JSONObject_t s = BDD_getSessionById(client->bdd, request->sid);
	if(JSONObject_getType(film_id) == INT && s != 0 && JSONObject_getType(value) == INT)
	{
		JSONObject_t user = BDD_getUserById(client->bdd, JSONObject_intValueOf(s, AS("UserId")));
		printf("Modifications allowed.\n");
		int fid = JSONInt_get(film_id), v = JSONInt_get(value);
		unlock(client->bdd);
		bool r = BDD_setFilmRateOfUser(client->bdd, fid, JSONObject_intValueOf(user, AS("Id")), v);
		lock(client->bdd);
		if(r == true)
		{
			printf("Note OK.\n");
			unlock(client->bdd);
			return RequestAnswerOk(request, 0);
		}
		printf("Note User err.\n");
		unlock(client->bdd);
		return RequestAnswerError(request, 0, 5, AS("Impossible de trouver l'utilisateur à modifier."));
	}
	printf("Unable to set note.\n");
	unlock(client->bdd);
	return RequestAnswerError(request, 0, 5, AS("Impossible de modifier la note"));
}
RequestAnswer ServerRequest_getUserRates(Client client, RequestQuery request)
{
	printf("Récupération des notes de l'utilisateur\n");
	RequestQuery(request, query);
	RequestObject(request, query, "UserId", user_id);
	lock(client->bdd);
	if(JSONObject_getType(user_id) == INT)
	{
		printf("Utilisateur bien connecté\n");
		int uid = JSONInt_get(user_id);
		JSONArray_t rates = BDD_getUserRates(client->bdd, uid);
		if(rates != 0)
		{
			printf("Liste correctement récupérée\n");
			unlock(client->bdd);
			return RequestAnswerOk(request, JSONArray_getCopy(rates));
		}
		printf("Liste User err.\n");
		unlock(client->bdd);
		return RequestAnswerError(request, 0, 5, autoString("Impossible de récupérer la liste"));
	}
	printf("Impossible de récupérer l'id de l'utilisateur\n");
	unlock(client->bdd);
	return RequestAnswerError(request, 0, 5, AS("Impossible de récupérer l'id de l'utilisateur"));
}
