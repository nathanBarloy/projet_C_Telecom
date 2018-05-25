#include "RandomReco.h"

JSONArray_t RandomReco(BDD bdd)
{
	JSONArray_t r = JSONArray_new(), cp = JSONArray_getCopy(BDD_Films(bdd));
	while(JSONArray_size(cp) > 0)
	{
		JSONArray_add(r, JSONArray_get(cp, rand() % JSONArray_size(cp)));
	}
	JSONArray_delete(cp);
	return r;
}
