#ifndef DISTANCE_H
#define DISTANCE_H
//#include <JSONALL.h>
#include <math.h>
#include <string.h>
#include <String/AutoString.h>
#include "BDD.h"

double distance_film(BDD bdd,int id1, int id2);
double distance_year(int y1, int y2);
double distance_genre(JSONArray_t l1, JSONArray_t l2);
double distance_actor(JSONArray_t l1, JSONArray_t l2);
double distance_real(JSONArray_t l1, JSONArray_t l2);
double distance_type(String_t t1, String_t t2);
double distance_Jacard(JSONArray_t l1, JSONArray_t l2);
int card_intersection(JSONArray_t l1, JSONArray_t l2);
#endif
