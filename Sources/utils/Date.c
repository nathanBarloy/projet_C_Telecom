#include "Date.h"
#include <stdlib.h>
#include "JSONShortcut.h"
#include "JSONCheck.h"
Date_t newDate()
{
	return newDateFull(0, 0, 0);
}
Date_t newDateFull(int day, int month, int year)
{
	Date_t d = (Date_t) malloc(sizeof(struct Date));
	d->day = day;
	d->month = month;
	d->year = year;
	return d;
}
Date_t freeDate(Date_t d)
{
	free(d);
	return 0;
}
AutoString_t dateToAutoString(Date_t d)
{
	char buf[100];
	sprintf(buf, "%2d/%2d/%4d", d->day, d->month, d->year);
	return autoString(buf);
}
JSONObject_t dateToJSON(Date_t d)
{
	JSONObject_t o = JSONObject_new();
	JSONObject_set(o, AS("Day"), JSONInt_new(d->day));
	JSONObject_set(o, AS("Month"), JSONInt_new(d->month));
	JSONObject_set(o, AS("Year"), JSONInt_new(d->year));
	return o;
}
Date_t dateFromJSON(JSONObject_t j)
{
	if(JSON_checkDate(j))
	{
		return newDateFull(JSONObject_intValueOf(j, AS("Day")), JSONObject_intValueOf(j, AS("Month")), JSONObject_intValueOf(j, AS("Year")));
	}
	return 0;
}
