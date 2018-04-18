#include <JSONAll.h>
#include <String/AutoString.h>
#include "utils/BDD.h"
#include <math.h>

/* Pour l'instant c'est la parce que je sais pas trop ou je suis censé le mettre, ni a partir d'où il est appelé
*/

float distance(BDD bdd,int id1, int id2) {
	float dist=0;
	JSONArray_t films = BDD_Films(bdd);
	JSONObject_t film1 = JSONArray_get(films, id1);
	JSONObject_t film2 = JSONArray_get(films, id2);
	float coeffActor=3,coeffGenre=5,coeffReal=3,coeffType=1,coeffYear=1;
	//float distActor = distance_actor();
	//float distGenre = distance_genre();
	//float distReal = distance_real();
	float distActor = 0;
	float distGenre = 0;
	float distReal = 0;
	float distType = distance_type(JSONObject_stringValueOf(film1,autoString("Type")),JSONObject_stringValueOf(film2,autoString("Type")));
	float distYear = distance_year(JSONObject_intValueOf(film1,autoString("Year")),JSONObject_intValueOf(film2,autoString("Year")));

	dist = (coeffActor*distActor+coeffGenre*distGenre+coeffReal*distReal+coeffType*distType+coeffYear*distYear ) / (coeffActor+coeffReal+coeffType+coeffYear+coeffGenre);

	printf("la distance entre ");
	printf("%s et ", cString(JSONObject_stringValueOf(film1,autoString("Title"))));
	printf("%s et ", cString(JSONObject_stringValueOf(film2,autoString("Title"))));
	printf("%f\n",dist);


	return dist;
}

float distance_year(int y1,int y2) {
  float dist = 0;
/*  float alpha = 0.05;
  dist = 1-exp(-alpha*(float)(abs(y1-y2))); */
  return dist;
}

float distance_genre(char **l1, char **l2) {
  float dist = 0;

  return dist;
}

float distance_actor(char **l1, char **l2) {
  float dist = 0;

  return dist;
}

float distance_real(char **l1, char **l2) {
  float dist = 0;

  return dist;
}

float distance_type(String_t t1, String_t t2) {
  float dist = 0;

  return dist;
}
