#include "ReadInput.h"
String_t ReadInput()
{
	String_t s = newString();
	char b[2];
	b[1] = 0;
	int r = 0;
	while(1)
	{
		r = read(0, b, 1);
		if(r != 1 || b[0] == '\n')
		{
			break;
		}
		else
		{
			concatString(s, autoString(b));
		}
	}
	return autoStringAllocated(s);
}

String_t ReadInputWithMsg(String_t dsp)
{
	if(dsp == 0)
	{
		dsp = autoString(">>> ");
	}
	write(1, dsp->str, sizeOfString(dsp));
	return ReadInput();
}
