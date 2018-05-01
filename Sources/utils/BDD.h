#ifndef BDD_H
#define BDD_H
#include <pthread.h>
#include <JSONAll.h>
#include <Vector/Vector.h>
#include <Map/Map.h>
#include "PthreadShortcut.h"
struct BDD
{
	JSONObject_t* json;
	pthread_mutex_t mutex;
	Vector_t clients;
	Map_t requests;//Défini les liens vers les requêtes
};
typedef struct BDD* BDD;

BDD BDD_load();//Charge la bdd depuis json/bdd.json
int BDD_save(BDD bdd);//Sauvegarde la BDD dans json/bdd.json en créant un backup simple
BDD BDD_new();//Instancie un nouvel objet de BDD
BDD BDD_free(BDD bdd);
JSONArray_t BDD_Users(BDD bdd);//Récupère la liste des utilisateurs depuis la BDD
JSONArray_t BDD_Films(BDD bdd);//Récupère la liste des films depuis la BDD
JSONObject_t BDD_getSid(BDD bdd, String_t sid);//Récupère la session associée a un SID.
bool BDD_checkUser(JSONObject_t user);//Vérifie la validité d'un utilisateur
bool BDD_checkFilm(JSONObject_t film);//Vérifie la validité d'un film
bool BDD_rightTypeOrNull(JSONObject_t obj, JSONType_t type);//Vérifie que l'objet existe avec le bon type, ou est nul.
bool BDD_checkBasicArray(JSONArray_t arr, JSONType_t type);//Vérifie que l'objet est un array, et contient le type défini.
#endif
