#include "Date.h"
#include <stdlib.h>
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
