#include "Distance.h"
#include "BDD.h"
#include <math.h>
double distance_film(BDD bdd,int id1, int id2) {
	double dist=0;
	double distActor=1,distGenre=1,distReal=1,distType=1,distYear=1;
	double coeffActor=3,coeffGenre=5,coeffReal=3,coeffType=1,coeffYear=1;
	JSONObject_t film1 = BDD_getFilmById(bdd, id1);
	JSONObject_t film2 = BDD_getFilmById(bdd, id2);
	if(film1 == 0 || film2 == 0)
	{
		printf("Distance: Invalid id: %d | %d\n", id1, id2);
		return -1;
	}
	JSONObject_t bdGenre = BDD_Genres(bdd);
	//printf("%s\n",cString(JSONObject_asString(bdGenre,0)) );
	String_t directors = newStringFromCharStar("Directors"), genres = newStringFromCharStar("Genres"), actors = newStringFromCharStar("Actors"), type =newStringFromCharStar("Type"), year = newStringFromCharStar("Year");
	if (JSONArray_size(JSONObject_getArray(film1,directors))==0 || JSONArray_size(JSONObject_getArray(film1,directors))==0) {
		coeffReal=0;
	} else {
		distReal = distance_real(JSONObject_getArray(film1,directors),JSONObject_getArray(film2,directors));
	}
	if (JSONArray_size(JSONObject_getArray(film1,genres))==0 || JSONArray_size(JSONObject_getArray(film1,genres))==0) {
		coeffGenre=0;
	} else{
		distGenre = distance_genre(JSONObject_getArray(film1,genres),JSONObject_getArray(film2,genres),bdGenre);
	}
	if (JSONArray_size(JSONObject_getArray(film1,actors))==0 || JSONArray_size(JSONObject_getArray(film1,actors))==0) {
		coeffActor=0;
	} else {
		distActor = distance_actor(JSONObject_getArray(film1,actors),JSONObject_getArray(film2,actors));
	}
	distType = distance_type(JSONObject_stringValueOf(film1,type),JSONObject_stringValueOf(film2,type));
	distYear = distance_year(JSONObject_intValueOf(film1,year),JSONObject_intValueOf(film2,year));
  //printf("%f\n%f\n%f\n%f\n%f\n",distActor,distGenre,distReal,distType,distYear);

	dist = (coeffActor*distActor+coeffGenre*distGenre+coeffReal*distReal+coeffType*distType+coeffYear*distYear ) / (coeffActor+coeffReal+coeffType+coeffYear+coeffGenre);

	/*printf("la distance entre ");
	printf("%s et ", cString(JSONObject_stringValueOf(film1,autoString("Title"))));
	printf("%s et ", cString(JSONObject_stringValueOf(film2,autoString("Title"))));
	printf("%f\n",dist);
	*/
	//printf("%f\n",distGenre);
	fString(directors);
	fString(genres);
	fString(actors);
	fString(type);
	fString(year);
	return dist;
}

double distance_year(int y1,int y2) {
  double dist = 0;
  double alpha = 0.1; //paramètre modifiable <1
  dist = 1.0-exp(-alpha*(double)(abs(y1-y2)));
  return dist;
}

double distance_year2(int y1,int y2) {
	double dist=0;
	double alpha = 0.15;
	dist = atan(alpha*(double)(abs(y1-y2)))*2/3.14159;
	return dist;
}

double distance_genre(JSONArray_t l1, JSONArray_t l2, JSONObject_t bdGenre) {
	//fait appel à la matrice de distance des genres
  double dist = 0;
	//dist = distance_matrice(l1,l2,bdGenre);
	dist = distance_Jacard(l1,l2);
  return dist;
}

double distance_matrice(JSONArray_t l1, JSONArray_t l2, JSONObject_t bdGenre) {
	int i,j,l,c;
	int n=JSONArray_size(l1);
	int m=JSONArray_size(l2);
	double dist=0.;
	String_t matrice = newStringFromCharStar("Matrice"), liste_s = newStringFromCharStar("Liste");
	JSONArray_t matr = JSONObject_getArray(bdGenre,matrice);
	JSONArray_t liste = JSONObject_getArray(bdGenre,liste_s);

	for (i=0;i<n;i++) {
		for (j=0;j<m;j++) {
			l= numero(liste,JSONArray_get(l1,i));
			c= numero(liste,JSONArray_get(l2,j));
			dist+=JSONDouble_get(JSONArray_getDouble(JSONArray_getArray(matr,l),c));
			#ifdef DEBUG
			printf("%d,%d  ",l,c);
			#endif
		}
	}
	#ifdef DEBUG
	printf("\n");
	#endif
	dist/=((double) (n*m));
	fString(matrice);
	fString(liste_s);
	return dist;
}

int numero(JSONArray_t liste, JSONObject_t genre) {
	int compteur=0;
	while (!JSONString_equals(genre,JSONArray_get(liste,compteur))) {
		compteur++;
		printf("%d ",compteur);
	}
	printf("\n");
	return compteur;
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
  double dist = 0;
	if (!equalsString(t1,t2)) {
		dist=1.0;
	}
  return dist;
}

double distance_Jacard(JSONArray_t l1, JSONArray_t l2) {
	int intersec = card_intersection(l1,l2);
	int uni = JSONArray_size(l1)+JSONArray_size(l2)-intersec;
	if (uni==0) {
		return 1.0;
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
				//printf(/*"i = %d, j = %d: */"%s\n", /*i, j, */cString(JSONObject_asString(JSONArray_get(l1,i),0)));
				//printf(/*"i = %d, j = %d: */"%s\n\n", /*i, j, */cString(JSONObject_asString(JSONArray_get(l2,j),0)));
				compteur++;
			}
		}
	}
	//printf("%d\n",compteur);
	return compteur;
}

JSONArray_t liste_recommandation(BDD bdd, int id) {
	JSONArray_t listeFilms = BDD_Films(bdd);
	JSONArray_t triFilms = JSONArray_new();
	int n = JSONArray_size(listeFilms);
	int i = 0;
	double dist = -1.0;
	int *triID=NULL;
	double *triDist=NULL;
	triID = (int*) malloc((n-1)*sizeof(int));
	triDist = (double*) malloc((n-1)*sizeof(double));
	if (triID == NULL || triDist == NULL) {
		printf("Unable to malloc. (liste_recommandation)\n");
		JSONObject_delete(triFilms);
		if(triID != 0)
		{
			free(triID);
		}
		if(triDist != 0)
		{
			free(triDist);
		}
		return 0;
	}

	for (i=0;i<n-1;i++) { //initialisation de la liste des distances à 1
		triDist[i]=1.0;
	}
	JSONObject_t tmp = 0;
	int tmpid = 0;
	String_t id_s = newStringFromCharStar("Id");
	for (i=0;i<n;i++) {
		if (i!=id) {
			tmp = JSONArray_get(listeFilms, i);
			tmpid = JSONObject_intValueOf(tmp, id_s);
			dist = distance_film(bdd, id,tmpid);
			insert_tri(dist,i,triDist,triID,n);
		}
	}
	fString(id_s);
	free(triDist);
	triFilms = tabToVect(bdd, triID,listeFilms,n);
	free(triID);
	return triFilms;
}

JSONArray_t tabToVect(BDD bdd, int *triID,JSONArray_t films,int n) {
	JSONArray_t triFilms = JSONArray_new();
	JSONObject_t film = 0;
	int i=0;
	for (i=0;i<n-1;i++) {
		film = BDD_getFilmById(bdd, triID[i]/* - 1*/);
		if(film != 0)
		{
			JSONArray_add(triFilms,JSONObject_getCopy(film));
		}
	}
	return triFilms;
}

void insert_tri(double dist, int id, double *triDist, int *triID, int n) {
	int k=0;
	while (triDist[k]<dist) {
		k++;
	}
	decale(dist, id, triDist, triID, n, k);
}

void decale(double dist, int id, double *triDist, int *triID, int n, int k) {
	int i;
	for (i=n-2;i>k;i--) {
		triDist[i]=triDist[i-1];
		triID[i]=triID[i-1];
	}
	triDist[k]=dist;
	triID[k]=id+1;
}

JSONArray_t listGenres(BDD bdd) {
	JSONArray_t films = BDD_Films(bdd);
	JSONArray_t list = JSONArray_new();
	int isIn;
	int i, j, k;
	String_t genres = newStringFromCharStar("Genres");
	for (i=0;i<JSONArray_size(films);i++) {
		JSONArray_t genres = JSONObject_getArray(JSONArray_get(films,i),genres);
		for (j=0;j<JSONArray_size(genres);j++) {
			isIn = 0;
			for (k=0;k<JSONArray_size(list);k++) {
				if (JSONString_equals(JSONArray_get(genres,j),JSONArray_get(list,k))) {isIn=1;}
			}
			if (isIn==0) {
				JSONArray_add(list,JSONArray_get(genres,j));
			}
		}
	}
	fString(genres);
	return list;
}
