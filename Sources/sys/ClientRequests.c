#include "ClientRequests.h"
#include "ClientRequest.h"
RequestAnswer prints(const char* addr_s, String_t message)
{
	RequestQuery q = newRequestQuery(0, newJSONRequestQuery(autoString(""), autoString("prints"), newStringFromString(message)));
	RequestAnswer a = clientRequest(addr_s, q);
	freeRequestQuery(q);
	return a;
}
