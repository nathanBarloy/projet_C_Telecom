#include "Connexion.h"
#include <stdlib.h>

Connexion_t newConnexion(char *addr_s)
{
	Connexion_t c = (Connexion_t) malloc(sizeof(struct Connexion));
	c->addr_s = newStringFromCharStar(addr_s);
	c->sid = 0;
	c->user = 0;
	return c;
}
Connexion_t freeConnexion(Connexion_t c)
{
	if(c->addr_s != 0)
	{
		fString(c->addr_s);
	}
	if(c->sid != 0)
	{
		fString(c->sid);
	}
	if(c->user != 0)
	{
		c->user = JSONObject_delete(c->user);
	}
	free(c);
	return 0;
}
String_t Connexion_getSid(Connexion_t c)
{
	return c->sid != 0 ? c->sid : autoString("");
}
void Connexion_setSid(Connexion_t c, String_t sid)
{
	if(c->sid)
	{
		fString(c->sid);
	}
	c->sid = newStringFromString(sid);
}
