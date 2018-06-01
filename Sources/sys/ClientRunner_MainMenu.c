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
	addToVector(MainMenu_choices, newStringFromCharStar("tendances"));
	addToVector(MainMenu_choices, newStringFromCharStar("au hasard"));
	addToVector(MainMenu_choices, newStringFromCharStar("hasard"));

	//Display
	printf("Bienvenue sur le menu principal, ");
	if(connexion->user != 0)
	{
		printf("%s\n", cStringValueOf(connexion->user, "Login"));
		addToVector(MainMenu_choices, newStringFromCharStar("mes recommandations"));
		addToVector(MainMenu_choices, newStringFromCharStar("recommandations"));
		addToVector(MainMenu_choices, newStringFromCharStar("mes films"));
		//addToVector(MainMenu_choices, newStringFromCharStar("voir profil"));
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
		//printf("- Voir profil\n");
		printf("- Mes recommandations\n");
		printf("- Mes films\n");
	}
	else
	{
		printf("- Connexion\n");
		printf("- Inscription\n");
	}
	printf("- Tendances\n");
	printf("- Voir films\n");
	printf("- Au hasard\n");
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
		else if(eq(sel, "mes recommandations") || eq(sel, "recommandations"))
		{
			ret = SHOW_RECOMMENDATIONS;
		}
		else if(eq(sel, "au hasard") || eq(sel, "hasard"))
		{
			ret = SHOW_RANDOM;
		}
		/*else if(eq(sel, "mon profil"))
		{
			ret = SHOW_USER_PROFILE;
		}*/
		else if(eq(sel, "deconnexion"))
		{
			ret = DISCONNECT_USER;
		}
		else if(eq(sel, "mes films"))
		{
			ret = SHOW_MY_FILMS;
		}
		else if(eq(sel, "tendances"))
		{
			ret = SHOW_TRENDS;
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
					freeVectorWithPtr(MainMenu_choices, freeVoidString);
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
		String_t rate = UTF8Rate(JSONObject_intValueOf(film, AS("Rate")));
		printf("[ %s (%s) - %s ]\n\n", cStringValueOf(film, "Title"), cStringValueOf(film, "Year"), cString(rate));
		fString(rate);
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
		String_t id_s = newStringFromCharStar("Id"), rate_s = newStringFromCharStar("Rate");
		if(connexion->user != 0)
		{
			JSONArray_t arr = serverGetUserRates(connexion);
			JSONObject_t rate = 0;
			if(arr != 0)
			{
				// printf("%s\n", cString(JSONObject_asString(arr, 0)));
				size_t c = 0, size = JSONArray_size(arr);
				JSONObject_t ru = 0;
				while(c < size)
				{
					ru = JSONArray_get(arr, c);
					if(JSONObject_intValueOf(ru, id_s) == id)
					{
						rate = ru;
						break;
					}
					++c;
				}
				JSONObject_delete(arr);
			}
			String_t rt = 0;
			if(rate != 0)
			{
				// printf("Note trouvée.\n");
				rt = UTF8Rate(JSONObject_intValueOf(rate, rate_s));
			}
			else
			{
				// printf("Non noté.\n");
				rt = UTF8Rate(0);
			}
			printf("Votre note: %s\n", cString(rt));
			fString(rt);
		}
		fString(id_s);
		fString(rate);
		printf("\n\nRecommandés si vous aimez ce film:\n");
		JSONArray_t reco = serverGetFilmRecommendation(connexion, id);
		Vector_t MainMenu_choices = newVector();
		addToVector(MainMenu_choices, newStringFromCharStar(""));
		addToVector(MainMenu_choices, newStringFromCharStar("exporter"));
		if(connexion->user != 0)
		{
			addToVector(MainMenu_choices, newStringFromCharStar("noter"));
		}
		int decal = sizeOfVector(MainMenu_choices);
		JSONArray_t export = JSONArray_new();
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
				JSONArray_add(export, JSONObject_getCopy(tmp));
				++c;
			}
		}
		else
		{
			printf("Echec d'obtention des recommandations.\n");
		}
		JSONObject_delete(film);
		printf("Entrez le nom d'un film pour accéder à sa fiche (ou début du nom).\n- \"exporter\" pour sauvegarder ces résultats.\n");
		if(connexion->user != 0)
		{
			printf("- \"noter\" pour attribuer une note.\n");
		}
		printf("-  enter pour quitter.\n");
		String_t sel = StandardPrompt(MainMenu_choices);
		if(sel != 0)
		{
			if(eq(sel, ""))
			{

			}
			else if(eq(sel, "noter") && connexion->user != 0)
			{
				ClientRunner_noter(connexion, id);
				ClientRunner_showFilm(connexion, id);
			}
			else if(eq(sel, "exporter"))
			{
				ClientRunner_export(export);
				ClientRunner_showFilm(connexion, id);
			}
			else if(reco != 0)
			{
				c = decal;
				size = sizeOfVector(MainMenu_choices);
				JSONObject_t tmp = 0;
				int nid = 0;
				bool found = false;
				printf("SEL: %s\n", cString(sel));
				while(c < size)
				{
					if(sel == (String_t) getFromVector(MainMenu_choices, c))
					{
						found = true;
						tmp = JSONArray_get(reco, c - (decal - 1 ));
						nid = JSONObject_intValueOf(tmp, AS("Id"));
						#ifdef DEBUG
						printf("ID: %d\n", nid);
						#endif
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
		JSONObject_delete(export);
		JSONObject_delete(reco);
		freeVectorWithPtr(MainMenu_choices, freeVoidString);
	}
	else
	{
		printf("Film introuvable.\n");
	}
}
void ClientRunner_export(JSONObject_t e)
{
	printf("Choisissez un nom pour le fichier à exporter, l'extension .json est ajoutée automatiquement. (ou laissez vide pour annuler)\n");
	AutoString_t name = ReadInputWithMsg(AS("Nom pour le fichier à exporter: "));
	if(sizeOfString(name) > 0)
	{
		concatString(name, autoString(".json"));
		JSONParser_saveFileString(e, name);
		printf("Export terminé: %s.\n", cString(name));
	}
	else
	{
		printf("Export annulé.\n");
	}
	ReadInputWithMsg(AS("Appuyez sur enter pour continuer."));
}

void ClientRunner_noter(Connexion_t connexion, int id)
{
	String_t rd = ReadInputWithMsg(AS("Attribuez une note entre 1 et 5 à ce film: "));
	int n = atoi(cString(rd));
	if(n > 0 && n <= 5)
	{
		RequestAnswer a = serverSetFilmRateOfUser(connexion, id, n);
		if(a != 0)
		{
			if(a->code == 0)
			{
				printf("Le film à bien été noté.\n");
			}
			else
			{
				printf("Une erreur est survenue lors de l'attribution de la note au film.\n");
			}
		}
		else
		{
			printf("Impossible de contacter le serveur pour noter le film.\n");
		}
		freeRequestAnswer(a);
	}
	else
	{
		printf("Note invalide.\n");
	}
	ReadInputWithMsg(AS("Appuyez sur enter pour continuer."));
}






enum ClientRunnerMode ClientRunner_ShowMyFilms(Connexion_t connexion)
{
	clearTerminal();
	//Choices

	/*addToVector(MainMenu_choices, newStringFromCharStar("quitter"));
	addToVector(MainMenu_choices, newStringFromCharStar("voir films"));
	addToVector(MainMenu_choices, newStringFromCharStar("films"));*/

	JSONArray_t films2 = serverGetFilms(connexion);
	JSONArray_t ufilms = serverGetUserRates(connexion);
	enum ClientRunnerMode ret = MAIN_MENU;
	if(films2 != 0 && ufilms != 0)
	{
		JSONArray_t films = JSONArray_new();
		{
			String_t id_s = newStringFromCharStar("Id");
			size_t c = 0, size = JSONArray_size(films2), c2 = 0, size2 = JSONArray_size(ufilms);
			JSONObject_t tmp = 0, tmp2 = 0;
			while(c < size)
			{
				tmp = JSONArray_get(films2, c);
				c2 = 0;
				while(c2 < size2)
				{
					tmp2 = JSONArray_get(ufilms, c2);
					if(JSONObject_intValueOf(tmp, id_s) == JSONObject_intValueOf(tmp2, id_s))
					{
						JSONArray_add(films, tmp);
					}
					++c2;
				}
				++c;
			}
			fString(id_s);
		}
		size_t c = 0, size = JSONArray_size(films), base = 0;
		String_t str = 0;
		JSONObject_t tmp = 0;
		bool selected = false;
		size_t decal = 0;
		while(base < size)
		{
			clearTerminal();
			c = 0;
			printf("Affichage de vos films: %lu - %lu / %lu\n", (base + 1), (base + 10 < size ? base + 10 : size - base), size);
			Vector_t MainMenu_choices = newVector();
			addToVector(MainMenu_choices, newStringFromCharStar(""));
			addToVector(MainMenu_choices, newStringFromCharStar("quit"));
			addToVector(MainMenu_choices, newStringFromCharStar("exit"));
			addToVector(MainMenu_choices, newStringFromCharStar("exporter"));
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
			printf("Entrez le nom d'un film (ou une partie de son nom) pour voir le détail.\n\n\"exporter\" pour exporter les résultats.\nAppuyez sur enter pour afficher la suite, \"quit\" / \"exit\" pour quitter.\n");
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
					freeVectorWithPtr(MainMenu_choices, freeVoidString);
					break;
				}
				else if(eq(sel, "exporter"))
				{
					ClientRunner_export(films);
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
		JSONObject_delete(ufilms);
		JSONObject_delete(films2);
	}
	else
	{
		clearTerminal();
		printf("Aucun film à afficher.\n");
		ReadInputWithMsg(autoString("Appuyez sur enter pour continuer."));
	}
	return ret;
}
enum ClientRunnerMode ClientRunner_ShowTrends(Connexion_t connexion)
{
	clearTerminal();
	//Choices

	/*addToVector(MainMenu_choices, newStringFromCharStar("quitter"));
	addToVector(MainMenu_choices, newStringFromCharStar("voir films"));
	addToVector(MainMenu_choices, newStringFromCharStar("films"));*/

	JSONArray_t films = serverGetFilmOrderedByRank(connexion);
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
			printf("Affichage des tendances: %lu - %lu / %lu\n", (base + 1), (base + 10 < size ? base + 10 : size - base), size);
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
					freeVectorWithPtr(MainMenu_choices, freeVoidString);
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
enum ClientRunnerMode ClientRunner_ShowRandom(Connexion_t connexion)
{
	clearTerminal();
	//Choices

	/*addToVector(MainMenu_choices, newStringFromCharStar("quitter"));
	addToVector(MainMenu_choices, newStringFromCharStar("voir films"));
	addToVector(MainMenu_choices, newStringFromCharStar("films"));*/

	JSONArray_t films = serverGetRandRecommendation(connexion);
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
			printf("Affichage des films au hasard: %lu - %lu / %lu\n", (base + 1), (base + 10 < size ? base + 10 : size - base), size);
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
					freeVectorWithPtr(MainMenu_choices, freeVoidString);
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

enum ClientRunnerMode ClientRunner_ShowRecommendations(Connexion_t connexion)
{
	clearTerminal();
	//Choices

	/*addToVector(MainMenu_choices, newStringFromCharStar("quitter"));
	addToVector(MainMenu_choices, newStringFromCharStar("voir films"));
	addToVector(MainMenu_choices, newStringFromCharStar("films"));*/

	JSONArray_t films = serverGetCollaborativeRecommnendation(connexion);
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
			printf("Affichage des recommandations personnalisées: %lu - %lu / %lu\n", (base + 1), (base + 10 < size ? base + 10 : size - base), size);
			Vector_t MainMenu_choices = newVector();
			addToVector(MainMenu_choices, newStringFromCharStar(""));
			addToVector(MainMenu_choices, newStringFromCharStar("quit"));
			addToVector(MainMenu_choices, newStringFromCharStar("exit"));
			addToVector(MainMenu_choices, newStringFromCharStar("exporter"));
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
			printf("Entrez le nom d'un film (ou une partie de son nom) pour voir le détail.\nAppuyez sur enter pour afficher la suite, \"exporter\" pour exporter les recommandations, \"quit\" / \"exit\" pour quitter.\n");
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
					freeVectorWithPtr(MainMenu_choices, freeVoidString);
					break;
				}
				else if(eq(sel, "exporter"))
				{
					ClientRunner_export(films);
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
