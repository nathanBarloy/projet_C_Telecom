#include "ClientRequests.h"
#include "ClientRequest.h"
void prints(const char* addr_s, String_t message)
{
	JSONObject_t obj = JSONObject_new();
	JSONObject_set(obj, autoString("message"), JSONString_new(newStringFromString(message)));
	//printf("%s\n", cString(JSONObject_asString(obj, 0)));
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(autoString(""), autoString("prints"), obj));
	RequestAnswer a = clientRequest(addr_s, q);
	freeRequestQuery(q);
	freeRequestAnswer(a);
}
