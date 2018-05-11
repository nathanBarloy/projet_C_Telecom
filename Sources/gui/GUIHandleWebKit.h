#ifndef GUI_HANDLE_WEBKIT_H
#define GUI_HANDLE_WEBKIT_H
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <Map/Map.h>
void clientGUIHeadGet(const char* name, const char* value, gpointer user_data);
void clientGUIRessourceRequestStarting(WebKitWebView* web_view, WebKitWebFrame *web_frame, WebKitWebResource* web_resource, WebKitNetworkRequest *request, WebKitNetworkResponse* response, gpointer user_data);
void clientGUIDocumentLoadFinished(WebKitWebView* web_view, WebKitWebFrame* web_frame, gpointer user_data);
gboolean clientGUIContextMenu(WebKitWebView *web_view, GtkWidget *default_menu, WebKitHitTestResult *hit_test_result, gboolean triggered_with_keyboard, gpointer user_data);
void clientGUIStart(GtkApplication* app, gpointer user_data);
Map_t getFunctionMap();
#endif
