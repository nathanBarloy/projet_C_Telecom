#include "sys/ClientRunner.h"
#include <String/AutoString.h>
#include "sys/ClientRequest.h"
#include "sys/ClientRequests.h"
#include "utils/Connexion.h"
#include "utils/JSONShortcut.h"
#include <gtk/gtk.h>
#include <webkit/webkit.h>

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
		/* Create the widgets */
		gtk_init(&argc, &argv);
		GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
		GtkWidget *web_view = webkit_web_view_new();

		/* Place the WebKitWebView in the GtkScrolledWindow */
		gtk_container_add (GTK_CONTAINER (scrolled_window), web_view);
		gtk_container_add (GTK_CONTAINER (main_window), scrolled_window);

		/* Open a webpage */
		webkit_web_view_load_uri(WEBKIT_WEB_VIEW(web_view), "http://www.gnome.org");

		/* Show the result */
		gtk_window_set_default_size(GTK_WINDOW (main_window), 800, 600);
		gtk_widget_show_all(main_window);
	/*	connexion = freeConnexion(connexion);
	}
	else
	{
		printf("Usage: client [server_ip]\n");
	}
	freeAutoString();*/
	return 0;
}
