#include "HTMLGenerator.h"
#include "../sys/ClientRequests.h"
#include "JSONShortcut.h"
String_t HTMLConnectToServer(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t ip = getParam(autoString("ip"), params);
	String_t ct = getParam(AS("connect"), params);
	if(ip != 0 && (ct == 0 || equalsString(ct, AS("0"))))
	{
		setString(connexion->addr_s, ip);
	}
	if(connexion->addr_s != 0 && !equalsString(connexion->addr_s, AS("")) && serverExists(connexion))
	{
		return newStringFromCharStar("<meta http-equiv=\"refresh\" content=\"1;url=exec://main.json?connect=1\" />");
	}
	else
	{
		setString(connexion->addr_s, autoString(""));
		return newStringFromCharStar("<meta http-equiv=\"refresh\" content=\"1;url=exec://boot.json?connect=0\" />");
	}
}
String_t HTMLCheckConnected(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t c = getParam(AS("connect"), params);
	if(c != 0)
	{
		if(!equalsString(c, autoString("1")))
		{
			return newStringFromCharStar("<div class=\"red\">La connexion au serveur a échoué.</div>");
		}
		else
		{
			return newStringFromCharStar("<div class=\"green\">Vous êtes maintenant connecté au serveur.</div>");
		}
	}
	return newString();
}
