#ifndef JSON_CHECK_H
#define JSON_CHECK_H
#include <JSONAll.h>
bool JSON_rightTypeOrNull(JSONObject_t obj, JSONType_t type);//Vérifie que l'objet existe avec le bon type, ou est nul.
bool JSON_rightTypeNotNull(JSONObject_t obj, JSONType_t type);//Vérifie que l'objet existe avec le bon type, ou est nul.
bool JSON_checkBasicArray(JSONArray_t arr, JSONType_t type);//Vérifie que l'objet est un array, et contient le type défini.
bool JSON_checkUser(JSONObject_t user, bool light);//Vérifie la validité d'un utilisateur, si light=true: ne vérifie pas l'Id, et les données spécifiques au serveur
bool JSON_checkFilm(JSONObject_t film);//Vérifie la validité d'un film
bool JSON_checkDate(JSONObject_t d);//Vérifie la validité d'une date (format)

#endif
