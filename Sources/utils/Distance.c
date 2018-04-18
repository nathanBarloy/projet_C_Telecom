#include <JSONAll.h>
#include <String/AutoString.h>
#include "utils/BDD.h"

/* Pour l'instant c'est la parce que je sais pas trop ou je suis censé le mettre, ni a partir d'où il est appelé
*/

float distance(BDD bdd,int id1, int id2) {
	float dist=0;
	JSONArray_t films = BDD_Films(bdd);
	JSONObject_t film1 = JSONArray_get(films, id1);
	JSONObject_t film2 = JSONArray_get(films, id2);

	printf("la distance entre ");
	printf("%s et ", cString(JSONObject_asString(JSONObject_get(film1,autoString("Title")),0)));
	printf("%s est ", cString(JSONObject_asString(JSONObject_get(film2,autoString("Title")),0)));
	printf("%f\n",dist);


	return dist;
}
