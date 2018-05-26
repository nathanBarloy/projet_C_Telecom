#ifndef BDD_H
#define BDD_H
#include <pthread.h>
#include <JSONAll.h>
#include <Vector/Vector.h>
#include <Map/Map.h>
#include "PthreadShortcut.h"
struct BDD
{
	JSONObject_t json;
	pthread_mutex_t mutex;
	Vector_t clients;
	Map_t requests;//Défini les liens vers les requêtes
};
typedef struct BDD* BDD;

BDD BDD_load();//Charge la bdd depuis json/bdd.json
int BDD_save(BDD bdd);//Sauvegarde la BDD dans json/bdd.json en créant un backup simple
BDD BDD_new();//Instancie un nouvel objet de BDD
BDD BDD_free(BDD bdd);
JSONArray_t BDD_Users(BDD bdd);//Récupère la liste des utilisateurs depuis la BD
JSONArray_t BDD_Genres(BDD bdd);//Récupère la liste des genres depuis la BDD
JSONArray_t BDD_Films(BDD bdd);//Récupère la liste des films depuis la BDD
JSONArray_t BDD_Sessions(BDD bdd);
int BDD_Users_maxId(BDD bdd);//Renvoie l'ID maximal des utilisateurs
JSONObject_t BDD_getFilmById(BDD bdd, int id);
JSONObject_t BDD_getFilmByRank(BDD bdd, int id);
JSONObject_t BDD_getUserById(BDD bdd, int id);
JSONObject_t BDD_getSessionById(BDD bdd, String_t sid);
JSONObject_t BDD_getUserByLogin(BDD bdd, String_t login);
JSONArray_t BDD_getFilmsOrderedByRank(BDD bdd);
void BDD_UpdateRate(BDD bdd, JSONObject_t film);
void BDD_UpdateRates(BDD bdd);
void BDD_UpdateRanks(BDD bdd);
void BDD_setFilmRateOfUser(BDD bdd, int film_id, int user_id, int rate);
#endif
