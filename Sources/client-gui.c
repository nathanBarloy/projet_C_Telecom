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


int main(int argc, char** argv, char** envp)
{
	/*if(argc >= 2)
	{
		initClient();
		Connexion_t connexion = newConnexion(argv[1]);*///Adresse du serveur
		//prints(connexion, autoString("Bonjour tout le monde !"));


		/*JSONObject_t machin = JSONObject_new();
		JSONObject_set(machin, autoString("lol"), JSONString_new(autoString("Bonjour")));
		JSONObject_set(machin, autoString("lol2"), JSONInt_new(18));
		printf("%s\n", cStringValueOf(machin, "lol"));
		printf("%d\n", ValueOf(machin, "lol2", int));
		JSONObject_delete(machin);*/


		//int r = clientRunner(connexion);
		//Fin
		Connexion_t connexion = 0;

		GtkApplication* app;
		int status = 0;
		app = gtk_application_new("eu.telecomnancy.projet_csd.g3", G_APPLICATION_FLAGS_NONE);
		g_signal_connect(app, "activate", G_CALLBACK(clientGUIStart), connexion);
		status = g_application_run(G_APPLICATION(app), argc, argv);
		g_object_unref(app);
		printf("Return: %d\n", status);
	/*	connexion = freeConnexion(connexion);
	}
	else
	{
		printf("Usage: client [server_ip]\n");
	}
	freeAutoString();*/
	return 0;
}
