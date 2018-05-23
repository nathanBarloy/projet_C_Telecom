#ifndef CLIENT_REQUESTS_H
#define CLIENT_REQUESTS_H
#include "RequestTypes.h"
#include <JSONAll.h>
#include "../utils/Connexion.h"
void prints(Connexion_t connexion, String_t message);
RequestAnswer Client_RegisterUser(Connexion_t connexion, JSONObject_t user);
bool serverExists(Connexion_t connexion);
JSONObject_t serverGetFilms(Connexion_t connexion);
JSONObject_t serverGetUsers(Connexion_t connexion);
JSONObject_t serverGetFilmById(Connexion_t connexion, int id);
JSONObject_t serverGetDistanceBetween(Connexion_t connexion, int id1, int id2);
JSONArray_t serverGetFilmRecommendation(Connexion_t connexion, int id);
#endif
