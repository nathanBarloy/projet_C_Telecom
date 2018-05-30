#include "ClientRunner.h"
#include "ClientRunnerContinue.h"
#include <stdlib.h>
#include <JSONAll.h>
#include <String/String.h>
#include "../utils/ReadInput.h"
#include "../utils/JSONShortcut.h"
#include <string.h>
#include "ClientRunner_MainMenu.h"
#include "ClientRunner_UserSession.h"
#include <unistd.h>
#include <signal.h>
#include "ClientRequests.h"
int clientRunner(Connexion_t connexion)
{
	//Signaux
	signal(2, signal_clientRunner);
	signal(15, signal_clientRunner);

	//Gestionnaire de fonctions
	enum ClientRunnerMode mode = MAIN_MENU;
	enum ClientRunnerMode(*modeFct[CLIENT_ENUM_SIZE])(Connexion_t);//Tableau contenant les fonctions à lancer.
	memset(modeFct, 0, sizeof(void*) * CLIENT_ENUM_SIZE);
	//Debut des fonctions
	modeFct[MAIN_MENU] = ClientRunner_MainMenu;
	modeFct[CONNECT_USER] = ClientRunner_Login;
	modeFct[REGISTER_USER] = ClientRunner_Register;
	modeFct[DISCONNECT_USER] = ClientRunner_Logout;
	modeFct[SHOW_FILM] = ClientRunner_ShowFilms;
	modeFct[SHOW_MY_FILMS] = ClientRunner_ShowMyFilms;
	modeFct[SHOW_TRENDS] = ClientRunner_ShowTrends;
	modeFct[SHOW_RANDOM] = ClientRunner_ShowRandom;
	modeFct[SHOW_RECOMMENDATIONS] = ClientRunner_ShowRecommendations;
	//Fin des fonctions
	String_t choice = autoString("");
	while(global_clientRunnerContinue(0, 0))
	{
		if(modeFct[mode] != 0)
		{
			mode = modeFct[mode](connexion);//Appel de la fonction correspondante
		}
		else
		{
			printf("Not implemented yet !\nGoing back to MainMenu.\n");
			sleep(1);
			mode = MAIN_MENU;
		}
	}
	RequestAnswer a = Client_Logout(connexion);
	if(a != 0)
	{
		freeRequestAnswer(a);
	}
	return 0;
}
