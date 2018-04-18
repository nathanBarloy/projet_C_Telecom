#include "ClientRunner.h"
#include <stdlib.h>
#include <JSONAll.h>
#include <String/String.h>



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
	while(global_clientRunnerContinue(0, 0))
	{
		usleep(10000);
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
