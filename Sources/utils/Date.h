#ifndef DATE_H
#define DATE_H
#include <String/AutoString.h>
#include <JSONAll.h>
struct Date
{
	int day, month, year;
};
typedef struct Date* Date_t;

Date_t newDate();
Date_t newDateFull(int day, int month, int year);
Date_t freeDate(Date_t d);
AutoString_t dateToAutoString(Date_t d);
JSONObject_t dateToJSON(Date_t d);
Date_t dateFromJSON(JSONObject_t j);
#endif
