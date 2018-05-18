#include "HTMLGenerator.h"
#include "../sys/ClientRequests.h"
#include "JSONShortcut.h"

String_t HTMLFicheFilm(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
  String_t reponse = newString();
  // le paramètre en question contient l'id du film cliqué
  String_t id = getParam(AS("id"), params);
  if(!(id == 0 || equalsString(id, AS(""))))
  {
    String_t tmp = 0;
    String_t finDiv = newStringFromCharStar("</div>");

    //récupération de objet JSON du film en question
    JSONObject_t films = serverGetFilms(connexion);
    int value_id = atoi(cString(id))-1;
    JSONObject_t film = JSONArray_get(films, value_id);
    
    tmp = newStringFromCharStar("<div class=\"block\">");
    concatString(reponse, tmp);
    fString(tmp);
    concatString(reponse, newStringFromCharStar("<div class=\"cover\">"));
    //image
    JSONObject_t img = JSONObject_new();
    JSONObject_set(img, AS("html"), JSONString_new(AS("class=\"filmImg\"")));
    //PROBLEME AVEC LES COVERS DANS BDD ?
    // Manière crade, je suis fatigué
    tmp = newStringFromCharStar("img/covers/");
    char valeur_string[50];
    sprintf(valeur_string, "%d", value_id);
    concatString(tmp, newStringFromCharStar(valeur_string));
    concatString(tmp, newStringFromCharStar(".jpg"));
    JSONObject_set(img, AS("src"), JSONString_new(tmp));
    fString(tmp);
    tmp = HTMLImg(connexion, json, img, params);
    concatString(reponse, tmp);
    fString(tmp);
    //fin div cover
    concatString(reponse, finDiv);
    //Ajout du titre
    concatString(reponse, newStringFromCharStar("<div class=\"data\">"));
    tmp = newStringFromCharStar("<div class=\"title\">");
    concatString(reponse, tmp);
    fString(tmp);
    concatString(reponse, newStringFromCharStar("<span class=\"name\">"));
    concatString(reponse, JSONObject_stringValueOf(film, AS("Title")));
    concatString(reponse, newStringFromCharStar("</span>"));
    //date sortie
    tmp = newStringFromCharStar("<span class=\"date_release\">(");
    concatString(reponse, tmp);
    fString(tmp);
    concatString(reponse, JSONObject_stringValueOf(film, AS("Year")));
    tmp = newStringFromCharStar(")</span>");
    concatString(reponse, tmp);
    fString(tmp);
    //fin titre
    concatString(reponse, finDiv);
    //Synopsis
    tmp = newStringFromCharStar("<div class=\"synopsis_box\">");
    concatString(reponse, tmp);
    fString(tmp);
    concatString(reponse, newStringFromCharStar("<h2>Synopsis</h2>"));
    concatString(reponse, newStringFromCharStar("<div class=\"synopsis_content\">"));
    concatString(reponse, JSONObject_stringValueOf(film, AS("Description")));
    //fin synopsis_content
    concatString(reponse, finDiv);
    //synopsis_box
    concatString(reponse, finDiv);
    // fin data
    concatString(reponse, finDiv);
    //fin block
    concatString(reponse, finDiv);
    JSONObject_delete(films);
    JSONObject_delete(img);
    fString(finDiv);
  }
  else
  {

  }
  return reponse;
}
