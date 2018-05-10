#include <JSONAll.h>
#include <stdio.h>
#include "../utils/Distance.h"

int main()
{
	JSONArray_t a = JSONArray_new(), b = JSONArray_new();
	JSONArray_add(a, JSONString_new(autoString("Henry Bonjour")));
	JSONArray_add(b, JSONString_new(autoString("Henry Bonjour")));

	JSONArray_add(a, JSONString_new(autoString("LOL")));
	JSONArray_add(b, JSONString_new(autoString("LOL")));

	JSONArray_add(a, JSONString_new(autoString("Henra Bonjour")));
	JSONArray_add(b, JSONString_new(autoString("Henra Bonjour")));

	JSONArray_add(a, JSONString_new(autoString("Harry Potter")));
	JSONArray_add(b, JSONString_new(autoString("Harry Potter")));

	JSONArray_add(a, JSONString_new(autoString("Karry Rotter")));
	JSONArray_add(b, JSONString_new(autoString("Barry Sotter")));
	int r = card_intersection(a, b);
	return 0;
}
