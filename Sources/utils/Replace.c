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
int getFirstChar(String_t str, char c)
{
	int pos = 0, size = sizeOfString(str);
	while(pos < size)
	{
		if(str->str[pos] == c)
		{
			return pos;
		}
		++pos;
	}
	return -1;
}
void transformValue(String_t str)
{
	size_t c = 0, size = sizeOfString(str);
	String_t r = newString(), tmp = newStringFromCharStar(" ");
	String_t code = 0;
	bool hex = false;
	int hexcount = 0;
	while(c < size)
	{
		if(!hex)
		{
			if(str->str[c] == '%')
			{
				hex = true;
				hexcount = 0;
				code = newString();
			}
			else if(str->str[c] == '+')
			{
				tmp->str[0] = ' ';
				concatString(r, tmp);
			}
			else
			{
				tmp->str[0] = str->str[c];
				concatString(r, tmp);
			}
		}
		else
		{
			++hexcount;
			tmp->str[0] = str->str[c];
			concatString(code, tmp);
			if(hexcount == 2)
			{
				tmp->str[0] = (char) strtol(cString(code), 0, 16);
				concatString(r, tmp);
				fString(code);
				hex = false;
			}
		}
		++c;
	}
	//printf("R: %s\n", cString(r));
	setString(str, r);
	fString(r);
}
