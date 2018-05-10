#ifndef HTML_GENERATOR_H
#define HTML_GENERATOR_H
#include <String/String.h>
#include <JSONAll.h>
#include "Connexion.h"
#include <Vector/Vector.h>
String_t HTMLFromJSONContainer(Connexion_t connexion, JSONObject_t json, JSONObject_t container, Vector_t params);
String_t HTMLFromJSON(Connexion_t connexion, JSONObject_t json, Vector_t params);
String_t HTMLFromJSONString(Connexion_t connexion, String_t str, Vector_t params);
String_t HTMLFromJSONFile(Connexion_t connexion, String_t file, Vector_t params);
String_t HTMLFromJSONUrl(Connexion_t connexion, String_t url);
#endif
