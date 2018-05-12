#include "GUIHandleWebKit.h"
#define BOOL_DEFINED
#include <String/AutoString.h>
#include <unistd.h>
#include "../utils/FileToString.h"
#include "../utils/Connexion.h"
#include "../utils/HTMLGenerator.h"
#include <libsoup/soup.h>
#include <Vector/Vector.h>
#include "../utils/Headers.h"
#include <string.h>
#include <glib-object.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
bool clientGUI_blockableRequest = 1;
bool clientGUI_firstRequest = 1;
void clientGUIHeadGet(const char* name, const char* value, gpointer user_data)
{
	Vector_t v = (Vector_t) user_data;
	Header_t h = newHeaderFull((char*) name, (char*) value);
	addToVector(v, (void*) h);
}
void clientGUIRessourceRequestStarting(WebKitWebView* web_view, WebKitWebFrame *web_frame, WebKitWebResource* web_resource, WebKitNetworkRequest *request, WebKitNetworkResponse* response, gpointer user_data)
{
	Connexion_t connexion = (Connexion_t) (user_data);
	printf("Request received.\n");
	printf("View: %p\n", web_view);
	printf("Frame: %p\n", web_frame);
	printf("Resource: %p\n", web_resource);
	printf("Request: %p\n", request);
	printf("FrameURI: %s\n", webkit_web_frame_get_uri(web_frame));
	printf("Response: %p\n", response);
	printf("URI: %s\n", webkit_network_request_get_uri(request));
	printf("Print end.\n");
	char *cfuri = (char*) webkit_web_frame_get_uri(web_frame);
	AutoString_t uri = autoString((char*)webkit_network_request_get_uri(request)), furi = autoString(cfuri != 0 ? cfuri : "");
	if(sizeOfString(uri) > 0 && uri->str[0] != 'e')
	{
		clientGUI_blockableRequest = false;
	}
	if(clientGUI_blockableRequest && !clientGUI_firstRequest)
	{
		clientGUI_blockableRequest = 0;
		//Reception des paramètres envoyés
		/*SoupMessage* msg = webkit_network_request_get_message(request);
		printf("Message: %p\n", msg);
		Vector_t headers = newVector();
		if(msg != 0)
		{
			SoupMessageBody* body = 0;
			//GValue val = G_VALUE_INIT;
			//g_value_init(&val, G_TYPE_POINTER);
			//g_object_get_property(G_OBJECT(msg), "request-body", &val);
			//body = (SoupMessageBody*) g_value_get(&val);
			g_object_get(msg, "request-body", &body, NULL);
			//g_value_unset(&val);
			if(body != 0)
			{
				printf("Body: %p\n", body);
				soup_message_body_complete(body);
				SoupBuffer* buffer = soup_message_body_get_chunk(body, 0);
				printf("Buffer: %p\n", buffer);
				if(buffer != 0)
				{
					char *buf = (char*) malloc(sizeof(char) * (buffer->length + 1));
					memcpy(buf, buffer->data, buffer->length);
					buf[buffer->length] = 0;
					printf("HTTP DATA:\n%s\n", buf);
					free(buf);
				}
			}

		}*/
		//Génération HTML
		//freeVectorWithPtr(headers, freeHeaderPtr);
		//Génération de la nouvelle requête
		size_t c = sizeOfString(uri) - 1;
		while(c > 0)
		{
			if(uri->str[c] == '.')
			{
				++c;
				break;
			}
			--c;
		}
		String_t mt = 0;
		bool isExec = true;
		if(c > 0)
		{
			if(strcmp(uri->str + c, "png") == 0)
			{
				mt = newStringFromCharStar("image/png");
			}
			else if(strcmp(uri->str + c, "jpg") == 0)
			{
				mt = newStringFromCharStar("image/jpeg");
			}
			if(mt != 0)
			{
				isExec = false;
			}
		}
		if(isExec)
		{
			webkit_web_view_stop_loading(web_view);
			printf("Request blocked: %s\n", cString(uri));
			String_t html = HTMLFromJSONUrl(connexion, uri);
			printf("Generated:\n%s\n", cString(html));
			//GetFile://
			char *wd = getcwd(0,0);
			String_t cwd = newStringFromCharStar(wd);
			free(wd);
			String_t r = newStringFromCharStar("file://");
			concatString(r, cwd);
			fString(cwd);
			cwd = newStringFromCharStar("/web/");
			concatString(r, cwd);
			fString(cwd);
			String_t value = newStringFromCharStar(uri->str + 7);
			concatString(r, value);
			fString(value);
			//end
			webkit_web_view_load_string(WEBKIT_WEB_VIEW(web_view), cString(html) , 0,0, cString(r));//Chargement via generateur HTML
			fString(r);
			fString(html);
		}
		else
		{
			if(/*sizeOfString(uri) >= sizeOfString(autoString(("exec://")))*/0)
			{
				/*String_t file = 0;
				if(sizeOfString(uri) >= sizeOfString(furi))
				{
					file = newStringFromCharStar(uri->str + sizeOfString(furi));
				}
				else
				{
					file = newStringFromCharStar(uri->str + sizeOfString(autoString("exec://")));
				}
				size_t st = 10000001;
				char *buf = (char*) malloc(sizeof(char) * st);
				buf[0] = 0;
				char *df = cString(autoConcatString(autoString("web/"), file));
				printf("Reading file: %s\n", df);
				int fd = open(df, O_RDONLY);
				if(fd != -1)
				{
					size_t r = read(fd, buf, st - 1);
					printf("Read size: %lu\n", r);
					buf[r] = 0;
					close(fd);
					//webkit_web_view_stop_loading(web_view);
					printf("Request blocked: %s\n", cString(uri));
					printf("Requesting: %s\n", df);
					//webkit_web_frame_load_string(WEBKIT_WEB_FRAME(web_frame), buf , cString(mt),0, cString(uri));//Chargement via generateur HTML
					free(buf);
				}
				else
				{
					printf("Error while reading file: %s\n", df);
				}*/
			}
			else
			{
				printf("Loading of: %s → Cancelled.", cString(uri));
			}
			fString(mt);
		}
	}
	else
	{
		printf("Request allowed: %s\n", cString(uri));
		clientGUI_blockableRequest = 1;
		clientGUI_firstRequest = 0;
	}
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
	//String_t html = fileToString(autoString("web/init.html"));
	webkit_web_view_load_string(WEBKIT_WEB_VIEW(web_view), "<!DOCTYPE html><html><head><meta http-equiv=\"refresh\" content=\"0;url=exec://init.json\" /></head><body>Loading...</body></html>", 0,0,"exec://wait");
	//sleep(1);
	//webkit_web_view_load_string(WEBKIT_WEB_VIEW(web_view), "", 0,0,"exec://init.json");
	/*if(html != 0)
	{
	fString(html);

	}
	else
	{
		webkit_web_view_load_string(WEBKIT_WEB_VIEW(web_view), cString(autoString("Unable to load: web/boot.html")), 0,0,"web/boot.html");
	}*/
	// Show the result
	gtk_window_set_default_size(GTK_WINDOW (main_window), 800, 600);
	gtk_widget_show_all(main_window);
}

Map_t getFunctionMap()
{
	Map_t r = newMap();
	//Insérer ici les associations
	setMap(r, autoString("youtube"), (void*) HTMLYoutubePlayer);
	setMap(r, autoString("img"), (void*) HTMLImg);
	setMap(r, autoString("connectToServer"), (void*) HTMLConnectToServer);
	//Fin des associations
	return r;
}
