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
String_t HTMLYoutubePlayer(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params);
String_t HTMLImg(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params);
String_t HTMLRatingStars(Connexion_t connexion);
//param
String_t getParam(String_t name, Vector_t params);



//HTMLGeneratorConnect
String_t HTMLConnectToServer(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params);
String_t HTMLCheckConnected(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params);
String_t HTMLMenuLogin(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params);

//HTMLMenuBar
String_t HTMLMenuBar(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params);
String_t HTMLMenuBar2(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params);


//HTMLMenuContent
String_t HTMLMenuContent(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params);
//HTMLFilm
String_t HTMLFilm(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params);
//HTMLFicheFilm
String_t HTMLFicheFilm(Connexion_t connexion, JSONObject_t json, JSONObject_t param, Vector_t params);
#endif
