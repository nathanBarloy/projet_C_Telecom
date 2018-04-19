#ifndef DISTANCE_H
#define DISTANCE_H
#include <JSONALL.h>
#include <math.h>
#include <String/AutoString.h>
#include "utils/BDD.h"

double distance_film(BDD bdd,int id1, int id2);
double distance_year(int y1, int y2);
double distance_genre(char **l1, char **l2);
double distance_actor(char **l1, char **l2);
double distance_real(char **l1, char **l2);
double distance_type(String_t t1, String_t t2);
#endif
