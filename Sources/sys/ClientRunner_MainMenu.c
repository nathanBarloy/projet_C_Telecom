#include "ClientRunner_MainMenu.h"
enum ClientRunnerMode ClientRunner_MainMenu(Connexion_t connexion)
{
	//Choices
	Vector_t MainMenu_choices = newVector();
	addToVector(MainMenu_choices, newStringFromCharStar("exit"));
	addToVector(MainMenu_choices, newStringFromCharStar("inscription"));
	addToVector(MainMenu_choices, newStringFromCharStar("connexion"));
	addToVector(MainMenu_choices, newStringFromCharStar("voir films"));
	addToVector(MainMenu_choices, newStringFromCharStar("voir profil"));
	addToVector(MainMenu_choices, newStringFromCharStar("mes recommandations"));

	//Display
	printf("Bienvenue sur le menu principal, ");
	if(connexion->user != 0)
	{
		printf("%s\n", cStringValueOf(connexion->user, "Login"));
	}
	else
	{
		printf("vous n'êtes pas connecté.\n");
	}
	freeVectorWithPtr(MainMenu_choices, freeVoidString);
	return MAIN_MENU;
}
