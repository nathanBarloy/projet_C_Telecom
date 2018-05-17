#include "HTMLGenerator.h"
#include "../sys/ClientRequests.h"
#include "JSONShortcut.h"
String_t HTMLMenuContent(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t r = newString();
	String_t selected = getParam(AS("selected"), params);
	String_t tmp = 0;
	/*printf("Selected: %p\n", selected);
	if(selected != 0)
	{
		printf("Selected: %s\n", cString(selected));
	}*/
	if(selected == 0 || equalsString(selected, AS("")))//Affichage des films
	{
		JSONObject_t films = serverGetFilms(connexion);
		String_t br = newStringFromCharStar("<br />"), div = newStringFromCharStar("<div class=\"film\">"), ediv = newStringFromCharStar("</div>"), tmp = 0;
		size_t c = 0, size = JSONArray_size(films);
		JSONObject_t img = JSONObject_new();
		while(c < size)
		{
			concatString(r, div);
			JSONObject_set(img, AS("src"), JSONObject_stringValueOf(JSONArray_get(films, c), AS("Cover")));
			tmp = HTMLImg(connexion, json, img, params);
			concatString(r, br);
			concatString(r, JSONObject_stringValueOf(JSONArray_get(films, c), AS("Title")));
			concatString(r, ediv);
			++c;
		}
		JSONObject_delete(img);
		JSONObject_delete(films);
		fString(br);
		fString(div);
		fString(ediv);
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
