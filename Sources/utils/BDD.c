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
	JSONObject_set(bdd, autoString("Sessions"), JSONArray_new());

	//Matrice des genres
	JSONObject_t genres = JSONParser_parseFile("data/genres.json");
	if(genres == 0)
	{
		genres = JSONObject_new();
		JSONObject_set(genres, autoString("Liste"), JSONArray_new());
		JSONObject_set(genres, autoString("Matrice"), JSONArray_new());
	}
	JSONObject_set(bdd, autoString("Genres"), genres);
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
	sprintf(buf, "data/genres_backup_%6d.json", JSONInt_get(backupNumber));
	replace(buf, ' ', '0');
	JSONParser_saveFile(BDD_Genres(bk), buf);
	backupNumber = 0;
	backup = JSONObject_delete(backup);
	BDD_free(bk);
	//save
	lock(bdd);
	int r = JSONParser_saveFile(BDD_Films(bdd), "data/bd.json");
	r = JSONParser_saveFile(BDD_Users(bdd),"data/users.json") && r;
	r = JSONParser_saveFile(BDD_Genres(bdd),"data/genres.json") && r;
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
JSONArray_t BDD_Sessions(BDD bdd)
{
	return JSONObject_get(bdd->json, autoString("Sessions"));
}
JSONArray_t BDD_Genres(BDD bdd)
{
	return JSONObject_get(bdd->json, autoString("Genres"));
}
int BDD_Users_maxId(BDD bdd)
{
	JSONArray_t users = BDD_Users(bdd);
	JSONObject_t user = 0;
	size_t c = 0, size = JSONArray_size(users);
	int max = 0;
	int n = 0;
	while(c < size)
	{
		user = JSONArray_get(users, c);
		n = JSONObject_intValueOf(user, AS("Id"));
		if(n > max)
		{
			max = n;
		}
		++c;
	}
	return max;
}
JSONObject_t BDD_getFilmById(BDD bdd, int id)
{
	JSONObject_t films = BDD_Films(bdd), tmp = 0;
	size_t c = 0, size = JSONArray_size(films);
	while(c < size)
	{
		tmp = JSONArray_get(films, c);
		if(JSONObject_intValueOf(tmp, AS("Id")) == id)
		{
			return tmp;
		}
		++c;
	}
	return 0;
}
JSONObject_t BDD_getFilmByRank(BDD bdd, int id)
{
	JSONObject_t films = BDD_Films(bdd), tmp = 0;
	size_t c = 0, size = JSONArray_size(films);
	while(c < size)
	{
		tmp = JSONArray_get(films, c);
		if(JSONObject_intValueOf(tmp, AS("Rank")) == id)
		{
			return tmp;
		}
		++c;
	}
	return 0;
}
JSONObject_t BDD_getUserById(BDD bdd, int id)
{
	JSONArray_t users = BDD_Users(bdd), u = 0;
	size_t c = 0, size = JSONArray_size(users);
	String_t id_s = newStringFromCharStar("Id");
	while(c < size)
	{
		u = JSONArray_get(users, c);
		if(JSONObject_intValueOf(u, id_s) == id)
		{
			fString(id_s);
			return u;
		}
		++c;
	}
	fString(id_s);
	return 0;
}
JSONObject_t BDD_getSessionById(BDD bdd, String_t sid)
{
	JSONArray_t users = BDD_Sessions(bdd), u = 0;
	size_t c = 0, size = JSONArray_size(users);
	String_t id_s = newStringFromCharStar("SessionId");
	while(c < size)
	{
		u = JSONArray_get(users, c);
		if(equalsString(JSONObject_stringValueOf(u, id_s), sid))
		{
			fString(id_s);
			return u;
		}
		++c;
	}
	fString(id_s);
	return 0;
}
JSONObject_t BDD_getUserByLogin(BDD bdd, String_t login)
{
	JSONArray_t users = BDD_Users(bdd), u = 0;
	size_t c = 0, size = JSONArray_size(users);
	String_t login_s = newStringFromCharStar("Login");
	while(c < size)
	{
		u = JSONArray_get(users, c);
		if(equalsString(JSONObject_stringValueOf(u, login_s), login))
		{
			fString(login_s);
			return u;
		}
		++c;
	}
	fString(login_s);
	return 0;
}

void BDD_UpdateRate(BDD bdd, JSONObject_t film)
{
	JSONArray_t users = BDD_Users(bdd), rates = 0;
	JSONObject_t u = 0, hist = 0, rate = 0;
	size_t c = 0, size = JSONArray_size(users), c2 = 0, size2 = 0;
	String_t history_s = newStringFromCharStar("History"), rates_s = newStringFromCharStar("Rates"), id_s = newStringFromCharStar("Id"), rate_s = newStringFromCharStar("Rate");
	int id = 0, fid = JSONObject_intValueOf(film, id_s);
	double frate = 0;
	unsigned int rateNb = 0;
	double rateSum = 0.0;
	while(c < size)
	{
		u = JSONArray_get(users, c);
		hist = JSONObject_get(u, history_s);
		if(hist != 0)
		{
			rates = JSONObject_get(hist, rates_s);
			if(rates != 0)
			{
				c2 = 0;
				size2 = JSONArray_size(rates);
				while(c2 < size2)
				{
					rate = JSONArray_get(rates, c2);
					id = JSONObject_intValueOf(rate, id_s);
					frate = JSONObject_doubleValueOf(rate, rate_s);
					if(id > 0 && frate >= 1 && id == fid)
					{
						rateSum += frate;
						++rateNb;
					}
					++c2;
				}
			}
			else
			{
				JSONObject_set(hist, rates_s, JSONArray_new());//Création du champ manquant
			}
		}
		else
		{
			JSONObject_set(u, history_s, JSONObject_new());//Creation du champ manquant
		}
		++c;
	}


	double finalRate = 0.0;
	if(rateNb > 0)
	{
		finalRate = rateSum / (double) (rateNb);
	}
	JSONObject_set(film, rate_s, JSONDouble_new(finalRate));
	fString(history_s);
	fString(rates_s);
	fString(id_s);
	fString(rate_s);
}
void BDD_UpdateRates(BDD bdd)
{
	JSONArray_t films = BDD_Films(bdd);
	JSONObject_t film = 0;
	size_t c = 0, size = JSONArray_size(films);
	while(c < size)
	{
		film = JSONArray_get(films, c);
		BDD_UpdateRate(bdd, film);
		++c;
	}
}
void BDD_UpdateRanks(BDD bdd)
{
	JSONArray_t films = JSONObject_getCopy(BDD_Films(bdd));
	JSONObject_t film = 0, nfilm = 0;
	size_t c = 0, size = JSONArray_size(films);
	double min = 0.0, nmin = 6.0, rate = 0.0;
	int lastRank = size;
	String_t rate_s = newStringFromCharStar("Rate"), id_s = newStringFromCharStar("Id"), rank_s = newStringFromCharStar("Rank");
	JSONObject_t rankSet = JSONObject_new();
	while(size > 0)
	{
		c = 0;
		nfilm = 0;
		nmin = 6.0;
		while(c < size)
		{
			film = JSONArray_get(films, c);
			rate = JSONObject_doubleValueOf(film, rate_s);
			if(rate >= min && rate != 0)
			{
				if(rate < nmin)
				{
					printf("nmin %f → %f\n", nmin, rate);
					nmin = rate;
					nfilm = film;
				}
			}
			else
			{
				printf("Reduce: %d - %f\n", JSONObject_intValueOf(film, id_s), rate);
				JSONObject_set(rankSet, JSONObject_stringValueOf(film, id_s), JSONInt_new(0));
				JSONObject_delete(film);
				--size;
				--lastRank;
				continue;
			}
			++c;
		}
		if(nfilm != 0)
		{
			min = nmin;
			printf("Found: %f → %d\n", nmin, lastRank);
			JSONObject_set(rankSet, JSONObject_stringValueOf(nfilm, id_s), JSONInt_new(lastRank));
			JSONObject_delete(nfilm);
			--size;
			--lastRank;
		}
		else
		{
			printf("Error?\n");
			break;
			/*while(size > 0)
			{
				film = JSONArray_get(films, 0);
				JSONObject_set(rankSet, JSONObject_stringValueOf(film, id_s), JSONInt_new(0));
				--size;
				--lastRank;
			}*/
		}

	}
	JSONArray_delete(films);
	films = BDD_Films(bdd);
	c = 0;
	size = JSONArray_size(films);
	while(c < size)
	{
		film = JSONArray_get(films, c);
		JSONObject_set(film, rank_s, JSONObject_get(rankSet, JSONObject_stringValueOf(film, id_s)));
		printf("Rank set: %d - %d\n", JSONObject_intValueOf(film, id_s), JSONObject_intValueOf(film, rank_s));
		++c;
	}
	JSONObject_delete(rankSet);
	fString(rate_s);
	fString(id_s);
	fString(rank_s);
}
JSONArray_t BDD_getFilmsOrderedByRank(BDD bdd)
{
	JSONArray_t films = BDD_Films(bdd);
	JSONArray_t l = JSONArray_new();
	JSONObject_t f = 0;
	size_t c = 0, size = JSONArray_size(films);
	while(c < size)
	{
		f = BDD_getFilmByRank(bdd, c + 1);
		if(f == 0)
		{
			break;
		}
		JSONArray_add(l,JSONObject_getCopy(f));
		++c;
	}
	return l;
}

bool BDD_setFilmRateOfUser(BDD bdd, int film_id, int user_id, int rate)
{
	lock(bdd);
	JSONObject_t user =  BDD_getUserById(bdd, user_id);
	if(user != 0)
	{
		JSONObject_t history = JSONObject_get(user, autoString("History"));
		if(history == 0)
		{
			history = JSONObject_new();
			JSONObject_set(user, autoString("History"), history);
		}
		JSONArray_t rates = JSONObject_get(history, autoString("Rates"));
		if(rates == 0)
		{
			rates = JSONArray_new();
			JSONObject_set(history, autoString("Rates"), rates);
		}
		size_t i = 0, size = JSONArray_size(rates), done = 0;
		while(i < size)
		{
			JSONObject_t mv = JSONArray_get(rates, i);
			if(JSONObject_intValueOf(mv, autoString("Id")) == film_id)
			{
				printf("Update rate !\n");
				JSONObject_set(mv, autoString("Rate"), JSONInt_new(rate));
				done = 1;
				break;
			}
			++i;
		}
		if(done == 0)
		{
			JSONObject_t n_mv = JSONObject_new();
			JSONObject_set(n_mv, autoString("Id"), JSONInt_new(film_id));
			JSONObject_set(n_mv, autoString("Rate"), JSONInt_new(rate));
			JSONArray_add(rates, n_mv);
			printf("Set new rate !\n");
			// printf("TEST\n");
			// printf("%s\n", cString(JSONArray_asString(n_mv, 0)));
			// printf("%s\n", cString(JSONArray_asString(rates, 0)));
		}
		BDD_UpdateRates(bdd);
		BDD_UpdateRanks(bdd);
		unlock(bdd);
		printf("Sauvegarde BDD...\n");
		BDD_save(bdd);
		printf("BDD sauvee.\n");
		freeAutoString();
		return 1;
	}
	else
	{
		printf("Utilisateur introuvable...Modification impossible\n");
	}
	unlock(bdd);
	return 0;
}

JSONArray_t BDD_getUserRates(BDD bdd, int user_id)
{
	JSONArray_t users = BDD_Users(bdd);
	int i;
	JSONObject_t current_user = 0;
	int id = 0;
	int size = JSONArray_size(users);
	for(i=0 ; i<size ; i++)
	{
		current_user = JSONArray_get(users, i);
		id = JSONObject_intValueOf(current_user, autoString("Id"));
		if(id == user_id)
		{
			break;
		}
	}
	if(current_user == 0)
	{
		printf("Pas de user valide\n");
		freeAutoString();
		return JSONArray_new();
	}
	JSONObject_t history = JSONObject_get(current_user, autoString("History"));
	if(history == 0)
	{
		printf("History fait défaut\n");
		freeAutoString();
		return JSONArray_new();
	}
	JSONArray_t rates = JSONObject_get(history, autoString("Rates"));
	if(rates == 0)
	{
		printf("Rates fait défaut\n");
		freeAutoString();
		return JSONArray_new();
	}
	printf("Bonne extraction des résultats\n");
	return rates;
}
