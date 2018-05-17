#include "HTMLGenerator.h"
#include "../sys/ClientRequests.h"
#include "JSONShortcut.h"

String_t HTMLFicheFilm(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
  String_t reponse = newString();
  // le paramètre en question contient l'id du film cliqué
  String_t selected = getParam(AS("selected"), params);
  String_t tmp = newStringFromCharStar("<h1>");
  concatString(reponse, tmp);
  fString(tmp);
  JSONObject_t films = serverGetFilms(connexion);
  JSONObject_t film = JSONArray_get(film, 0);
  printf("%s\n", JSONObject_stringValueOf(film, "Title"));
  concatString(reponse, JSONObject_stringValueOf(film, "Title"));
  tmp = newStringFromCharStar("</div>");
  concatString(reponse, tmp);
  fString(tmp);
  JSONObject_delete(films);
  JSONObject_delete(film);
  return reponse;
}
