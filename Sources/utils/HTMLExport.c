#include "HTMLGenerator.h"
#include "../gui/Export.h"
#include <gtk/gtk.h>
#include "JSONShortcut.h"
#include <webkit/webkit.h>
gboolean HTMLExportDialog(gpointer ptr)
{
	JSONObject_t e = getExport();
	JSONObject_t data = JSONObject_get(e, AS("Data")), name = JSONObject_get(e, AS("Name")), url = JSONObject_get(e, AS("Url"));
	String_t tmp = 0;
	if(data == 0)
	{

	}
	else
	{
		//webkit_web_view_stop_loading(getWebKitWebView(0,0));
		AutoString_t n = (name != 0 &&JSONObject_getType(name) == STRING) ? JSONString_get(name) : autoString("fichier.txt");
		GtkWidget *dialog;
		GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
		gint res;
		dialog = gtk_file_chooser_dialog_new ("Sauvegarder les données", getWindow(0,0), action, "_Annuler", GTK_RESPONSE_CANCEL, "_Enregistrer", GTK_RESPONSE_ACCEPT, NULL);
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
		printf("Filename base: %s\n", cString(n));
		//gtk_file_chooser_set_filename (chooser, cString(n));
		gtk_file_chooser_set_current_name(chooser, cString(n));
		gtk_file_chooser_set_local_only(chooser, true);
		res = gtk_dialog_run (GTK_DIALOG (dialog));
		if (res == GTK_RESPONSE_ACCEPT)
		{
		char *filename;
		filename = gtk_file_chooser_get_filename(chooser);
		printf("Filename: %s\n", filename);
		if(filename != 0)
		{
			JSONParser_saveFile(data, filename);
		}
		else
		{
			printf("Pas de fichier spécifié.\n");
		}
		g_free (filename);
		}
		gtk_widget_destroy(dialog);

	}
	return false;
}
void HTMLExportLater()
{
	g_timeout_add_seconds(0, (GSourceFunc) HTMLExportDialog, 0);
}
String_t HTMLExport(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t r = newStringFromCharStar("<div class=\"ctr\"><h1>Export de données</h1>");
	JSONObject_t e = getExport();
	JSONObject_t data = JSONObject_get(e, AS("Data")), name = JSONObject_get(e, AS("Name")), url = JSONObject_get(e, AS("Url"));
	String_t tmp = 0;
	if(data == 0)
	{
		concatString(r, autoString("Aucune donnée à exporter.<br />"));
	}
	else
	{
		//webkit_web_view_stop_loading(getWebKitWebView(0,0));
		/*AutoString_t n = (name != 0 &&JSONObject_getType(name) == STRING) ? JSONString_get(name) : autoString("fichier.txt");
		GtkWidget *dialog;
		GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
		gint res;
		dialog = gtk_file_chooser_dialog_new ("Sauvegarder les données", getWindow(0,0), action, "_Annuler", GTK_RESPONSE_CANCEL, "_Enregistrer", GTK_RESPONSE_ACCEPT, NULL);
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
		printf("Filename base: %s\n", cString(n));
		//gtk_file_chooser_set_filename (chooser, cString(n));
		gtk_file_chooser_set_current_name(chooser, cString(n));
		gtk_file_chooser_set_local_only(chooser, true);
		res = gtk_dialog_run (GTK_DIALOG (dialog));
		if (res == GTK_RESPONSE_ACCEPT)
		{
		char *filename;
		filename = gtk_file_chooser_get_filename(chooser);
		printf("Filename: %s\n", filename);
		if(filename != 0)
		{
			JSONParser_saveFile(data, filename);
		}
		else
		{
			printf("Pas de fichier spécifié.\n");
		}
		g_free (filename);
		}
		gtk_widget_destroy(dialog);*/
		tmp = newStringFromCharStar("<a href=\"exec://export.json\" >Exporter à nouveau...</a><br/>");
		concatString(r, tmp);
		HTMLExportLater();

	}

	if(url != 0)
	{
 	tmp = newStringFromCharStar("<a href=\"");
	concatString(r, tmp);
	fString(tmp);
	concatString(r, JSONString_get(url));
	tmp = newStringFromCharStar("\" >Retour</a><br/>");
	concatString(r, tmp);
	}
	tmp = newStringFromCharStar("</div>");
	concatString(r, tmp);
	fString(tmp);
	return r;
}
