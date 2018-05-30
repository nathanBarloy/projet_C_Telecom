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
		if(connexion->user != 0)
		{
			JSONArray_t films = serverGetCollaborativeRecommnendation(connexion);
			String_t tmp = newStringFromCharStar("<div class=\"filmDIV\">");
			if(JSONArray_size(films) != 0)
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
		JSONArray_t films = serverGetRandRecommendation(connexion);
		//printf("films_random : %s\n", cString(JSONArray_asString(films, 0)));
		String_t tmp = newStringFromCharStar("<div class=\"filmDIV\">");
		if(films != 0 && JSONArray_size(films) > 0)
		{
			printf("GOOOOOOOOOOO\n");
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
	else if(equalsString(selected, AS("viewed")))//Film déjà vu
	{
		if(connexion->user != 0)
		{
			JSONArray_t rated_films = serverGetUserRates(connexion);
			JSONArray_t displayed_films = JSONArray_new();
			int size_rf = JSONArray_size(rated_films);
			if(size_rf != 0)
			{
				int i;
				for (i=size_rf-1 ; i>=0 ; i--)
				{
					int id_film = JSONObject_intValueOf(JSONArray_get(rated_films, i), autoString("Id"));
					JSONObject_t film = serverGetFilmById(connexion, id_film);
					JSONArray_add(displayed_films, film);
				}
			}
			JSONArray_delete(rated_films);
			String_t tmp = newStringFromCharStar("<div class=\"filmDIV\">");
			if(JSONArray_size(displayed_films) != 0)
			{
				size_t c = 0, size = JSONArray_size(displayed_films);
				concatString(r, tmp);
				fString(tmp);
				while(c < size)
				{
					tmp = HTMLFilm(connexion, json, JSONArray_get(displayed_films, c), params);
					concatString(r, tmp);
					fString(tmp);
					++c;
				}
			}
			else
			{
				tmp = newStringFromCharStar("Impossible de récupérer les films depuis le serveur... la connexion à échoué.");
				concatString(r, tmp);
				fString(tmp);
			}
			JSONObject_delete(displayed_films);
			tmp = newStringFromCharStar("</div>");
			concatString(r, tmp);
			fString(tmp);
		}
	}
	return r;
}
