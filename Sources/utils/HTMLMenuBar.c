#include "HTMLGenerator.h"
#include "JSONShortcut.h"
String_t HTMLMenuBar(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t r = newStringFromCharStar("<div class=\"menubar\"><a href=\"exec://main.json\" title=\"Menu principal\" >Accueil</a> - "), end = newStringFromCharStar("</div>");
	String_t u;
	if(connexion->user != 0)
	{
		u = newStringFromCharStar("<a href=\"exec://profile.json\" title=\"Profil utilisateur\" >");
		String_t u2 = newStringFromCharStar("</a> - <a href=\"exec://login.json\" title=\"Déconnexion\" >Déconnexion</a>");
		concatString(u, JSONObject_stringValueOf(connexion->user, AS("Login")));
		concatString(u, u2);
		fString(u2);

	}
	else
	{
		u = newStringFromCharStar("<a href=\"exec://login.json\" title=\"Connexion\" >Connexion</a> - <a href=\"exec://register.json\" title=\"Inscription\" >Inscription</a>");
	}
	concatString(r, u);
	fString(u);
	concatString(r, end);
	fString(end);
	return r;
}

String_t HTMLMenuBar2(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t r = newStringFromCharStar("<div class=\"menubar\"><a href=\"exec://main.json?selected=\" title=\"Films\" >Films</a> - "), end = newStringFromCharStar("</div>");
	String_t u;
	if(connexion->user != 0)
	{
		u = newStringFromCharStar("<a href=\"exec://main.json?selected=recommended\" title=\"Recommandé pour vous\" >Recommandé pour vous</a> - ");
		concatString(r, u);
		fString(u);
	}
	u = newStringFromCharStar("<a href=\"exec://main.json?selected=trends\" title=\"Tendances\" >Tendances</a> - <a href=\"exec://main.json?selected=random\" title=\"Au hasard\" >Au hasard</a>");
	concatString(r, u);
	fString(u);
	concatString(r, end);
	fString(end);
	return r;
}
