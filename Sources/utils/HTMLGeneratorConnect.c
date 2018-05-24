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
		return newStringFromCharStar("<meta http-equiv=\"refresh\" content=\"0.5;url=exec://main.json?connect=1\" />");
	}
	else
	{
		setString(connexion->addr_s, autoString(""));
		return newStringFromCharStar("<meta http-equiv=\"refresh\" content=\"0.5;url=exec://boot.json?connect=0\" />");
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
String_t HTMLMenuLogin(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t d = getParam(AS("d"), params);
	String_t login = getParam(AS("login"), params);
	String_t password = getParam(AS("password"), params);
	String_t con = getParam(AS("c"), params);
	String_t r = newString();
	String_t div = newStringFromCharStar("<div class=\"ctr\">");
	String_t tmp = 0;
	concatString(r, div);
	fString(div);
	String_t msg = 0;
	if(connexion->sid != 0)
	{
		if(d != 0)
		{
			RequestAnswer a = Client_Logout(connexion);
			if(a != 0)
			{
				fString(connexion->sid);
				JSONObject_delete(connexion->user);
				connexion->user = 0;
				if(a->code == 0)
				{
					msg = newStringFromCharStar("<span class=\"green\">Déconnexion réussie !</span><script>location.href = \"exec://login.json\";</script>");
				}
				else
				{
					msg = newStringFromCharStar("<span class=\"green\">Déconnexion forcée: non connecté !</span>");
				}
				freeRequestAnswer(a);
			}
			else
			{
				msg = newStringFromCharStar("<span class=\"red\">Déconnexion impossible !</span>");
			}
		}
	}
	else
	{
		if(con != 0)
		{
			if(login != 0 && password != 0)
			{
				JSONObject_t obj = JSONObject_new();
				JSONObject_set(obj, AS("Login"), JSONString_new(login));
				JSONObject_set(obj, AS("Password"), JSONString_new(password));
				RequestAnswer a = Client_Login(connexion, obj);
				if(a != 0)
				{
					if(a->code == 0)
					{
						JSONObject_t ans = JSONObject_get(a->obj, AS("Answer")), u = 0;
						if(ans != 0)
						{
							u = JSONObject_get(ans, AS("User"));
						}
						if(u != 0)
						{
							connexion->user = JSONObject_getCopy(u);
							connexion->sid = newStringFromString(JSONObject_stringValueOf(ans, AS("SessionId")));
							msg = newStringFromCharStar("<span class=\"green\">Connexion réussie !</span><script>location.href = \"exec://login.json\";</script>");
						}
						else
						{
							msg = newStringFromCharStar("<span class=\"red\">Réponse invalide du serveur....</span>");
						}
					}
					else
					{
						msg = newStringFromCharStar("<span class=\"red\">Une erreur est survenue: ");
						concatString(msg, JSONObject_stringValueOf(a->obj, AS("Error")));
						tmp = newStringFromCharStar("</span>");
						concatString(msg, tmp);
						fString(tmp);
					}
					freeRequestAnswer(a);
				}
				else
				{
					msg = newStringFromCharStar("<span class=\"red\">Erreur de connexion au serveur, veuillez ré-essayer...</span>");
				}
			}
			else
			{
				msg = newStringFromCharStar("<span class=\"red\">Erreur de transmission de paramètres, veuillez recommencer...</span>");
			}
		}
	}
	if(connexion->sid != 0)
	{
		div = newStringFromCharStar("<h1>Deconnexion</h1>Cliquez ici pour vous déconnecter: <br /><a href=\"exec://login.json?d=1\" />Se déconnecter</a><br />");
		concatString(r, div);
		fString(div);
	}
	else
	{
		div = newStringFromCharStar("<h1>Connexion</h1>Vous n'êtes pas connecté à un compte utilisateur, connectez vous :) <br /><form action=\"exec://login.json\" method=\"get\" ><table style=\"text-align: left;\" class=\"ctr2\"><tr><td>Login: </td><td><input type=\"text\" name=\"login\" placeholder=\"Login...\" /></td></tr><tr><td>Mot de passe:</td><td><input type=\"password\" name=\"password\" placeholder=\"Mot de passe...\" /></td></tr><tr><td colspan=\"2\" style=\"text-align: center;\"><input type=\"submit\" value=\"Connexion\" /><input type=\"hidden\" name=\"c\" value=\"1\" /></td></tr></table></form><br />");
		concatString(r, div);
		fString(div);
	}
	if(msg != 0)
	{
		concatString(r, msg);
		fString(msg);
	}
	div = newStringFromCharStar("</div>");
	concatString(r, div);
	fString(div);
	return r;
}
