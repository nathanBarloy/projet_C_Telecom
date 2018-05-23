#include <JSONAll.h>
#include <String/AutoString.h>
#include "../utils/BDD.h"
#include "../utils/Distance_utilisateur.h"

int main() {
  BDD bdd = BDD_load();
  JSONArray_t array_distance = all_distances(bdd,0);
  BDD_free(bdd);
  int i;
  for(i=0 ; i<JSONArray_size(array_distance) ; i++)
  {
    printf("Id : %d\n", JSONObject_intValueOf(JSONArray_get(array_distance, i), autoString("Id")));
    printf("Similarité : %f\n", JSONObject_doubleValueOf(JSONArray_get(array_distance, i), autoString("Sim")));
  }
  printf("%s\n",cString(JSONArray_asString(array_distance,0)));
	freeAutoString();
  printf("FIN\n");
  return 0;
}
