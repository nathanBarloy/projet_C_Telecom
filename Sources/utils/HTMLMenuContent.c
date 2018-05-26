#include "HTMLGenerator.h"
#include "../sys/ClientRequests.h"
#include "JSONShortcut.h"

String_t HTMLMenuContent(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t r = newString();
	String_t selected = getParam(AS("selected"), params);
	String_t tmp = 0;
	if(selected == 0 || equalsString(selected, AS("")))//Affichage des films
	{
		JSONObject_t films = serverGetFilms(connexion);
		String_t tmp = newStringFromCharStar("<div class=\"filmDIV\">");
		if(films != 0)
		{
			size_t c = 0, size = JSONArray_size(films);
			concatString(r, tmp);
			fString(tmp);
			while(c < size)
			{
				tmp = HTMLFilm(connexion, json, JSONArray_get(films, c), params);
				concatString(r, tmp);
				fString(tmp);
				++c;
			}

			JSONObject_delete(films);
		}
		else
		{
			tmp = newStringFromCharStar("Impossible de récupérer les films depuis le serveur... la connexion à échoué.");
			concatString(r, tmp);
			fString(tmp);
		}
		tmp = newStringFromCharStar("</div>");
		concatString(r, tmp);
		fString(tmp);
	}
	else if(equalsString(selected, AS("recommended")))//Recommandé pour l'utilisateur
	{
		// JSONArray_t films = serverGetCollaborativeRecommnendation(connexion);
		// String_t tmp = newStringFromCharStar("<div class=\"filmDIV\">");
		// if(films != 0)
		// {
		// 	size_t c = 0, size = JSONArray_size(films);
		// 	concatString(r, tmp);
		// 	fString(tmp);
		// 	while(c < size)
		// 	{
		// 		tmp = HTMLFilm(connexion, json, JSONArray_get(films, c), params);
		// 		concatString(r, tmp);
		// 		fString(tmp);
		// 		++c;
		// 	}
		//
		// 	JSONObject_delete(films);
		// }
		// else
		// {
		// 	tmp = newStringFromCharStar("Impossible de récupérer les films depuis le serveur... la connexion à échoué.");
		// 	concatString(r, tmp);
		// 	fString(tmp);
		// }
		// tmp = newStringFromCharStar("</div>");
		// concatString(r, tmp);
		// fString(tmp);
	}
	else if(equalsString(selected, AS("trends")))//Tendances
	{
		JSONObject_t films = serverGetFilmOrderedByRank(connexion);
		String_t tmp = newStringFromCharStar("<div class=\"filmDIV\">");
		if(films != 0)
		{
			size_t c = 0, size = JSONArray_size(films);
			concatString(r, tmp);
			fString(tmp);
			while(c < size)
			{
				tmp = HTMLFilm(connexion, json, JSONArray_get(films, c), params);
				concatString(r, tmp);
				fString(tmp);
				++c;
			}

			JSONObject_delete(films);
		}
		else
		{
			tmp = newStringFromCharStar("Impossible de récupérer les films depuis le serveur... la connexion à échoué.");
			concatString(r, tmp);
			fString(tmp);
		}
		tmp = newStringFromCharStar("</div>");
		concatString(r, tmp);
		fString(tmp);
	}
	else if(equalsString(selected, AS("random")))//Au hasard
	{
		// JSONObject_t films = serverGetRandRecommendation(connexion);
		// printf("films_random : %s\n", cString(JSONArray_asString(films, 0)));
		// String_t tmp = newStringFromCharStar("<div class=\"filmDIV\">");
		// if(films != 0)
		// {
		// 	size_t c = 0, size = JSONArray_size(films);
		// 	concatString(r, tmp);
		// 	fString(tmp);
		// 	while(c < size)
		// 	{
		// 		tmp = HTMLFilm(connexion, json, JSONArray_get(films, c), params);
		// 		concatString(r, tmp);
		// 		fString(tmp);
		// 		++c;
		// 	}
		//
		// 	JSONObject_delete(films);
		// }
		// else
		// {
		// 	tmp = newStringFromCharStar("Impossible de récupérer les films depuis le serveur... la connexion à échoué.");
		// 	concatString(r, tmp);
		// 	fString(tmp);
		// }
		// tmp = newStringFromCharStar("</div>");
		// concatString(r, tmp);
		// fString(tmp);
	}
	return r;
}
