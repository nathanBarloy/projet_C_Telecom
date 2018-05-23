#include "ClientRunner_MainMenu.h"
#include "../utils/ReadInput.h"
#include "ClientRunner.h"
#include "ClientRunnerContinue.h"
#include <time.h>
#include <unistd.h>
#include "ClientRequests.h"

#define eq(sel, menu) equalsString(sel, autoString(menu))
enum ClientRunnerMode ClientRunner_MainMenu(Connexion_t connexion)
{
	clearTerminal();
	//Choices
	Vector_t MainMenu_choices = newVector();
	addToVector(MainMenu_choices, newStringFromCharStar("exit"));
	addToVector(MainMenu_choices, newStringFromCharStar("quitter"));
	addToVector(MainMenu_choices, newStringFromCharStar("voir films"));
	addToVector(MainMenu_choices, newStringFromCharStar("films"));

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
	AutoString_t sel = StandardPrompt(MainMenu_choices);
	enum ClientRunnerMode ret = MAIN_MENU;
	if(sel != 0)
	{
		if(eq(sel, "quitter") || eq(sel, "exit"))
		{
			global_clientRunnerContinue(1,0);
		}
		else if(eq(sel, "voir films") || eq(sel, "films"))
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





enum ClientRunnerMode ClientRunner_ShowFilms(Connexion_t connexion)
{
	clearTerminal();
	//Choices

	/*addToVector(MainMenu_choices, newStringFromCharStar("quitter"));
	addToVector(MainMenu_choices, newStringFromCharStar("voir films"));
	addToVector(MainMenu_choices, newStringFromCharStar("films"));*/

	JSONArray_t films = serverGetFilms(connexion);
	enum ClientRunnerMode ret = MAIN_MENU;
	if(films != 0)
	{
		size_t c = 0, size = JSONArray_size(films), base = 0;
		String_t str = 0;
		JSONObject_t tmp = 0;
		bool selected = false;
		while(base < size)
		{
			clearTerminal();
			c = 0;
			printf("Affichage des films: %lu - %lu / %lu\n", (base + 1), (base + 10 < size ? base + 10 : size - base), size);
			Vector_t MainMenu_choices = newVector();
			addToVector(MainMenu_choices, newStringFromCharStar(""));
			addToVector(MainMenu_choices, newStringFromCharStar("quit"));
			addToVector(MainMenu_choices, newStringFromCharStar("exit"));
			while(c < 10 && base + c < size)
			{
				tmp = JSONArray_get(films, base + c);
				str = newStringFromString(JSONObject_stringValueOf(tmp, autoString("Title")));
				lowerString(str);
				addToVector(MainMenu_choices, str);
				printf("\t- \"%s\"\n", cString(JSONObject_stringValueOf(tmp, autoString("Title"))));
				++c;
			}
			printf("Entrez le nom d'un film (ou une partie de son nom) pour voir le détail.\nAppuyez sur enter pour afficher la suite.\n");
			AutoString_t sel = StandardPrompt(MainMenu_choices);
			if(sel != 0)
			{
				if(eq(sel, ""))
				{
					base += c;
				}
				else if(eq(sel, "quit") || eq(sel, "exit"))
				{
					printf("Retour au menu...\n");
					selected = true;
					break;
				}
				else
				{
					selected = true;
					printf("Affichage du détail du film: %s\n", cString(sel));
					break;
				}
			}
			else
			{
				ReadInputWithMsg(autoString("Appuyez sur enter pour continuer."));
			}
			freeVectorWithPtr(MainMenu_choices, freeVoidString);
		}
		if(!selected)
		{
			clearTerminal();
			printf("Fin des films à afficher.\n");
		}
	}
	else
	{
		clearTerminal();
		printf("Aucun film à afficher.\n");
	}
	ReadInputWithMsg(autoString("Appuyez sur enter pour continuer."));
	return ret;
}
