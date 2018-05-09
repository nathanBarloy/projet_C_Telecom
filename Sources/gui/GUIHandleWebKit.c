#include "GUIHandleWebKit.h"
#define BOOL_DEFINED
#include <String/AutoString.h>
#include <unistd.h>
#include "../utils/FileToString.h"
#include "../utils/Connexion.h"

void clientGUIRessourceRequestStarting(WebKitWebView* web_view, WebKitWebFrame *web_frame, WebKitWebResource* web_resource, WebKitNetworkRequest *request, WebKitNetworkResponse* response, gpointer user_data)
{
	Connexion_t connexion = (Connexion_t) (user_data);
	printf("Request received.\n");
	printf("View: %p\n", web_view);
	printf("Frame: %p\n", web_frame);
	printf("Resource: %p\n", web_resource);
	printf("Request: %p\n", request);
	printf("Response: %p\n", response);
	printf("URI: %s\n", webkit_network_request_get_uri(request));
}
void clientGUIDocumentLoadFinished(WebKitWebView* web_view, WebKitWebFrame* web_frame, gpointer user_data)
{
	Connexion_t connexion = (Connexion_t) (user_data);
	printf("Document load finished.\n");
	printf("View: %p\n", web_view);
	printf("Frame: %p\n", web_frame);
}
gboolean clientGUIContextMenu(WebKitWebView *web_view, GtkWidget *default_menu, WebKitHitTestResult *hit_test_result, gboolean triggered_with_keyboard, gpointer user_data)
{
	Connexion_t connexion = (Connexion_t) (user_data);
	printf("Document load finished.\n");
	printf("View: %p\n", web_view);
	printf("DefaultMenu: %p\n", default_menu);
	return true;
}
void clientGUIStart(GtkApplication* app, gpointer user_data)
{
	Connexion_t connexion = (Connexion_t) (user_data);
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
	g_signal_connect(web_view, "resource-request-starting", G_CALLBACK(clientGUIRessourceRequestStarting), connexion);
	g_signal_connect(web_view, "document-load-finished", G_CALLBACK(clientGUIDocumentLoadFinished), connexion);
	g_signal_connect(web_view, "context-menu", G_CALLBACK(clientGUIContextMenu), connexion);
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
