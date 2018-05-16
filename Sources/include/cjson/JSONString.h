#ifndef JSONSTRING_H
#define JSONSTRING_H
#include "JSONValue.h"
#ifdef __cplusplus
#include <JSONAll.hpp>
extern "C"
{
#endif
/*! \brief Voir JSONObject_new()
* \param i Valeur par défaut
*/
JSONString_t JSONString_new(String_t i);
/*! \brief Voir JSONObject_delete()
* \param self Objet concerné
* \return 0
*/
JSONString_t JSONString_delete(JSONString_t self);
/*! \brief Voir JSONObject_getParent()
* \param self Objet concerné
* \return Objet parent
*/
JSONObject_t JSONString_getParent(JSONString_t self);
/*! \brief Voir JSONObject_hasParent()
* \param self Objet concerné
* \return True si l'objet à un parent, false sinon
*/
bool JSONString_hasParent(JSONString_t self);
/*! \brief Voir JSONObject_asString() */
AutoString_t JSONString_asString(JSONString_t self, unsigned int tabs);
/*! \brief Retoure la valeur du type demandé
* \param self Objet concerné
* \return Valeur de l'objet au type demandé
*/
AutoString_t JSONString_get(JSONString_t self);
/*! \brief Assigne la valeur du type demandé à l'objet JSON
* \param self Objet concerné
* \param i nouvelle valeur
*/
void JSONString_set(JSONString_t self, String_t i);
/*! \brief Voir JSONObject_equals()
* \param self Objet concerné
* \param obj Second objet, a comparer.
* \return True si est identique au second.
*/
bool JSONString_equals(JSONString_t self, JSONObject_t obj);
/*! \brief Voir JSONObject_clear()
* \param self Objet concerné
* Remet l'objet a sa valeur par défaut
*/
void JSONString_clear(JSONString_t self);
/*! \brief Voir JSONObject_assign()
* \param self Objet concerné
* \param obj Objet à assigner.
* \return true si l'assignation réussi, false sinon.
* Tente d'assigner un objet à un autre.
*/
bool JSONString_assign(JSONString_t self, JSONObject_t obj);
/*! \brief Voir JSONObject_assignArray()
* \param self Objet concerné
* \param arr Tableau à assigner.
* \return true si l'assignation réussi, false sinon.
* Tente d'assigner un tableau à un objet JSON.
*/
bool JSONString_assignArray(JSONString_t self, Vector_t arr);
/*! \brief Voir JSONObject_intValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
int JSONString_intValue(JSONString_t self);
/*! \brief Voir JSONObject_doubleValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
double JSONString_doubleValue(JSONString_t self);
/*! \brief Voir JSONObject_booleanValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
bool JSONString_booleanValue(JSONString_t self);

/*! \brief Obtenir une copie de l'objet
*
* \param obj Objet à copier
* Retourne une copie de l'objet
*/
JSONString_t JSONString_getCopy(JSONString_t obj);
#ifdef __cplusplus
}
#endif
#endif
