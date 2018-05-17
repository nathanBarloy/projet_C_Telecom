#include "GUIHandleWebKit.h"
#include <String/AutoString.h>
#define BOOL_DEFINED
#include "../utils/HTMLGenerator.h"
Map_t getFunctionMap()
{
	Map_t r = newMap();
	//Insérer ici les associations
	setMap(r, autoString("youtube"), (void*) HTMLYoutubePlayer);
	setMap(r, autoString("img"), (void*) HTMLImg);
	setMap(r, autoString("connectToServer"), (void*) HTMLConnectToServer);
	setMap(r, autoString("checkConnected"), (void*) HTMLCheckConnected);
	setMap(r, autoString("menuBar"), (void*) HTMLMenuBar);
	setMap(r, autoString("menuBar2"), (void*) HTMLMenuBar2);
	//Fin des associations
	return r;
}
