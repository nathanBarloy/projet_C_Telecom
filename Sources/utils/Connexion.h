#ifndef CONNEXION_H
#define CONNEXION_H
#include <String/String.h>
#include <JSONAll.h>
struct Connexion//Permet de garder les informations nécessaires à la connexion coté client
{
	String_t addr_s;
	String_t sid;
	JSONObject_t user;
};
typedef struct Connexion* Connexion_t;

Connexion_t newConnexion(char *addr_s);
Connexion_t freeConnexion(Connexion_t c);
String_t Connexion_getSid(Connexion_t c);
void Connexion_setSid(Connexion_t c, String_t sid);
#endif
