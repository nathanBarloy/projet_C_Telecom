#ifndef HTML_GENERATOR_H
#define HTML_GENERATOR_H
#include <String/String.h>
#include <JSONAll.h>
#include "Connexion.h"
String_t HTMLFromJSONContainer(Connexion_t connexion, JSONObject_t container);
String_t HTMLFromJSON(Connexion_t connexion, JSONObject_t json);
String_t HTMLFromJSONString(Connexion_t connexion, String_t str);
String_t HTMLFromJSONFile(Connexion_t connexion, String_t file);
String_t HTMLFromJSONUrl(Connexion_t connexion, String_t url);
#endif
