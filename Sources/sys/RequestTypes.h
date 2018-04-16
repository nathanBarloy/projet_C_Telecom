#include <JSONAll.h>
//Définition de types
struct RequestAnswer//Type permettant le retour d'une réponse
{
	int code;
	JSONObject_t obj;
};
typedef struct RequestAnswer* RequestAnswer;
struct RequestQuery//Type permettant le passage d'une requête a une fonction
{
	int id;
	JSONObject_t obj;
};
typedef struct RequestQuery* RequestQuery;

//Constructions/Destructions de types
RequestAnswer newRequestAnswer(int code, JSONObject_t obj);//Génère une structure de réponse
RequestAnswer freeRequestAnswer(RequestAnswer r);//Libère une structure de réponse
RequestQuery newRequestQuery(int id, JSONObject_t obj);//Génère une structure de requête
RequestQuery freeRequestQuery(RequestQuery r);//Libère une structure de réponse
