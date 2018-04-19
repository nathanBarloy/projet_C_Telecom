#include "ClientRunner.h"
#include <stdlib.h>
#include <JSONAll.h>
#include <String/String.h>
#include "../utils/ReadInput.h"
#include "../utils/JSONShortcut.h"

int clientRunner(Connexion_t connexion)
{
	signal(2, signal_clientRunner);
	signal(15, signal_clientRunner);
	//initClient();
	//Init ncurses
	//initscr();
	//WINDOW* window = stdscr;
	//CDKSCREEN* screen = initCDKScreen(window);
	//initCDKColor();
	//char *a[1];
	//a[0] =  (char*) "</B>Bonjour !<!B>";
	//CDKDIALOG* dialog = newCDKDialog(screen, CENTER, CENTER, (char**) a, 1, 0, 0, 0, 1, 1, 1);
	//CDKLABEL* label = newCDKLabel(screen, CENTER, CENTER, a, 1, 1, 1);
	//refreshCDKScreen(screen);
	//waitCDKDialog(dialog, ' ');
	//waitCDKLabel(label, ' ');
	//printw("OK !");
	//refresh();
	enum ClientRunnerMode mode = MAIN_MENU;
	String_t choice = autoString("");
	while(global_clientRunnerContinue(0, 0))
	{
		switch(mode)
		{
			case MAIN_MENU:
			printf("Bienvenue sur le menu principal, ");
			if(connexion->user != 0)
			{
				printf("%s\n", cStringValueOf(connexion->user, "Login"));
			}
			else
			{
				printf("vous n'êtes pas connecté.\n");
			}
			break;
			default:
			printf("Not implemented yet !\n");
			mode = MAIN_MENU;

		}
		usleep(10000);
		choice = ReadInputWithMsg(0);
		lowerString(choice);
		//printf("Vous avez entré: \"%s\"\n", cString(choice));
		if(equalsString(choice, autoString("exit")))
		{
			global_clientRunnerContinue(1,0);
		}
		else
		{
			printf("Inconnu: \"%s\"\n", cString(choice));
		}
	}
	//destroyCDKDialog(dialog);
	//destroyCDKScreen(screen);
	//Fin de ncurses
	//endCDK();
	//endwin();
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
