#ifndef HEADERS_H
#define HEADERS_H
#include <String/String.h>
struct Header
{
	String_t name, value;
};
typedef struct Header* Header_t;

Header_t newHeader();
Header_t newHeaderFull(char* name, char* value);
Header_t freeHeader(Header_t header);
void freeHeaderPtr(void* header);
#endif
