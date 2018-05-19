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

    tmp = newStringFromCharStar("<div class=\"block1\">");
    concatString(reponse, tmp);
    fString(tmp);
    concatString(reponse, newStringFromCharStar("<div class=\"cover\">"));
    //image
    JSONObject_t img = JSONObject_new();
    JSONObject_set(img, AS("html"), JSONString_new(AS("class=\"filmImg\"")));
    JSONObject_set(img, AS("src"), JSONString_new(JSONObject_stringValueOf(film, AS("Cover"))));
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
    concatString(reponse, newStringFromCharStar("<div class=\"block_data\"><div class=\"line_box\">"));
    //Synopsis
    concatString(reponse, newStringFromCharStar("<div class=\"box_body\"><h2>Synopsis</h2><p>"));
    concatString(reponse, JSONObject_stringValueOf(film, AS("Description")));
    concatString(reponse, newStringFromCharStar("</p></div>"));
    concatString(reponse, newStringFromCharStar("<div class=\"box_body\"><h2>Détails</h2><h3>Durée :</h3><p>"));
    concatString(reponse, JSONObject_stringValueOf(film, AS("Duration")));
    concatString(reponse, newStringFromCharStar("mins</p><h3>Genres :</h3><p>"));
    //print des genres du film
    int i = 0;
    JSONObject_t genres = JSONObject_getArray(film, newStringFromCharStar("Genres"));
    for(i = 0 ; i<JSONArray_size(genres) ; i++)
    {
      concatString(reponse, JSONObject_stringValue(JSONArray_get(genres, i)));
      concatString(reponse, newStringFromCharStar(", "));
    }
    JSONObject_delete(genres);
    concatString(reponse, newStringFromCharStar("</p><h3>Type :</h3><p>"));
    concatString(reponse, JSONObject_stringValueOf(film, AS("Type")));
    concatString(reponse, newStringFromCharStar("</p>"));
    //fin premiere ligne
    concatString(reponse, finDiv);
    concatString(reponse, finDiv);
    concatString(reponse, newStringFromCharStar("<div class=\"line_box\">"));
    concatString(reponse, newStringFromCharStar("<div class=\"box_body\"><h2>Director(s) :</h2><p>"));
    JSONObject_t director = JSONObject_getArray(film, newStringFromCharStar("Directors"));
    for(i = 0 ; i<JSONArray_size(director) ; i++)
    {
      concatString(reponse, JSONObject_stringValue(JSONArray_get(director, i)));
      concatString(reponse, newStringFromCharStar(", "));
    }
    JSONObject_delete(director);
    concatString(reponse, newStringFromCharStar("</p></div>"));
    concatString(reponse, newStringFromCharStar("<div class=\"box_body\"><h2>Actors :</h2><p>"));
    JSONObject_t actors = JSONObject_getArray(film, newStringFromCharStar("Actors"));
    for(i = 0 ; i<JSONArray_size(actors) ; i++)
    {
      concatString(reponse, JSONObject_stringValue(JSONArray_get(actors, i)));
      concatString(reponse, newStringFromCharStar(", "));
    }
    JSONObject_delete(actors);
    concatString(reponse, newStringFromCharStar("</p></div>"));
    //fin ligne 2
    concatString(reponse, finDiv);
    //fin block_data
    concatString(reponse, finDiv);
    // fin data
    concatString(reponse, finDiv);
    //fin block
    concatString(reponse, finDiv);

    //seconde box
    concatString(reponse, newStringFromCharStar("<div class=\"box2\">"));
    JSONObject_t ytPlayer = JSONObject_new();
    //dimensions gérées automatiquement 
    // JSONObject_set(ytPlayer, AS("width"), JSONString_new(AS("560")));
    // JSONObject_set(ytPlayer, AS("height"), JSONString_new(AS("315")));
    JSONObject_set(ytPlayer, AS("link"), JSONString_new(JSONObject_stringValueOf(film, AS("Url"))));
    tmp = HTMLYoutubePlayer(connexion, json, ytPlayer, params);
    concatString(reponse, tmp);
    fString(tmp);
    concatString(reponse, finDiv);

    JSONObject_delete(films);
    JSONObject_delete(img);
    JSONObject_delete(ytPlayer);
    fString(finDiv);
  }
  else
  {

  }
  return reponse;
}
