#include "HTMLGenerator.h"
#include "JSONShortcut.h"
#include <String/AutoString.h>
#include <JSONAll.h>
String_t HTMLFilm(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t a = newStringFromCharStar("<a href=\"exec://film.json?id="), tmp = newStringFromCharStar("\" >");
	concatString(a, JSONObject_stringValueOf(param, AS("Id")));
	concatString(a, tmp);
	fString(tmp);
	String_t r = newString(), d1 = newStringFromCharStar("<div class=\"filmD1\">"), d2 = newStringFromCharStar("<div class=\"filmD2\">"), div = newStringFromCharStar("<div class=\"film\">"), ediv = newStringFromCharStar("</div>");
	JSONObject_t img = JSONObject_new();
	JSONObject_set(img, AS("html"), JSONString_new(AS("class=\"filmImg\"")));
	concatString(r, a);
	concatString(r, div);
	concatString(r, d1);
	JSONObject_set(img, AS("src"), JSONString_new(JSONObject_stringValueOf(param, AS("Cover"))));
	tmp = HTMLImg(connexion, json, img, params);
	concatString(r, tmp);
	concatString(r, ediv);
	concatString(r, d2);
	concatString(r, JSONObject_stringValueOf(param, AS("Title")));
	concatString(r, ediv);
	concatString(r, ediv);
	JSONObject_delete(img);
	fString(d1);
	fString(d2);
	fString(div);
	fString(ediv);
	tmp = newStringFromCharStar("</a>");
	concatString(r, tmp);
	fString(tmp);
	return r;
}
