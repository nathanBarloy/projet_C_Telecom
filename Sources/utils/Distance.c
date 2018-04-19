#include "Distance.h"

/* Pour l'instant c'est la parce que je sais pas trop ou je suis censé le mettre, ni a partir d'où il est appelé
*/

double distance_film(BDD bdd,int id1, int id2) {
	double dist=0;
	JSONArray_t films = BDD_Films(bdd);
	JSONObject_t film1 = JSONArray_get(films, id1);
	JSONObject_t film2 = JSONArray_get(films, id2);
	double coeffActor=3,coeffGenre=5,coeffReal=3,coeffType=1,coeffYear=1;
	//double distActor = distance_actor();
	//double distGenre = distance_genre();
	//double distReal = distance_real();
	double distActor = 0;
	double distGenre = 0;
	double distReal = 0;
	double distType = distance_type(JSONObject_stringValueOf(film1,autoString("Type")),JSONObject_stringValueOf(film2,autoString("Type")));
	double distYear = distance_year(JSONObject_intValueOf(film1,autoString("Year")),JSONObject_intValueOf(film2,autoString("Year")));

	dist = (coeffActor*distActor+coeffGenre*distGenre+coeffReal*distReal+coeffType*distType+coeffYear*distYear ) / (coeffActor+coeffReal+coeffType+coeffYear+coeffGenre);

	printf("la distance entre ");
	printf("%s et ", cString(JSONObject_stringValueOf(film1,autoString("Title"))));
	printf("%s et ", cString(JSONObject_stringValueOf(film2,autoString("Title"))));
	printf("%f\n",dist);


	return dist;
}

double distance_year(int y1,int y2) {
  double dist = 0;
/*  double alpha = 0.05;
  dist = 1-exp(-alpha*(double)(abs(y1-y2)));
	problème au niveau de biblioteque math.h, askip il y a un truc a rajouter dans le Makefile mais je sais pas quoi*/
  return dist;
}

double distance_genre(char **l1, char **l2) {
  double dist = 0;

  return dist;
}

double distance_actor(char **l1, char **l2) {
  double dist = 0;

  return dist;
}

double distance_real(char **l1, char **l2) {
  double dist = 0;

  return dist;
}

double distance_type(String_t t1, String_t t2) {
  double dist = 0;

  return dist;
}
