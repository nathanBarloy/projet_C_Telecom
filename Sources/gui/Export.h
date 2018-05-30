#ifndef EXPORT_H
#define EXPORT_H
#include <JSONAll.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
JSONObject_t getExport();
GtkWindow* getWindow(GtkWindow* w, bool edit);
WebKitWebView* getWebKitWebView(WebKitWebView* w, bool edit);
#endif
