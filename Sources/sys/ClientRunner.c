#include "ClientRunner.h"
#include <stdlib.h>
#include <JSONAll.h>
#include <String/String.h>
#include "../utils/ReadInput.h"
#include "../utils/JSONShortcut.h"
#include <string.h>
#include "ClientRunner_MainMenu.h"
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
			mode = MAIN_MENU;
		}
		usleep(10000);
	}
	return 0;
}
int global_clientRunnerContinue(int set, int nvalue)
{
	static int init = 1;
	static pthread_mutex_t m;
	if(init)
	{
		init = 0;
		pthread_mutex_init(&m, 0);
	}
	pthread_mutex_lock(&m);
	static int value = 0;
	if(set)
	{
		value = nvalue;
	}
	int r = value;
	pthread_mutex_unlock(&m);
	return r;
}
void signal_clientRunner(int signal)
{
	if(signal == 2 || signal == 15)
	{
		global_clientRunnerContinue(1, 0);
		printf("\n");
	}
}
void initClient()
{
	global_clientRunnerContinue(1, 1);
}
