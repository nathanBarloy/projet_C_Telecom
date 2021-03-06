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
	setMap(r, autoString("menuContent"), (void*) HTMLMenuContent);
	setMap(r, autoString("film"), (void*) HTMLFilm);
	setMap(r, autoString("ficheFilm"), (void*) HTMLFicheFilm);
	setMap(r, autoString("menuLogin"), (void*) HTMLMenuLogin);
	setMap(r, autoString("register"), (void*) HTMLRegister);
	setMap(r, autoString("export"), (void*) HTMLExport);
	//Fin des associations
	return r;
}
