#ifndef JSONARRAY_H
#define JSONARRAY_H
#include "JSONValue.h"
#ifdef __cplusplus
#include <JSONAll.hpp>
extern "C"
{
#endif
/*! \brief Crée un nouveau JSONArray
* \return Nouveau JSONArray
 */
JSONArray_t JSONArray_new();
/*! \brief Crée un nouveau JSONArray depuis un tableau
* \return Nouveau JSONArray
*/
JSONArray_t JSONArray_newFromVector(Vector_t arr);
/*! \brief Voir JSONObject_delete()
* \param self Objet courant*/
JSONArray_t JSONArray_delete(JSONArray_t self);
/*! \brief Voir JSONObject_getParent()
* \param self Objet courant*/
JSONArray_t JSONArray_getParent(JSONArray_t self);
/*! \brief  Voir JSONObject_hasParent()
* \param self Objet courant*/
bool JSONArray_hasParent(JSONArray_t self);
/*! \brief Voir JSONObject_asString()
* \param self Objet courant */
AutoString_t JSONArray_asString(JSONArray_t self, unsigned int tabs);
/*! \brief Retourne le JSONObject a la position n
* \param n Position dans le tableau
* \param self Objet courant
* \return JSONObject */
JSONObject_t JSONArray_get(JSONArray_t self, unsigned int n);
/*! \brief Retourne le JSONObject a la position n
* \param n Position dans le tableau
* \param self Objet courant
* \return JSONObject */
JSONInt_t JSONArray_getInt(JSONArray_t self, unsigned int n);
/*! \brief Retourne le JSONObject a la position n
* \param n Position dans le tableau
* \param self Objet courant
* \return JSONObject */
JSONString_t JSONArray_getString(JSONArray_t self, unsigned int n);
/*! \brief Retourne le JSONObject a la position n
* \param n Position dans le tableau
* \param self Objet courant
* \return JSONObject */
JSONDouble_t JSONArray_getDouble(JSONArray_t self, unsigned int n);
/*! \brief Retourne le JSONObject a la position n
* \param n Position dans le tableau
* \param self Objet courant
* \return JSONObject */
JSONBoolean_t JSONArray_getBoolean(JSONArray_t self, unsigned int n);
/*! \brief Retourne le JSONObject a la position n
* \param n Position dans le tableau
* \param self Objet courant
* \return JSONObject */
JSONArray_t JSONArray_getArray(JSONArray_t self, unsigned int n);
/*! \brief Retourne la chaine à la position n
* \param n Position dans le tableau
* \param self Objet courant
* \return String_t */
AutoString_t JSONArray_stringValue(JSONArray_t self, unsigned int n);
/*! \brief Détache le JSONObject a la position n
* \param n Position dans le tableau
* Libére la mémoire automatiquement, voir JSONArray::detach
* \param self Objet courant
*/
void JSONArray_detachIndex(JSONArray_t self, unsigned int n);
/*! \brief Détache le JSONObject a la position n
* \param obj Objet a retirer du tableau
* Libére la mémoire automatiquement, voir JSONArray::detach
* \param self Objet courant
*/
void JSONArray_detach(JSONArray_t self, JSONObject_t obj);
/*! \brief Détache tous les objets présents dans le tableau
* Libére la mémoire automatiquement, voir JSONArray::detach
* \param self Objet courant
*/
void JSONArray_detachAll(JSONArray_t self);
/*! \brief Retourne la valeur à la position n
* \param n Position dans le tableau
* \param self Objet courant
* \return Valeur du type demandé */
int JSONArray_intValue(JSONArray_t self, unsigned int n);
/*! \brief Retourne la valeur à la position n
* \param n Position dans le tableau
* \param self Objet courant
* \return Valeur du type demandé */
double JSONArray_doubleValue(JSONArray_t self, unsigned int n);
/*! \brief Retourne la valeur à la position n
* \param n Position dans le tableau
* \param self Objet courant
* \return Valeur du type demandé */
bool JSONArray_booleanValue(JSONArray_t self, unsigned int n);
/*! \brief Assigne la valeur (objet) à la position n
* \param n Position dans le tableau
* \param self Objet courant
* \param obj Nouvel objet à placer dans le tableau */
void JSONArray_set(JSONArray_t self, unsigned int i, JSONObject_t obj);
/*! \brief Retourne la taille du tableau (nombre d'élements)
* \param self Objet courant
* \return Taille du tableau/nombre d'élements dans le tableau*/
unsigned int JSONArray_size(JSONArray_t self);
/*! \brief Détache le JSONObject a la position i
* \param self Objet courant
* \param i Position dans le tableau
* \param destruct Libére la mémoire automatiquement si true, sinon ne libère pas la mémoire de l'objet détaché
* Libére la mémoire automatiquement si destruct=true, voir JSONArray::detach
*/
void JSONArray_removeIndex(JSONArray_t self, unsigned int i, bool destruct);
/*! \brief Détache le JSONObject du tableau
* \param self Objet courant
* \param obj Objet à supprimer du tableau
* \param destruct Libére la mémoire automatiquement si true, sinon ne libère pas la mémoire de l'objet détaché
* Libére la mémoire automatiquement si destruct=true, voir JSONArray::detach
*/
void JSONArray_remove(JSONArray_t self, JSONObject_t obj, bool destruct);
/*! \brief Ajoute le JSONObject a la fin du tableau
* \param self Objet courant
* \param obj Objet a ajouter
*/
void JSONArray_add(JSONArray_t self, JSONObject_t obj);
/*! \brief Ajoute la valeur sous forme de JSONObject a la fin du tableau
* \param self Objet courant
* \param child Valeur a ajouter sous forme de JSONObject
*/
void JSONArray_addInt(JSONArray_t self, int child);
/*! \brief Ajoute la valeur sous forme de JSONObject a la fin du tableau
* \param self Objet courant
* \param child Valeur a ajouter sous forme de JSONObject
*/
void JSONArray_addDouble(JSONArray_t self, double child);
/*! \brief Ajoute la valeur sous forme de JSONObject a la fin du tableau
* \param self Objet courant
* \param child Valeur a ajouter sous forme de JSONObject
*/
void JSONArray_addString(JSONArray_t self, String_t child);
/*! \brief Ajoute la valeur sous forme de JSONObject a la fin du tableau
* \param self Objet courant
* \param child Valeur a ajouter sous forme de JSONObject
*/
void JSONArray_addBoolean(JSONArray_t self, bool child);
/*! \brief Detache tous les élements du tableau
* \param self Objet courant
* Ne libère pas la mémoire pour les objets détachés
*/
void JSONArray_clear(JSONArray_t self);
/*! \brief Voir JSONObject_assignArray() */
bool JSONArray_assignArray(JSONArray_t self, Vector_t arr);
/*! \brief Voir JSONObject_assignArrayOfObjects() */
bool JSONArray_assignArrayOfObjects(JSONArray_t self, Vector_t arr);
/*! \brief Voir JSONObject_equals() */
bool JSONArray_equals(JSONArray_t self, JSONObject_t obj);
/*! \brief Voir JSONObject_asVector() */
Vector_t JSONArray_asVector(JSONArray_t self);
#ifdef __cplusplus
}
#endif
#endif
