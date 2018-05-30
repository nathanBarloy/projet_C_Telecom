#include "HTMLGenerator.h"
#include "../gui/Export.h"
#include <gtk/gtk.h>

String_t HTMLExport(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params)
{
	String_t r = newStringFromCharStar("<div class=\"ctr\"><h1>Export de données</h1>");
	JSONObject_t e = getExport();
	JSONObject_t data = JSONObject_get(e, AS("Data")), name = JSONObject_get(e, AS("Name")), url = JSONObject_get(e, AS("Url"));
	if(data == 0)
	{
		concatString(r, autoString("Aucune donnée à exporter.<br />"));
	}
	else
	{
		String_t n = (name != 0 ) ? name : autoString("fichier.txt");
		GtkWidget *dialog;
		GtkFileChooser *chooser;
		GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
		gint res;
		dialog = gtk_file_chooser_dialog_new ("Sauvegarder les données", getWebkit(0,0), action, _("_Cancel"), GTK_RESPONSE_CANCEL, _("_Save"), GTK_RESPONSE_ACCEPT, NULL);
		gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
		gtk_file_chooser_set_filename (chooser, cString(n));
		res = gtk_dialog_run (GTK_DIALOG (dialog));
		if (res == GTK_RESPONSE_ACCEPT)
		{
		char *filename;
		filename = gtk_file_chooser_get_filename (chooser);
		JSONParser_saveFile(data, filename);
		g_free (filename);
		}

	}
	String_t tmp = 0;
	if(url != 0)
	{
 	tmp = newStringFromCharStar("<a href=\"");
	concatString(r, tmp);
	fString(tmp);
	concatString(r, JSONString_get(url));
	tmp = newStringFromCharStar("\" >Retour</a>");

	}
	tmp = newStringFromCharStar("</div>");
	concatString(r, tmp);
	fString(tmp);
	return r;
}
