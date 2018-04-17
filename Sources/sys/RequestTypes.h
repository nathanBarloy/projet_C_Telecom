#ifndef REQUEST_TYPES_H
#define REQUEST_TYPES_H
#include <JSONAll.h>
#include <String/String.h>
#include <String/AutoString.h>
//Définition de types
struct RequestAnswer//Type permettant le retour d'une réponse
{
	int code;//Code de retour de la requête
	JSONObject_t obj;
};
typedef struct RequestAnswer* RequestAnswer;
struct RequestQuery//Type permettant le passage d'une requête a une fonction
{
	int id;//Permet de stocker un id sur la requête, pour des raisons pratiques. n'est pas transmis par le réseau
	String_t sid;//Session id, rempli automatiquement par le serveur
	JSONObject_t session;//Session en cours, rempli automatiquement par le serveur
	int connected;//1 si utilisateur connecté, 0 sinon. Rempli automatiquement par le serveur.
	JSONObject_t obj;
};
typedef struct RequestQuery* RequestQuery;

//Constructions/Destructions de types
RequestAnswer newRequestAnswer(int code, JSONObject_t obj);//Génère une structure de réponse
RequestAnswer freeRequestAnswer(RequestAnswer r);//Libère une structure de réponse
RequestQuery newRequestQuery(int id, JSONObject_t obj);//Génère une structure de requête
RequestQuery freeRequestQuery(RequestQuery r);//Libère une structure de réponse

JSONObject_t newJSONRequestQuery(String_t sid, String_t type, JSONObject_t data);
#endif
