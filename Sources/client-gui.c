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

void clientGUIStart(GtkApplication* app, gpointer user_data)
{
	/*GtkWidget *window;
	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
	gtk_widget_show_all (window);*/
	// Create the widgets
	//gtk_init(&argc, &argv);
	GtkWidget *main_window = gtk_application_window_new(app);
	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	GtkWidget *web_view = webkit_web_view_new();

	// Place the WebKitWebView in the GtkScrolledWindow
	gtk_container_add (GTK_CONTAINER (scrolled_window), web_view);
	gtk_container_add (GTK_CONTAINER (main_window), scrolled_window);

	//Open a webpage
	//webkit_web_view_load_uri(WEBKIT_WEB_VIEW(web_view), /*"http://www.gnome.org"*//*"https://www.youtube.com/watch?v=Ugs9HASX4rA")*/);
	String_t html = fileToString(autoString("web/boot.html"));
	if(html != 0)
	{
		webkit_web_view_load_string(WEBKIT_WEB_VIEW(web_view), cString(html), 0,0,"web/boot.html");
		fString(html);
	}
	else
	{
		webkit_web_view_load_string(WEBKIT_WEB_VIEW(web_view), cString(autoString("Unable to load: web/boot.html")), 0,0,"web/boot.html");
	}
	// Show the result
	gtk_window_set_default_size(GTK_WINDOW (main_window), 800, 600);
	gtk_widget_show_all(main_window);
}
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


		GtkApplication* app;
		int status = 0;
		app = gtk_application_new("eu.telecomnancy.projet_csd.g3", G_APPLICATION_FLAGS_NONE);
		g_signal_connect(app, "activate", G_CALLBACK(clientGUIStart), NULL);
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
