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

String_t Recognize(Vector_t propositions, String_t word)
{
	size_t c = 0;//compteur pour les mots
	size_t cs = 0;//compteur pour la longueur
	size_t maxLength = 0;//longueur max en commun
	size_t currentSize = 0;
	Vector_t a = newVectorFromVector(propositions);
	String_t s = 0;
	//printf("Loaded.\n");
	while(c < sizeOfVector(a))//1er tri par la taille
	{
		s = (String_t) getFromVector(a, c);
		//printf("%ld: %s - %p\n", c, cString(s), s);
		if(sizeOfString(s) < sizeOfString(word))
		{
			eraseOnVector(a, c);
			//printf("%ld: %s - %p - erased\n", c, cString(s), s);
			continue;
		}
		++c;
	}
	currentSize = sizeOfVector(a);
	c = 0;
	//printf("Après 1er tri: %ld\n", currentSize);
	while(c < sizeOfVector(a))//2e tri par les correspondances
	{
		cs = 0;
		s = (String_t) getFromVector(a, c);
		//printf("%ld: %s - %p\n", c, cString(s), s);
		while(cs < sizeOfString(s) && cs < sizeOfString(word))
		{
			if(cString(s)[cs] == cString(word)[cs])
			{
				if(cs + 1 > maxLength)
				{
					maxLength = cs + 1;
				}
			}
			else
			{
				eraseOnVector(a, c);
				--c;
				break;
			}
			++cs;
		}
		if(cs == sizeOfString(s) && cs == sizeOfString(word))
		{
			//printf("Return a equals: %s - %s - %ld - %ld - %p - %p\n", cString(s), cString(word), c, cs, s, word);
			freeVector(a);
			return s;
		}
		++c;
		if(sizeOfVector(a) < currentSize)
		{
			currentSize = sizeOfVector(a);
			c = 0;
		}
	}
	if(sizeOfVector(a) == 0 || (sizeOfVector(a) == 1 && maxLength < sizeOfString(word)) || sizeOfString(word) == 0)
	{
		printf("[%s]: Aucune correspondance.\n", cString(word));
	}
	else if(sizeOfVector(a) == 1)
	{
		s = (String_t) getFromVector(a, 0);
		freeVector(a);
		//printf("Return a 1.\n");
		return s;
	}
	else
	{
		printf("Impossible de compléter votre demande, plusieurs mots correspondent:\n");
		c = 0;
		while(c < sizeOfVector(a))
		{
			s = (String_t) getFromVector(a, c);
			printf("\t- %s\n", cString(s));
			++c;
		}
	}
	//printf("Return a end.\n");
	freeVector(a);
	return 0;
}
String_t StandardPrompt(Vector_t propositions)
{
	String_t s = ReadInputWithMsg(0);
	lowerString(s);
	return Recognize(propositions, s);
}
void clearTerminal()
{
	printf("\033[2J");
}
