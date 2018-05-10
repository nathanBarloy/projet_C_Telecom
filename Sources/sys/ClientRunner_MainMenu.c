#include "ClientRunner_MainMenu.h"
#include "../utils/ReadInput.h"
#include "ClientRunner.h"
#include "ClientRunnerContinue.h"
#include <time.h>
#include <unistd.h>

#define eq(sel, menu) equalsString(sel, autoString(menu))
enum ClientRunnerMode ClientRunner_MainMenu(Connexion_t connexion)
{
	clearTerminal();
	//Choices
	Vector_t MainMenu_choices = newVector();
	addToVector(MainMenu_choices, newStringFromCharStar("exit"));
	addToVector(MainMenu_choices, newStringFromCharStar("quitter"));
	addToVector(MainMenu_choices, newStringFromCharStar("voir films"));

	//Display
	printf("Bienvenue sur le menu principal, ");
	if(connexion->user != 0)
	{
		printf("%s\n", cStringValueOf(connexion->user, "Login"));
		addToVector(MainMenu_choices, newStringFromCharStar("mes recommandations"));
		addToVector(MainMenu_choices, newStringFromCharStar("voir profil"));
		addToVector(MainMenu_choices, newStringFromCharStar("deconnexion"));
	}
	else
	{
		printf("vous n'êtes pas connecté.\n");
		addToVector(MainMenu_choices, newStringFromCharStar("inscription"));
		addToVector(MainMenu_choices, newStringFromCharStar("connexion"));
	}
	printf("\n");
	printf("Que souhaitez-vous faire?\n");
	if(connexion->user != 0)
	{
		printf("- Deconnexion\n");
		printf("- Voir profil\n");
		printf("- Mes recommandations\n");
	}
	else
	{
		printf("- Connexion\n");
		printf("- Inscription\n");
	}
	printf("- Voir films\n");
	printf("- Quitter\n");

	//Selection
	String_t sel = StandardPrompt(MainMenu_choices);
	enum ClientRunnerMode ret = MAIN_MENU;
	if(sel != 0)
	{
		if(eq(sel, "quitter") || eq(sel, "exit"))
		{
			global_clientRunnerContinue(1,0);
		}
		else if(eq(sel, "voir films"))
		{
			ret = SHOW_FILM;
		}
		else if(eq(sel, "inscription"))
		{
			ret = REGISTER_USER;
		}
		else if(eq(sel, "connexion"))
		{
			ret = CONNECT_USER;
		}
		else if(eq(sel, "mes recommandations"))
		{
			ret = SHOW_RECOMMENDATIONS;
		}
		else if(eq(sel, "mon profil"))
		{
			ret = SHOW_USER_PROFILE;
		}
		else if(eq(sel, "deconnexion"))
		{
			ret = DISCONNECT_USER;
		}
		else
		{
			printf("Une erreur interne est survenue.\nCe choix n'est pas défini correctement.\n");
			sleep(3);
		}
	}
	else
	{
		sleep(1);
	}
	freeVectorWithPtr(MainMenu_choices, freeVoidString);
	return ret;
}
