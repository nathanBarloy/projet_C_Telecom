#include "HTMLGenerator.h"
#include "../sys/ClientRequests.h"
#include "JSONShortcut.h"
#include "../gui/Export.h"

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

		JSONArray_t export = JSONArray_new();
		if(connexion->user != 0)
		{
			JSONArray_t films = serverGetCollaborativeRecommnendation(connexion);
			if(JSONArray_size(films) != 0)
			{
				tmp = newStringFromCharStar("<div class=\"titre\"><h1>Recommandé pour vous :</h1>(<a href=\"exec://export.json\" >Exporter...</a>)</div><div class=\"filmDIV\">");
				concatString(r, tmp);
				fString(tmp);
				size_t c = 0, size = JSONArray_size(films);
				JSONObject_t tmpf = 0;
				while(c < size)
				{
					tmpf = JSONArray_get(films, c);
					tmp = HTMLFilm(connexion, json, tmpf, params);
					JSONArray_add(export, JSONObject_getCopy(tmpf));
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
			JSONObject_t e = getExport();
			JSONObject_set(e, AS("Data"), export);
			tmp = newStringFromCharStar("recommendationsCollab.json");
			JSONObject_set(e, AS("Name"), JSONString_new(tmp));
			fString(tmp);
			JSONObject_t u = JSONObject_get(json, AS("url"));
			if(u != 0 && JSONObject_getType(u) == STRING)
			{
				tmp = newStringFromCharStar("?selected=");
				concatString(tmp, selected);
				String_t tmp2 = newStringFromString(JSONString_get(u));
				concatString(tmp2, tmp);
				JSONString_set(u, tmp2);
				fString(tmp);
				fString(tmp2);
			}
			else
			{
				u = JSONString_new(autoString(""));
			}
			JSONObject_set(e, AS("Url"), u);
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
		JSONArray_t export = JSONArray_new();
		if(connexion->user != 0)
		{
			JSONArray_t rated_films = serverGetUserRates(connexion);
			JSONArray_t displayed_films = JSONArray_new();
			int size_rf = JSONArray_size(rated_films);
			if(size_rf != 0)
			{
				tmp = newStringFromCharStar("<div class=\"titre\"><h1>Mes films :</h1>(<a href=\"exec://export.json\" >Exporter...</a>)</div><div class=\"filmDIV\">");
				concatString(r, tmp);
				fString(tmp);
				int i;
				for (i=size_rf-1 ; i>=0 ; i--)
				{
					int id_film = JSONObject_intValueOf(JSONArray_get(rated_films, i), autoString("Id"));
					JSONObject_t film = serverGetFilmById(connexion, id_film);
					JSONArray_add(displayed_films, film);
					JSONArray_add(export, JSONObject_getCopy(film));
				}
			}
			JSONArray_delete(rated_films);
			if(JSONArray_size(displayed_films) != 0)
			{
				size_t c = 0, size = JSONArray_size(displayed_films);
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
			JSONObject_t e = getExport();
			JSONObject_set(e, AS("Data"), export);
			tmp = newStringFromCharStar("films_vu.json");
			JSONObject_set(e, AS("Name"), JSONString_new(tmp));
			fString(tmp);
			JSONObject_t u = JSONObject_get(json, AS("url"));
			if(u != 0 && JSONObject_getType(u) == STRING)
			{
				tmp = newStringFromCharStar("?selected=");
				concatString(tmp, selected);
				String_t tmp2 = newStringFromString(JSONString_get(u));
				concatString(tmp2, tmp);
				JSONString_set(u, tmp2);
				fString(tmp);
				fString(tmp2);
			}
			else
			{
				u = JSONString_new(autoString(""));
			}
			JSONObject_set(e, AS("Url"), u);
			JSONObject_delete(displayed_films);
			tmp = newStringFromCharStar("</div>");
			concatString(r, tmp);
			fString(tmp);
		}
	}
	return r;
}
