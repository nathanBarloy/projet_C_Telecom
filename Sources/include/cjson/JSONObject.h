#ifndef JSONOBJECT_H
#define JSONOBJECT_H
#include <String/String.h>
#include <Vector/Vector.h>
#include <String/AutoString.h>
#include "JSONTuple.h"
#ifdef __cplusplus
#include <string>
#include <JSONAll.hpp>
/*! \brief S_JSONObject permet un cast en JSONObject* (retour en C++) */
#define S_JSONObject(a) static_cast<JSONObject*>(a)
/*! \brief S_JSONInt permet un cast en JSONInt* (retour en C++) */
#define S_JSONInt(a) static_cast<JSONInt*>(a)
/*! \brief S_JSONString permet un cast en JSONString* (retour en C++) */
#define S_JSONString(a) static_cast<JSONString*>(a)
/*! \brief S_JSONDouble permet un cast en JSONDouble* (retour en C++) */
#define S_JSONDouble(a) static_cast<JSONDouble*>(a)
/*! \brief S_JSONBoolean permet un cast en JSONBoolean* (retour en C++) */
#define S_JSONBoolean(a) static_cast<JSONBoolean*>(a)
/*! \brief S_JSONArray permet un cast en JSONArray* (retour en C++) */
#define S_JSONArray(a) static_cast<JSONArray*>(a)
/*! \brief S_JSONNull permet un cast en JSONNull* (retour en C++) */
#define S_JSONNull(a) static_cast<JSONNull*>(a)
/*! \brief S_JSONValue permet un cast en JSONValue* (retour en C++) */
#define S_JSONValue(a) static_cast<JSONValue*>(a)
extern "C"
{
#endif
#ifndef __cplusplus
/*! \brief Représente le vrai d'un booleen*/
#define true 1
/*! \brief Représente le faux d'un booleen*/
#define false 0
/*! \brief Définition du type bool en C
* Le type bool n'existe pas en C, il est pourtant utilisé par libjson en C++.
* Cette définition permet de l'utiliser de manière transparente.
*/
#ifndef BOOL_DEFINED
#define BOOL_DEFINED
typedef char bool;
#endif
#endif
/*! \brief JSONType_t représente le type de l'objet JSON pointé
* Ce type est 100% compatible avec celui de libjson, il permet de tester le type d'un objet JSON.
*/
typedef enum
{
	OBJECT, ARRAY, VALUE, STRING, INT, DOUBLE, BOOLEAN, NULLOBJ
}  JSONType_t;
/*! \brief JSONObject_t représente un objet JSON en C
* Il représente d'ailleurs n'importe quel objet JSON en C, les pointeurs sont interchangeables avec les autres types.
* Toutes ces définitions correspondent a void*, elles existent toutes cependant pour permettre une utilisation plus intuitive de la bibliothèque.
*/
typedef void* JSONObject_t;
/*! \brief JSONInt_t représente un objet JSON en C
* Il représente d'ailleurs n'importe quel objet JSON en C, les pointeurs sont interchangeables avec les autres types.
* Toutes ces définitions correspondent a void*, elles existent toutes cependant pour permettre une utilisation plus intuitive de la bibliothèque.
*/
typedef void* JSONInt_t;
/*! \brief JSONString_t représente un objet JSON en C
* Il représente d'ailleurs n'importe quel objet JSON en C, les pointeurs sont interchangeables avec les autres types.
* Toutes ces définitions correspondent a void*, elles existent toutes cependant pour permettre une utilisation plus intuitive de la bibliothèque.
*/
typedef void* JSONString_t;
/*! \brief JSONDouble_t représente un objet JSON en C
* Il représente d'ailleurs n'importe quel objet JSON en C, les pointeurs sont interchangeables avec les autres types.
* Toutes ces définitions correspondent a void*, elles existent toutes cependant pour permettre une utilisation plus intuitive de la bibliothèque.
*/
typedef void* JSONDouble_t;
/*! \brief JSONBoolean_t représente un objet JSON en C
* Il représente d'ailleurs n'importe quel objet JSON en C, les pointeurs sont interchangeables avec les autres types.
* Toutes ces définitions correspondent a void*, elles existent toutes cependant pour permettre une utilisation plus intuitive de la bibliothèque.
*/
typedef void* JSONBoolean_t;
/*! \brief JSONArray_t représente un objet JSON en C
* Il représente d'ailleurs n'importe quel objet JSON en C, les pointeurs sont interchangeables avec les autres types.
* Toutes ces définitions correspondent a void*, elles existent toutes cependant pour permettre une utilisation plus intuitive de la bibliothèque.
*/
typedef void* JSONArray_t;
/*! \brief JSONNull_t représente un objet JSON en C
* Il représente d'ailleurs n'importe quel objet JSON en C, les pointeurs sont interchangeables avec les autres types.
* Toutes ces définitions correspondent a void*, elles existent toutes cependant pour permettre une utilisation plus intuitive de la bibliothèque.
*/
typedef void* JSONNull_t;
/*! \brief JSONValue_t représente un objet JSON en C
* Il représente d'ailleurs n'importe quel objet JSON en C, les pointeurs sont interchangeables avec les autres types.
* Toutes ces définitions correspondent a void*, elles existent toutes cependant pour permettre une utilisation plus intuitive de la bibliothèque.
*/
typedef void* JSONValue_t;
/*! \brief Instancie un nouveau JSONObject*
* L'objet C++ instancié sera récupéré sous forme de JSONObject_t
* \return Nouvel objet
*/
JSONObject_t JSONObject_new();
/*! \brief Libère la mémoire d'un JSONObject_t
* Libère aussi la mémoire de n'importe quel autre objet.
* Utilisation conséillée:
* `a = JSONObject_delete(a);`
* \param self Objet à libérer de la mémoire
* \return 0
*/
JSONObject_t JSONObject_delete(JSONObject_t self);
/*! \brief Définir la valeur d'une clé
* Voir JSONObject::set
* \param self Objet dans lequel modifier la clé
* \param name Nom de la clé
* \param child Nouvelle valeur pour la clé
* Note: Ne libère pas la mémoire de la précédente valeur.
*/
void JSONObject_set(JSONObject_t self, String_t name, JSONObject_t child);
/*! \brief Définir la valeur d'une clé
* Voir JSONObject::set
* \param self Objet dans lequel modifier la clé
* \param name Nom de la clé
* \param child Nouvelle valeur pour la clé
* Note: Ne libère pas la mémoire de la précédente valeur.
*/
void JSONObject_setInt(JSONObject_t self, String_t name, int child);
/*! \brief Définir la valeur d'une clé
* Voir JSONObject::set
* \param self Objet dans lequel modifier la clé
* \param name Nom de la clé
* \param child Nouvelle valeur pour la clé
* Note: Ne libère pas la mémoire de la précédente valeur.
*/
void JSONObject_setDouble(JSONObject_t self, String_t name, double child);
/*! \brief Définir la valeur d'une clé
* Voir JSONObject::set
* \param self Objet dans lequel modifier la clé
* \param name Nom de la clé
* \param child Nouvelle valeur pour la clé
* Note: Ne libère pas la mémoire de la précédente valeur.
*/
void JSONObject_setString(JSONObject_t self, String_t name, String_t child);
/*! \brief Définir la valeur d'une clé
* Voir JSONObject::set
* \param self Objet dans lequel modifier la clé
* \param name Nom de la clé
* \param child Nouvelle valeur pour la clé
* Note: Ne libère pas la mémoire de la précédente valeur.
*/
void JSONObject_setBoolean(JSONObject_t self, String_t name, bool child);
/*! \brief Supprimer une clé et sa valeur
* Voir JSONObject::remove
* Supprime la clé, et libère la mémoire de la valeur si destruct=true.
* \param self Objet à modifier
* \param name Clé
* \param destruct Si true, libère la mémoire de l'objet associé a la clé.
*/
void JSONObject_remove(JSONObject_t self, String_t name, bool destruct);
/*! \brief Supprimer une clé et sa valeur a partir de la valeur
* Voir JSONObject::remove
* Supprime la clé, et libère la mémoire de la valeur si destruct=true.
* \param self Objet à modifier
* \param obj Valeur (ptr)
* \param destruct Si true, libère la mémoire de l'objet associé a la clé.
*/
void JSONObject_removeObject(JSONObject_t self, JSONObject_t obj, bool destruct);
/*! \brief Détacher un objet d'une clé, et libérer la mémoire
* Equivalent de JSONObject_remove avec destruct=true.
* \param self Object à modifier
* \param name clé à détacher */
void JSONObject_detach(JSONObject_t self, String_t name);
/*! \brief Détacher un objet d'une clé, et libérer la mémoire
* Equivalent de JSONObject_removeObject avec destruct=true.
* \param self Object à modifier
* \param obj Objet à détacher */
void JSONObject_detachObject(JSONObject_t self, JSONObject_t obj);
/*! \brief Détacher tous les objets du JSONObject
*
* Ne libère pas la mémoire.
* \param self Object concerné
*/
void JSONObject_detachAll(JSONObject_t self);
/*! \brief Obtenir un JSONObject de valeur pour une clé
*
* \param self Object concerné
* \param name Clé dans l'objet
* \return JSONObject correspondant a la valeur de la clé
*/
JSONObject_t JSONObject_get(JSONObject_t self, String_t name);
/*! \brief Obtenir un String_t correspondant au nom de la clé pour la valeur donnée (pointeur)
*
* \param self Object concerné
* \param child Valeur dans l'objet
* \return String_t correspondant au nom de la clé
*/
AutoString_t JSONObject_getKey(JSONObject_t self, JSONObject_t child);
/*! \brief Obtenir un JSONObject de valeur pour une clé, au type souhaité
*
* \param self Object concerné
* \param name Clé dans l'objet
* \return JSONObject correspondant a la valeur de la clé
*/
JSONInt_t JSONObject_getInt(JSONObject_t self, String_t name);
/*! \brief Obtenir un JSONObject de valeur pour une clé, au type souhaité
*
* \param self Object concerné
* \param name Clé dans l'objet
* \return JSONObject correspondant a la valeur de la clé
*/
JSONString_t JSONObject_getString(JSONObject_t self, String_t name);
/*! \brief Obtenir un JSONObject de valeur pour une clé, au type souhaité
*
* \param self Object concerné
* \param name Clé dans l'objet
* \return JSONObject correspondant a la valeur de la clé
*/
JSONDouble_t JSONObject_getDouble(JSONObject_t self, String_t name);
/*! \brief Obtenir un JSONObject de valeur pour une clé, au type souhaité
*
* \param self Object concerné
* \param name Clé dans l'objet
* \return JSONObject correspondant a la valeur de la clé
*/
JSONBoolean_t JSONObject_getBoolean(JSONObject_t self, String_t name);
/*! \brief Obtenir un JSONObject de valeur pour une clé, au type souhaité
*
* \param self Object concerné
* \param name Clé dans l'objet
* \return JSONObject correspondant a la valeur de la clé
*/
JSONArray_t JSONObject_getArray(JSONObject_t self, String_t name);
/*! \brief Obtenir la valeur de l'objet dans le type souhaité pour une clé donnée
*
* \param self Object concerné
* \param name Clé dans l'objet
* \return Type correspondant au type souhaité, valeur de la clé
*/
AutoString_t JSONObject_stringValueOf(JSONObject_t self, String_t name);
/*! \brief Obtenir la valeur de l'objet dans le type souhaité pour une clé donnée
*
* \param self Object concerné
* \param name Clé dans l'objet
* \return Type correspondant au type souhaité, valeur de la clé
*/
int JSONObject_intValueOf(JSONObject_t self, String_t name);
/*! \brief Obtenir la valeur de l'objet dans le type souhaité pour une clé donnée
*
* \param self Object concerné
* \param name Clé dans l'objet
* \return Type correspondant au type souhaité, valeur de la clé
*/
double JSONObject_doubleValueOf(JSONObject_t self, String_t name);
/*! \brief Obtenir la valeur de l'objet dans le type souhaité pour une clé donnée
*
* \param self Object concerné
* \param name Clé dans l'objet
* \return Type correspondant au type souhaité, valeur de la clé
*/
bool JSONObject_booleanValueOf(JSONObject_t self, String_t name);
/*! \brief Obtenir la valeur de l'objet dans le type souhaité
*
* \param self Object concerné
* \return Type correspondant au type souhaité
*/
AutoString_t JSONObject_stringValue(JSONObject_t self);
/*! \brief Obtenir la valeur de l'objet dans le type souhaité
*
* \param self Object concerné
* \return Type correspondant au type souhaité
*/
int JSONObject_intValue(JSONObject_t self);
/*! \brief Obtenir la valeur de l'objet dans le type souhaité
*
* \param self Object concerné
* \return Type correspondant au type souhaité
*/
double JSONObject_doubleValue(JSONObject_t self);
/*! \brief Obtenir la valeur de l'objet dans le type souhaité
*
* \param self Object concerné
* \return Type correspondant au type souhaité
*/
bool JSONObject_booleanValue(JSONObject_t self);
/*! \brief Convertir en texte JSON
*
* Parse n'importe quel JSONObject en String_t.
* Permet d'avoir la chaine JSON correspondant à l'arbre.
* \param self Objet concerné
* \return String_t équivalent de l'arbre JSON en chaine de caractères.
*/
AutoString_t JSONObject_asString(JSONObject_t self, unsigned int tabs);
/*! \brief Renvoie le parent
*
* \param self Objet concerné
* \return Parent
*/
JSONObject_t JSONObject_getParent(JSONObject_t self);
/*! \brief Vérifier si l'objet à un parent
*
* \param self Objet concerné
* \return true/1 si l'objet à un parent, false/0 sinon.
*/
bool JSONObject_hasParent(JSONObject_t self);
/*! \brief Transformer l'objet JSON en Vector de JSONTuple_t
*
* \param self Objet concerné
* \return Vector_t Array contenant des JSONTuples_t formant les couples.
*/
Vector_t JSONObject_asVector(JSONObject_t self);
/*! \brief Retourne le type de l'objet sous forme de JSONType_t
* \param self Objet concerné
* \return Type de l'objet
*/
JSONType_t JSONObject_getType(JSONObject_t self);
/*! \brief Compare 2 objets de type JSONObject entre eux.
*
* \param self Objet concerné
* \param obj Objet avec lequel le comparer
* Compare les valeurs contenues, et les valeurs de tous les enfants.
*/
bool JSONObject_equals(JSONObject_t self, JSONObject_t obj);
/*! \brief Nettoyer l'objet, le remettre à son état par défaut
*
* \param self Objet concerné
* Supprime toutes les clés
* Note: Ne libère pas la mémoire des clés libérées.
*/
void JSONObject_clear(JSONObject_t self);
/*! \brief Assigner un autre objet à celui ci
*
* \param self Objet concerné (destination)
* \param obj Objet servant de source
* Ajoute les valeurs de l'objet obj dans l'objet concerné (self)
* Ne supprime pas les valeurs déjà présents dans l'objet.
*/
bool JSONObject_assign(JSONObject_t self, JSONObject_t obj);
/*! \brief Assigner un tableau de couples JSONTuples_t à celui ci
*
* \param self Objet concerné (destination)
* \param arr Tableau servant de source
* Ajoute les valeurs du tableau dans l'objet concerné (self)
* Ne supprime pas les valeurs déjà présents dans l'objet.
*/
bool JSONObject_assignArray(JSONObject_t self, Vector_t arr);
#ifdef __cplusplus
}
#endif
#endif
