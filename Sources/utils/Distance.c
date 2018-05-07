#include "Distance.h"


double distance_film(BDD bdd,int id1, int id2) {
	double dist=0;
	double coeffActor=3,coeffGenre=5,coeffReal=3,coeffType=1,coeffYear=1;
	JSONArray_t films = BDD_Films(bdd);
	JSONObject_t film1 = JSONArray_get(films, id1);
	JSONObject_t film2 = JSONArray_get(films, id2);
	if (JSONArray_size(JSONObject_getArray(film1,autoString("Directors")))==0 || JSONArray_size(JSONObject_getArray(film1,autoString("Directors")))==0) {
		coeffReal=0;
	}
	if (JSONArray_size(JSONObject_getArray(film1,autoString("Genres")))==0 || JSONArray_size(JSONObject_getArray(film1,autoString("Genres")))==0) {
		coeffGenre=0;
	}
	if (JSONArray_size(JSONObject_getArray(film1,autoString("Actors")))==0 || JSONArray_size(JSONObject_getArray(film1,autoString("Actors")))==0) {
		coeffActor=0;
	}
	double distActor = distance_actor(JSONObject_getArray(film1,autoString("Actors")),JSONObject_getArray(film2,autoString("Actors")));
	double distGenre = distance_genre(JSONObject_getArray(film1,autoString("Genres")),JSONObject_getArray(film2,autoString("Genres")));
	double distReal = distance_real(JSONObject_getArray(film1,autoString("Directors")),JSONObject_getArray(film2,autoString("Directors")));
	double distType = distance_type(JSONObject_stringValueOf(film1,autoString("Type")),JSONObject_stringValueOf(film2,autoString("Type")));
	double distYear = distance_year(JSONObject_intValueOf(film1,autoString("Year")),JSONObject_intValueOf(film2,autoString("Year")));
  printf("%f\n%f\n%f\n%f\n%f\n",distActor,distGenre,distReal,distType,distYear);

	dist = (coeffActor*distActor+coeffGenre*distGenre+coeffReal*distReal+coeffType*distType+coeffYear*distYear ) / (coeffActor+coeffReal+coeffType+coeffYear+coeffGenre);

	printf("la distance entre ");
	printf("%s et ", cString(JSONObject_stringValueOf(film1,autoString("Title"))));
	printf("%s et ", cString(JSONObject_stringValueOf(film2,autoString("Title"))));
	printf("%f\n",dist);


	return dist;
}

double distance_year(int y1,int y2) {
  double dist = 0;
  double alpha = 0.05; //paramètre modifiable <1
  dist = 1.0-exp(-alpha*(double)(abs(y1-y2)));
  return dist;
}

double distance_genre(JSONArray_t l1, JSONArray_t l2) {
	//fait appel à la matrice de distance des genres
  double dist = 0;
	dist = distance_Jacard(l1,l2);
  return dist;
}

double distance_actor(JSONArray_t l1, JSONArray_t l2) {
  double dist = 0;
	dist = distance_Jacard(l1,l2);
  return dist;
}

double distance_real(JSONArray_t l1, JSONArray_t l2) {
  double dist = 0;
	dist = distance_Jacard(l1,l2);
  return dist;
}

double distance_type(String_t t1, String_t t2) {
	//fait appel à la matrice de distance de types
  double dist = 0;

  return dist;
}

double distance_Jacard(JSONArray_t l1, JSONArray_t l2) {
	int intersec = card_intersection(l1,l2);
	int uni = JSONArray_size(l1)+JSONArray_size(l2)-intersec;
	if (uni==0) {
		return 0;
	} else {
		return 1.0-((double)(intersec))/((double)(uni));
	}
}

int card_intersection(JSONArray_t l1, JSONArray_t l2) {
	int compteur=0;
	int i, j;
	for(i = 0;i < JSONArray_size(l1);i++) {
		for(j = 0;j < JSONArray_size(l2);j++) {
			if(JSONString_equals(JSONArray_get(l1,i),JSONArray_get(l2,j))) {
			//if(!strcmp(cString(JSONObject_asString(JSONArray_get(l1,i),0)),cString(JSONObject_asString(JSONArray_get(l2,j),0))) ) {
				printf(/*"i = %d, j = %d: */"%s\n", /*i, j, */cString(JSONObject_asString(JSONArray_get(l1,i),0)));
				printf(/*"i = %d, j = %d: */"%s\n\n", /*i, j, */cString(JSONObject_asString(JSONArray_get(l2,j),0)));
				compteur++;
			}
		}
	}
	printf("%d\n",compteur);
	return compteur;
}
