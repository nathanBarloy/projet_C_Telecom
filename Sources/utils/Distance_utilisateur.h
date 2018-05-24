#ifndef DISTANCE_UTILISATEUR_H
#define DISTANCE_UTILISATEUR_H
#include <String/AutoString.h>
#include "BDD.h"
#include <math.h>

double distance_users(BDD bdd, int id1, int id2);
double mean_rates(JSONArray_t history_rates);
double pearson_correlation(JSONArray_t hr1, JSONArray_t hr2);
int get_position(JSONArray_t hr, int id);
JSONArray_t all_distances(BDD bdd, int user_id);
#endif
