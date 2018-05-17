#include "HTMLGenerator.h"
#include "../sys/ClientRequests.h"
String_t HTMLMenuContent(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t r = newString();
	String_t selected = getParam(AS("selected"), params);
	String_t tmp = 0;
	if(selected == 0 || equalsString(selected, AS("")))//Affichage des films
	{
		JSONObject_t films = serverGetFilms(connexion);
		String_t br = newStringFromCharStar("<br />");
		size_t c = 0, size = JSONArray_size(films);
		while(c < size)
		{
			concatString(r, JSONObject_stringValueOf(JSONArray_get(films, c)), AS("Title"));
			++c;
		}
		JSONObject_delete(films);
	}
	else if(equalsString(selected, AS("recommended")))//Recommandé pour l'utilisateur
	{

	}
	else if(equalsString(selected, AS("trends")))//Tendances
	{

	}
	else if(equalsString(selected, AS("random")))//Au hasard
	{

	}
	return r;
}
