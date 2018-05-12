#include "HTMLGenerator.h"
#include "../sys/ClientRequests.h"
String_t HTMLConnectToServer(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t ip = getParam(autoString("ip"), params);
	if(ip != 0)
	{
		setString(connexion->addr_s, ip);
	}
	if(ip != 0 && serverExists(connexion))
	{
		return newStringFromCharStar("<meta http-equiv=\"refresh\" content=\"url=exec://main.json?connect=1;0\" />");
	}
	else
	{
		setString(connexion->addr_s, autoString(""));
		return newStringFromCharStar("<meta http-equiv=\"refresh\" content=\"url=exec://boot.json?connect=1;0\" />");
	}
}
