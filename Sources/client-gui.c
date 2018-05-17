#include "sys/ClientRunner.h"
#include <String/AutoString.h>
#include "sys/ClientRequest.h"
#include "sys/ClientRequests.h"
#include "utils/Connexion.h"
#include "utils/JSONShortcut.h"
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <unistd.h>
#include "utils/FileToString.h"
#include "gui/GUIHandleWebKit.h"
#include "sys/ClientRunnerContinue.h"

int main(int argc, char** argv, char** envp)
{
	initClient();
	Connexion_t connexion = 0;
	if(argc >= 2)
	{
		connexion = newConnexion(argv[1]);//Adresse du serveur
		/*if(!serverExists(connexion))
		{
			setString(connexion->addr_s, autoString("");
		}*/
	}
	else
	{
		connexion = newConnexion("");
	}
	GtkApplication* app;
	int status = 0;
	app = gtk_application_new("eu.telecomnancy.projet_csd.g3", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(clientGUIStart), connexion);
	status = g_application_run(G_APPLICATION(app), 1, argv);
	g_object_unref(app);
	printf("Return: %d\n", status);
	connexion = freeConnexion(connexion);
	freeAutoString();
	return 0;
}
