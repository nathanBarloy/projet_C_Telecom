#ifndef BDD_H
#define BDD_H
#include <pthread.h>
#include <JSONAll.h>
struct BDD
{
	JSONObject_t* json;
	pthread_mutex_t mutex;
};
typedef struct BDD* BDD;
#define lock(a) pthread_mutex_lock(&a->mutex);
#define unlock(a) pthread_mutex_unlock(&a->mutex);
BDD BDD_load();
int BDD_save(BDD bdd);
BDD BDD_new();
BDD BDD_free(BDD bdd);
JSONArray_t BDD_Users(BDD bdd);
JSONArray_t BDD_Films(BDD bdd);
#endif
