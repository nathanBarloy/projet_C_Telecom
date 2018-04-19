#include "../utils/ReadInput.h"
#include <stdio.h>

int main()
{
	Vector_t v = newVector();
	addToVector(v, newStringFromCharStar("exit"));
	addToVector(v, newStringFromCharStar("call"));
	addToVector(v, newStringFromCharStar("upgrade"));
	addToVector(v, newStringFromCharStar("apt-get"));
	addToVector(v, newStringFromCharStar("echo"));
	addToVector(v, newStringFromCharStar("rm"));
	addToVector(v, newStringFromCharStar("register"));
	addToVector(v, newStringFromCharStar("login"));
	addToVector(v, newStringFromCharStar("subscribe"));
	addToVector(v, newStringFromCharStar("sudo"));
	addToVector(v, newStringFromCharStar("hello"));
	String_t str = ReadInputWithMsg(autoString("Entrez une proposition: "));
	String_t reco = Recognize(v, str);
	if(reco == 0)
	{
		printf("Unable to Recognize.\n");
	}
	else
	{
		printf("Recognized: %s\n", cString(reco));
	}
	freeVectorWithPtr(v, freeVoidString);
	freeAutoString();
	return 0;
}
