#include "RequestTypes.h"
//Construction/destruction
RequestAnswer newRequestAnswer(int code, JSONObject_t obj)
{
	RequestAnswer r = (RequestAnswer) malloc(sizeof(struct RequestAnswer));
	r->code = code;
	r->obj = obj;
	return r;
}
RequestAnswer freeRequestAnswer(RequestAnswer r)
{
	if(r->obj != 0)
	{
		r->obj = JSONObject_delete(r->obj);
	}
	free(r);
	return 0;
}
RequestQuery newRequestQuery(int id, JSONObject_t obj)
{
	RequestQuery r = (RequestQuery) malloc(sizeof(struct RequestQuery));
	r->id = id;
	r->obj = obj;
	return r;
}
RequestQuery freeRequestQuery(RequestQuery r)
{
	if(r->obj != 0)
	{
		r->obj = JSONObject_delete(r->obj);
	}
	free(r);
	return 0;
}
JSONObject_t newJSONRequestQuery(String_t sid, String_t type, JSONObject_t data)
{
	JSONObject_t obj = JSONObject_new();
	JSONObject_set(obj, autoString("Sid"), JSONString_new(sid));
	JSONObject_set(obj, autoString("Type"), JSONString_new(type));
	JSONObject_set(obj, autoString("Query"), data);
	return obj;
}
