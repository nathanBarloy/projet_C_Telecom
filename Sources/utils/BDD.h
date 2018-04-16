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

BDD BDD_load();
int BDD_save(BDD bdd);
BDD BDD_new();
BDD BDD_free(BDD bdd);
JSONArray_t BDD_Users(BDD bdd);
JSONArray_t BDD_Films(BDD bdd);
#endif
