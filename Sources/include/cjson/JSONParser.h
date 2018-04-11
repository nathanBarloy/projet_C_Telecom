#ifndef JSONPARSER_H
#define JSONPARSER_H
#include "JSONObject.h"
#define JSONPARSER_DEFAULT_EXIT 1
#ifdef __cplusplus
#include <JSONAll.hpp>
extern "C"
{
#endif
/*! \brief Permet de parser une chaine JSON en Arbre JSON
*
* La chaine entrée doit être un JSON Valide, sinon une exception sera lancée.
*/
JSONObject_t JSONParser_parse(const char * str);
/*! \brief Permet de parser une chaine JSON en Arbre JSON
*
* La chaine entrée doit être un JSON Valide, sinon une exception sera lancée.
* \param str Chaine a parser
* \return JSONObject_t représentant l'arbre JSON, 0 en cas d'échec.
*/
JSONObject_t JSONParser_parseString(String_t str);
/*! \brief Permet de parser un fichier JSON
*
* Le fichier doit contenir un JSON Valide sinon une exception sera lancée.
* \param str Chaine a parser
* \return JSONObject_t représentant l'arbre JSON, 0 en cas d'échec.
*/
JSONObject_t JSONParser_parseFile(const char *fileName);
/*! \brief Permet de parser un fichier JSON
*
* Le fichier doit contenir un JSON Valide sinon une exception sera lancée.
* \param fileName Nom du fichier à parser
* \return JSONObject_t représentant l'arbre JSON, 0 en cas d'échec.
*/
JSONObject_t JSONParser_parseFileString(String_t fileName);
/*! \brief Permet de sauvegarder un arbre JSON dans un fichier
*
* \param obj Arbre JSON a sauvegarder.
* \param fileName Nom du fichier de sortie
* \return 1 en cas de réussie, 0 en cas d'échec.*/
bool JSONParser_saveFile(JSONObject_t obj, const char* fileName);
/*! \brief Permet de sauvegarder un arbre JSON dans un fichier
*
* \param obj Arbre JSON a sauvegarder.
* \param fileName Nom du fichier de sortie
* \return 1 en cas de réussie, 0 en cas d'échec.*/
bool JSONParser_saveFileString(JSONObject_t obj, String_t fileName);
/*! \brief Fonction interne a la bibliothèque, ne pas utiliser.
*
* Permet de modifier l'état de privateExit.
*/
bool JSONParser_privateExit(bool nv, bool modify);
/*! \brief Permet de savoir si le programme s'arrêtera ou non en cas d'exception.
*
* \param nv Nouvelle valeur
* \param modify Modifier la valeur si true/1.
* \return Retourne 1 si oui, 0 sinon.
*/
bool JSONParser_willExitOnException();
/*! \brief Permet de définir si le programme doit quitter ou non.
*
* Par défaut, en cas d'exception, le programme s'arrêtera.
* Sinon, l'exception sera gérée par libcjson et continuera.
* Les fonctions ayant provoquée une exception retourneront 0 a la place d'un quelconque pointeur.
* \param value true/1 pour quitter en cas d'exception, false/0 sinon.*/
void JSONParser_setExitOnException(bool value);
#ifdef __cplusplus
}
#endif
#endif
