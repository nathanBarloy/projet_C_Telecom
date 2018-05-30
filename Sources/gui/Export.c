#include "Export.h"
JSONObject_t getExport()
{
	static bool firstCall = true;
	static JSONObject_t obj = 0;
	if(firstCall)
	{
		obj = JSONObject_new();
		firstCall = false;
	}
	printf("Export called:\n%s\n", cString(JSONObject_asString(obj, 0)));
	return obj;
}
GtkWindow* getWindow(GtkWindow* w, bool edit)
{
	static GtkWindow* wid = 0;
	if(edit)
	{
		wid = w;
	}
	return wid;
}

WebKitWebView* getWebKitWebView(WebKitWebView* w, bool edit)
{
	static WebKitWebView* wid = 0;
	if(edit)
	{
		wid = w;
	}
	return wid;
}
