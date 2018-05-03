#include "Replace.h"
#include <stdlib.h>
void replace(char* str, char oc, char nc)
{
	size_t c = 0;
	while(str[c] != 0)
	{
		if(str[c] == oc)
		{
			str[c] = nc;
		}
		++c;
	}
}
