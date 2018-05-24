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
	String_t sel = StandardPrompt(MainMenu_choices);
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
		size_t decal = 0;
		while(base < size)
		{
			clearTerminal();
			c = 0;
			printf("Affichage des films: %lu - %lu / %lu\n", (base + 1), (base + 10 < size ? base + 10 : size - base), size);
			Vector_t MainMenu_choices = newVector();
			addToVector(MainMenu_choices, newStringFromCharStar(""));
			addToVector(MainMenu_choices, newStringFromCharStar("quit"));
			addToVector(MainMenu_choices, newStringFromCharStar("exit"));
			decal = sizeOfVector(MainMenu_choices);
			while(c < 10 && base + c < size)
			{
				tmp = JSONArray_get(films, base + c);
				str = newStringFromString(JSONObject_stringValueOf(tmp, autoString("Title")));
				lowerString(str);
				addToVector(MainMenu_choices, str);
				printf("\t- \"%s\"\n", cString(JSONObject_stringValueOf(tmp, autoString("Title"))));
				++c;
			}
			printf("Entrez le nom d'un film (ou une partie de son nom) pour voir le détail.\nAppuyez sur enter pour afficher la suite, \"quit\" / \"exit\" pour quitter.\n");
			String_t sel = StandardPrompt(MainMenu_choices);
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
					size_t cc = 0, ssize = sizeOfVector(MainMenu_choices);
					int id = -1;
					while(cc < ssize)
					{
						if(sel == (String_t) getFromVector(MainMenu_choices, cc))
						{
							tmp = JSONArray_get(films, (cc - decal) + base);
							//printf("CC: %lu, pos: %lu\n", cc, (cc - decal) + base);
							id = JSONObject_intValueOf(tmp, autoString("Id"));
							break;
						}
						++cc;
					}
					if(id > 0)
					{
						printf("Affichage du détail du film: %d - %s\n", id, cString(sel));
						ClientRunner_showFilm(connexion, id);
					}
					else
					{
						printf("Erreur interne: Le film demandé n'a pas été retrouvé.\n");
					}
					//break;
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
			ReadInputWithMsg(autoString("Appuyez sur enter pour continuer."));
		}
		JSONObject_delete(films);
	}
	else
	{
		clearTerminal();
		printf("Aucun film à afficher.\n");
		ReadInputWithMsg(autoString("Appuyez sur enter pour continuer."));
	}
	return ret;
}

void ClientRunner_showFilm(Connexion_t connexion, int id)
{
	JSONObject_t film = serverGetFilmById(connexion, id);
	if(film != 0)
	{
		clearTerminal();
		printf("[ %s (%s) ]\n\n", cStringValueOf(film, "Title"), cStringValueOf(film, "Year"));
		printf("Synopsis:\n%s\n\n", cStringValueOf(film, "Description"));
		printf("Genres:\n");
		JSONArray_t genres = JSONObject_get(film, AS("Genres"));
		size_t c = 0, size = JSONArray_size(genres);
		while(c < size)
		{
			printf("\t- %s\n", cString(JSONArray_stringValue(genres, c)));
			++c;
		}
		printf("\n");
		printf("Réalisateur(s):\n");
		JSONArray_t directors = JSONObject_get(film, AS("Directors"));
		c = 0;
		size = JSONArray_size(directors);
		while(c < size)
		{
			printf("\t- %s\n", cString(JSONArray_stringValue(directors, c)));
			++c;
		}
		printf("\n");
		printf("Acteur(s):\n");
		JSONArray_t actors = JSONObject_get(film, AS("Actors"));
		c = 0;
		size = JSONArray_size(actors);
		while(c < size)
		{
			printf("\t- %s\n", cString(JSONArray_stringValue(actors, c)));
			++c;
		}
		printf("\n");
		printf("Bande annonce: http://www.youtube.com/watch?v=%s\n", cStringValueOf(film, "Url"));
		char *buf = getcwd(0, 0);
		printf("Cover: file://%s/web/%s\n", buf, cStringValueOf(film, "Cover"));
		free(buf);
		printf("\n\nRecommandés si vous aimez ce film:\n");
		JSONArray_t reco = serverGetFilmRecommendation(connexion, id);
		Vector_t MainMenu_choices = newVector();
		addToVector(MainMenu_choices, newStringFromCharStar(""));
		if(reco != 0)
		{
			c = 1;
			size = JSONArray_size(reco);
			JSONObject_t tmp = 0;
			String_t str = 0;
			while(c < size && c < 11)
			{
				tmp = JSONArray_get(reco, c);
				printf("\t- %s ( %s )\n", cStringValueOf(tmp, "Title"), cStringValueOf(tmp, "Year"));
				str = newStringFromString(JSONObject_stringValueOf(tmp, AS("Title")));
				lowerString(str);
				addToVector(MainMenu_choices, str);
				++c;
			}
		}
		else
		{
			printf("Echec d'obtention des recommendations.\n");
		}
		JSONObject_delete(film);
		printf("Entrez le nom d'un film pour accéder a sa fiche (ou début du nom), enter pour quitter.\n");
		String_t sel = StandardPrompt(MainMenu_choices);
		if(sel != 0)
		{
			if(eq(sel, ""))
			{

			}
			else if(reco != 0)
			{
				c = 1;
				size = sizeOfVector(MainMenu_choices);
				JSONObject_t tmp = 0;
				int nid = 0;
				bool found = false;
				while(c < size)
				{
					if(sel == (String_t) getFromVector(MainMenu_choices, c))
					{
						found = true;
						tmp = JSONArray_get(reco, c);
						nid = JSONObject_intValueOf(tmp, AS("Id"));
						printf("ID: %d\n", nid);
						JSONArray_delete(reco);
						freeVectorWithPtr(MainMenu_choices, freeVoidString);
						ClientRunner_showFilm(connexion, nid);
						break;
					}
					++c;
				}
				if(!found)
				{
					JSONArray_delete(reco);
					freeVectorWithPtr(MainMenu_choices, freeVoidString);
					printf("Film introuvable (erreur interne).\n");
				}
			}
			else
			{
				JSONArray_delete(reco);
				freeVectorWithPtr(MainMenu_choices, freeVoidString);
				printf("Bug trouvé ! (erreur interne).\n");
			}
		}
		else
		{
			ReadInputWithMsg(autoString("Appuyez sur enter pour continuer."));
			freeVectorWithPtr(MainMenu_choices, freeVoidString);
			JSONArray_delete(reco);
			ClientRunner_showFilm(connexion, id);
		}
	}
	else
	{
		printf("Film introuvable.\n");
	}
}
