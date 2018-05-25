#ifndef MERGE_SORT_H
#define MERGE_SORT_H
#include <String/AutoString.h>
#include <math.h>
#include <stdlib.h>
#include <JSONAll.h>

Vector_t fromArrayToVector(JSONArray_t list);
JSONArray_t fromVectorToArray(Vector_t v);
Vector_t merge_sort(Vector_t list);
Vector_t merge(Vector_t list1, Vector_t list2);
#endif
