#include "HTMLGenerator.h"
#include "../sys/ClientRequests.h"
#include "JSONShortcut.h"
String_t HTMLConnectToServer(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t ip = getParam(autoString("ip"), params);
	if(ip != 0)
	{
		setString(connexion->addr_s, ip);
	}
	if(ip != 0 && serverExists(connexion))
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
			return newStringFromCharStar("<span class=\"red\">La connexion au serveur a échoué.</span>");
		}
		else
		{
			return newStringFromCharStar("<span class=\"green\">Vous êtes maintenant connecté au serveur.</span>");
		}
	}
	return newString();
}
