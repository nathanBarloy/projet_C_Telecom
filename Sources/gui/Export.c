#include "Export.h"
JSONObject_t getExport()
{
	static bool firstCall = true;
	static JSONObject_t obj = 0;
	if(firstCall)
	{
		obj = JSONObject_new();
	}
	return obj;
}
GtkWidget* getWebkit(GtkWidget* w, bool edit)
{
	static GtkWidget* wid = 0;
	if(edit)
	{
		wid = w;
	}
	return wid;
}
