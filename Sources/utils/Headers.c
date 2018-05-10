#include "Headers.h"
Header_t newHeader()
{
	return newHeaderFull("", "");
}
Header_t newHeaderFull(char* name, char* value)
{
	Header_t h = (Header_t) malloc(sizeof(struct Header));
	h->name = newStringFromCharStar(name);
	h->value = newStringFromCharStar(value);
	return h;
}
Header_t freeHeader(Header_t header)
{
	if(header->name != 0)
	{
		fString(header->name);
	}
	if(header->value != 0)
	{
		fString(header->value);
	}
	free(header);
	return 0;
}
void freeHeaderPtr(void* h)
{
	freeHeader((Header_t) h);
}
