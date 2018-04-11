#include <cjson/JSONAll.h>
#include <String/AutoString.h>
int main()
{
	JSONObject_t bdd = JSONObject_new();
	JSONObject_t films = JSONParser_parseFile("data/bd.json");
	JSONObject_set(bdd, autoString("films"), films);
	JSONArray_t users = JSONArray_new();
	JSONObject_set(bdd, autoString("users"), users);
	printf("%s\n", cString(JSONObject_asString(bdd, 0)));
	bdd = JSONObject_delete(bdd);
	freeAutoString();
	return 0;
}
