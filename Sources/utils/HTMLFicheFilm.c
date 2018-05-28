#include "HTMLGenerator.h"
#include "../sys/ClientRequests.h"
#include "JSONShortcut.h"

String_t HTMLFicheFilm(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t id = getParam(AS("id"), params);
	if(getParam(AS("value"), params) != 0)
	{
		// printf("cccccc\n");
		int fid = atoi(cString(id));
		int uid = atoi(cString(JSONObject_stringValueOf(connexion->user, autoString("Id"))));
		int val = atoi(cString(getParam(AS("value"), params)));
		// printf("fid=%d\nuid=%d\nval=%d\n", fid, uid, val);
		serverSetFilmRateOfUser(connexion, fid, val);
	}
	String_t reponse = newString();
	// le paramètre en question contient l'id du film cliqué
	if(!(id == 0 || equalsString(id, AS(""))))
	{
	String_t tmp = 0;
	String_t finDiv = newStringFromCharStar("</div>");

	//récupération de objet JSON du film en question
	//JSONObject_t films = serverGetFilms(connexion);
	int value_id = atoi(cString(id))/*-1*/;
	JSONObject_t film = serverGetFilmById(connexion, value_id);//JSONArray_get(films, value_id);
	if(film == 0)
	{
		concatString(reponse, autoString("<h1>Film introuvable !</h1>"));
		return reponse;
	}
	tmp = newStringFromCharStar("<div class=\"block1\">");
	concatString(reponse, tmp);
	fString(tmp);
	tmp = newStringFromCharStar("<div class=\"cover\">");
	concatString(reponse, tmp);
	fString(tmp);
	//image
	JSONObject_t img = JSONObject_new();
	JSONObject_set(img, AS("html"), JSONString_new(AS("class=\"filmImg\"")));
	JSONObject_set(img, AS("src"), JSONString_new(JSONObject_stringValueOf(film, AS("Cover"))));
	tmp = HTMLImg(connexion, json, img, params);
	concatString(reponse, tmp);
	fString(tmp);
	//fin div cover
	tmp = HTMLFilmRate(connexion, json, film, params);
	concatString(reponse, tmp);
	fString(tmp);
	concatString(reponse, finDiv);
	//Ajout du titre
	tmp = newStringFromCharStar("<div class=\"data\">");
	concatString(reponse, tmp);
	fString(tmp);
	tmp = newStringFromCharStar("<div class=\"title\">");
	concatString(reponse, tmp);
	fString(tmp);
	tmp = newStringFromCharStar("<span class=\"name\">");
	concatString(reponse, tmp);
	fString(tmp);
	concatString(reponse, JSONObject_stringValueOf(film, AS("Title")));
	tmp = newStringFromCharStar("</span>");
	concatString(reponse, tmp);
	fString(tmp);
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
	//Stars

	tmp = HTMLRatingStars(connexion, json, film, params);
	concatString(reponse, tmp);
	fString(tmp);
	tmp = newStringFromCharStar("<table class=\"block_data\"><tr>");
	concatString(reponse, tmp);
	fString(tmp);
	//Synopsis
	tmp = newStringFromCharStar("<td class=\"box_body\" colspan=\"2\"><h2>Synopsis</h2></td></tr><tr><td colspan=\"2\">");
	concatString(reponse, tmp);
	fString(tmp);
	concatString(reponse, JSONObject_stringValueOf(film, AS("Description")));
	tmp = newStringFromCharStar("</td></tr></table>");
	concatString(reponse, tmp);
	fString(tmp);
	//Youtube
	//seconde box
	tmp = newStringFromCharStar("<a href=\"\" onclick=\"return showBA();\" >Voir la bande annonce</a><div id=\"ba_hover\" class=\"ba_hover\"><div id=\"ba\" class=\"ba\"><h3>Bande-Annonce: <a href=\"\" onclick=\"return hideBA();\" >( X )</a></h3>");//style=\"text-align: center;\" //style=\"width: 800px;margin-left:auto;margin-right: auto;\"
	concatString(reponse, tmp);
	fString(tmp);
	JSONObject_t ytPlayer = JSONObject_new();
	JSONObject_set(ytPlayer, AS("width"), JSONString_new(autoString("800px")));
	JSONObject_set(ytPlayer, AS("height"), JSONString_new(autoString("450px")));
	JSONObject_set(ytPlayer, AS("link"), JSONString_new(JSONObject_stringValueOf(film, AS("Url"))));
	tmp = HTMLYoutubePlayer(connexion, json, ytPlayer, params);
	concatString(reponse, tmp);
	fString(tmp);
	concatString(reponse, finDiv);//fin ba
	concatString(reponse, finDiv);//fin ba_hover
	//Fin Youtube
	tmp = newStringFromCharStar("<table><tr><td class=\"box_body\" colspan=\"2\"><h2>Détails</h2></td></tr><tr><td>");
	concatString(reponse, tmp);
	fString(tmp);
	tmp = newStringFromCharStar("<h3>Durée :</h3></td><td><h3>Genres :</h3></td></tr><tr><td>");
	concatString(reponse, tmp);
	fString(tmp);
	concatString(reponse, JSONObject_stringValueOf(film, AS("Duration")));
	tmp = newStringFromCharStar("mins</td><td>");
	concatString(reponse, tmp);
	fString(tmp);
	//print des genres du film
	int i = 0;
	tmp = newStringFromCharStar("Genres");
	JSONObject_t genres = JSONObject_getArray(film, tmp);
	fString(tmp);
	for(i = 0 ; i<JSONArray_size(genres) ; i++)
	{
	  concatString(reponse, JSONObject_stringValue(JSONArray_get(genres, i)));
	  tmp = newStringFromCharStar(", ");
	  concatString(reponse, tmp);
	  fString(tmp);
	}
	JSONObject_delete(genres);
	tmp = newStringFromCharStar("</td></tr><tr><td><h3>Type :</h3></td><td><h3>Director(s) :</h3></td></tr><tr><td>");
	concatString(reponse, tmp);
	fString(tmp);
	concatString(reponse, JSONObject_stringValueOf(film, AS("Type")));
	tmp = newStringFromCharStar("</td><td>");
	concatString(reponse, tmp);
	fString(tmp);
	//fin premiere ligne
	/*concatString(reponse, finDiv);
	concatString(reponse, finDiv);
	concatString(reponse, newStringFromCharStar(""));*/
	tmp = newStringFromCharStar("Directors");
	JSONObject_t director = JSONObject_getArray(film, tmp);
	fString(tmp);
	for(i = 0 ; i<JSONArray_size(director) ; i++)
	{
	  concatString(reponse, JSONObject_stringValue(JSONArray_get(director, i)));
	  tmp = newStringFromCharStar(", ");
	  concatString(reponse, tmp);
	  fString(tmp);
	}
	JSONObject_delete(director);
	tmp = newStringFromCharStar("</td></tr><tr><td colspan=\"2\">");
	concatString(reponse, tmp);
	fString(tmp);
	tmp = newStringFromCharStar("<h3>Actors :</h3></td></tr><tr><td colspan=\"2\">");
	concatString(reponse, tmp);
	fString(tmp);
	tmp = newStringFromCharStar("Actors");
	JSONObject_t actors = JSONObject_getArray(film, tmp);
	fString(tmp);
	for(i = 0 ; i<JSONArray_size(actors) ; i++)
	{
	  concatString(reponse, JSONObject_stringValue(JSONArray_get(actors, i)));
	  tmp = newStringFromCharStar(", ");
	  concatString(reponse, tmp);
	  fString(tmp);
	}
	JSONObject_delete(actors);
	tmp = newStringFromCharStar("</td></tr></table>");
	concatString(reponse, tmp);
	fString(tmp);
	/*
	//fin ligne 2
	concatString(reponse, finDiv);
	//fin block_data
	concatString(reponse, finDiv);
	// fin data
	concatString(reponse, finDiv);
	//fin block
	concatString(reponse, finDiv);*/


    //Affichage des recommandations
	tmp = newStringFromCharStar("<h1>Recommandé si vous aimez ce film:</h1><div>");
	concatString(reponse, tmp);
	fString(tmp);
	JSONArray_t reco = serverGetFilmRecommendation(connexion, value_id);
	if(reco != 0)
	{
		size_t c = 1, size = JSONArray_size(reco);
		String_t f = 0;
		JSONObject_t tmpf = 0;
		String_t id_s = newStringFromCharStar("Id");
		while(c < size && c < 11)
		{
			tmpf = JSONArray_get(reco, c);
			f = HTMLFilm(connexion, json, tmpf, params);
			concatString(reponse, f);
			fString(f);
			++c;
		}
		fString(id_s);
	}
	else
	{
		tmp = newStringFromCharStar("Impossible d'obtenir les recommendations...\n");
		concatString(reponse, tmp);
		fString(tmp);
	}
	concatString(reponse, finDiv);//Fin de div des reco

	//Fin d'affichage des recommendations
    //JSONObject_delete(films);
    JSONObject_delete(img);
    JSONObject_delete(ytPlayer);
    fString(finDiv);

  }
  else
  {

  }
  return reponse;
}
