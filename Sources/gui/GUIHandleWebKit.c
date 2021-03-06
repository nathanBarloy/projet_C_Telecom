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
#include "../sys/ClientRequests.h"
#include "../gui/Export.h"
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
	#ifdef DEBUG
	printf("Request received.\n");
	printf("View: %p\n", web_view);
	printf("Frame: %p\n", web_frame);
	printf("Resource: %p\n", web_resource);
	printf("Request: %p\n", request);
	printf("FrameURI: %s\n", webkit_web_frame_get_uri(web_frame));
	printf("Response: %p\n", response);
	printf("URI: %s\n", webkit_network_request_get_uri(request));
	printf("Print end.\n");
	#endif
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
			#ifdef DEBUG
			printf("Request blocked: %s\n", cString(uri));
			#endif
			String_t html = HTMLFromJSONUrl(connexion, uri);
			#ifdef DEBUG
			printf("Generated:\n%s\n", cString(html));
			#endif
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
			#ifdef DEBUG
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
			#endif
			fString(mt);
		}
	}
	else
	{
		#ifdef DEBUG
		printf("Request allowed: %s\n", cString(uri));
		#endif
		clientGUI_blockableRequest = 1;
		clientGUI_firstRequest = 0;
	}
}
void clientGUIDocumentLoadFinished(WebKitWebView* web_view, WebKitWebFrame* web_frame, gpointer user_data)
{
	Connexion_t connexion = (Connexion_t) (user_data);
	#ifdef DEBUG
	printf("Document load finished.\n");
	printf("View: %p\n", web_view);
	printf("Frame: %p\n", web_frame);
	#endif
	gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel(gtk_widget_get_toplevel(GTK_WIDGET(web_view)))),webkit_web_view_get_title(WEBKIT_WEB_VIEW(web_view)));
}
gboolean clientGUIContextMenu(WebKitWebView *web_view, GtkWidget *default_menu, WebKitHitTestResult *hit_test_result, gboolean triggered_with_keyboard, gpointer user_data)
{
	Connexion_t connexion = (Connexion_t) (user_data);
	#ifdef DEBUG
	printf("Document load finished.\n");
	printf("View: %p\n", web_view);
	printf("DefaultMenu: %p\n", default_menu);
	#endif
	return true;
}
void clientQUIT(GtkWidget* win, GdkEvent* ev, gpointer user_data)
{
	gtk_widget_destroy(win);
	Connexion_t connexion = (Connexion_t) user_data;
	RequestAnswer a = Client_Logout(connexion);
	if(a != 0)
	{
		freeRequestAnswer(a);
	}
	JSONObject_t e = getExport();
	JSONObject_delete(e);
}
void clientGUIUserChangedContents(WebKitWebView *web_view, gpointer user_data)
{
	//printf("CONTENT CHANGED !\n");
}
void clientGUIPasteClipboard(WebKitWebView *web_view, gpointer user_data)
{
	printf("CLIPBOARD !\n");
}
bool clientGUINavigationPolicyDecisionRequested(WebKitWebView *web_view, WebKitWebFrame* frame, WebKitNetworkRequest* request, WebKitWebNavigationAction* navigation_action, WebKitWebPolicyDecision *policy_decision, gpointer user_data)
{
	//printf("POLICY !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	char* rq = (char*) webkit_network_request_get_uri(request);
	if(rq[0] == 'f' && clientGUI_blockableRequest == 1)
	{
		webkit_web_policy_decision_ignore(policy_decision);
	}
	else
	{
		webkit_web_policy_decision_use(policy_decision);
	}
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
	getWindow(GTK_WINDOW(main_window), 1);
	getWebKitWebView(WEBKIT_WEB_VIEW(web_view), 1);
	// Place the WebKitWebView in the GtkScrolledWindow
	gtk_container_add (GTK_CONTAINER (scrolled_window), web_view);
	gtk_container_add (GTK_CONTAINER (main_window), scrolled_window);
	gtk_widget_set_size_request(main_window, 800, 600);
	g_signal_connect (main_window, "delete_event", G_CALLBACK (clientQUIT), connexion);
	//Open a webpage
	//webkit_web_view_load_uri(WEBKIT_WEB_VIEW(web_view), /*"http://www.gnome.org"*//*"https://www.youtube.com/watch?v=Ugs9HASX4rA")*/);
	g_signal_connect(web_view, "resource-request-starting", G_CALLBACK(clientGUIRessourceRequestStarting), connexion);
	g_signal_connect(web_view, "document-load-finished", G_CALLBACK(clientGUIDocumentLoadFinished), connexion);
	g_signal_connect(web_view, "context-menu", G_CALLBACK(clientGUIContextMenu), connexion);
	g_signal_connect(web_view, "user-changed-contents", G_CALLBACK(clientGUIUserChangedContents), connexion);
	g_signal_connect(web_view, "paste-clipboard", G_CALLBACK(clientGUIPasteClipboard), connexion);
	g_signal_connect(web_view, "navigation-policy-decision-requested", G_CALLBACK(clientGUINavigationPolicyDecisionRequested), connexion);
	//String_t html = fileToString(autoString("web/init.html"));
	webkit_web_view_load_string(WEBKIT_WEB_VIEW(web_view), "<!DOCTYPE html><html><head><meta http-equiv=\"refresh\" content=\"0;url=exec://init.json\" /></head><body>Loading...</body></html>", 0,0,"exec://wait");
	// Show the result
	gtk_window_set_default_size(GTK_WINDOW (main_window), 800, 600);
	gtk_widget_show_all(main_window);
}
