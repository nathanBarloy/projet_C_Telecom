#include "ClientRequests.h"
#include "ClientRequest.h"
#include "ClientRunnerContinue.h"
#include <unistd.h>

void prints(Connexion_t connexion, String_t message)
{
	JSONObject_t obj = JSONObject_new();
	JSONObject_set(obj, autoString("message"), JSONString_new(message));
	//printf("%s\n", cString(JSONObject_asString(obj, 0)));
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("prints"), obj));
	RequestAnswer a = clientRequest(connexion, q);
	freeRequestQuery(q);
	freeRequestAnswer(a);
}
RequestAnswer Client_RegisterUser(Connexion_t connexion, JSONObject_t user)
{
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(Connexion_getSid(connexion), autoString("registerUser"), user));
	RequestAnswer a = clientRequest(connexion, q);
	freeRequestQuery(q);
	return a;
}
