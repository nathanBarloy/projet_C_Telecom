#include "FileToString.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
String_t fileToString(String_t fileName)
{
	String_t s = newString();
	int fd = open(cString(fileName), O_RDONLY);
	if(fd != -1)
	{
		String_t s2 = newStringFromCharStar(" ");
		int r = 0;
		while(1)
		{
			r = read(fd, s2->str, 1);
			if(r != 1)
			{
				break;
			}
			concatString(s, s2);

		}
		close(fd);
		fString(s2);
		return s;
	}
	else
	{
		return 0;
	}
}
