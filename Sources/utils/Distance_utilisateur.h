#ifndef DISTANCE_UTILISATEUR_H
#define DISTANCE_UTILISATEUR_H
#include <String/AutoString.h>
#include "BDD.h"

double distance_users(BDD bdd_users, int id1, int id2);
double mean_rates(JSONArray_t history_rates);
double Pearson_correlation(JSONArray_t hr1, JSONArray_t hr2);
int max_length(int a, int b);
double Pearson_correlation(JSONArray_t hr1, JSONArray_t hr2);
bool check_id(JSONArray_t hr, int id);
#endif
