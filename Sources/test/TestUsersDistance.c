#include <JSONAll.h>
#include <String/AutoString.h>
#include "../utils/BDD.h"
#include "../utils/Distance_utilisateur.h"

int main() {
	BDD bdd = BDD_load();
	//printf("%s\n",cString(JSONArray_asString(BDD_Users(bdd),0)));
	//JSONArray_t array_distance = all_distances(bdd,7);
	// double distance = distance_users(bdd, 1, 2);
	//printf("%f\n", distance);
	JSONArray_t rates_estim = rates_estimations(bdd, 7);
	printf("%s\n",cString(JSONArray_asString(rates_estim, 0)));
	BDD_free(bdd);
	freeAutoString();
	return 0;
}
