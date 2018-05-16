#ifndef JSONBOOLEAN_H
#define JSONBOOLEAN_H
#include "JSONValue.h"
#ifdef __cplusplus
#include <JSONAll.hpp>
extern "C"
{
#endif
/*! \brief Voir JSONObject_new()
* \param i Valeur par défaut
*/
JSONBoolean_t JSONBoolean_new(bool i);
/*! \brief Voir JSONObject_delete()
* \param self Objet concerné
* \return 0
*/
JSONBoolean_t JSONBoolean_delete(JSONBoolean_t self);
/*! \brief Voir JSONObject_getParent()
* \param self Objet concerné
* \return Objet parent
*/
JSONObject_t JSONBoolean_getParent(JSONBoolean_t self);
/*! \brief Voir JSONObject_hasParent()
* \param self Objet concerné
* \return True si l'objet à un parent, false sinon
*/
bool JSONBoolean_hasParent(JSONBoolean_t self);
/*! \brief Voir JSONObject_asString() */
AutoString_t JSONBoolean_asString(JSONBoolean_t self, unsigned int tabs);
/*! \brief Retoure la valeur du type demandé
* \param self Objet concerné
* \return Valeur de l'objet au type demandé
*/
bool JSONBoolean_get(JSONBoolean_t self);
/*! \brief Assigne la valeur du type demandé à l'objet JSON
* \param self Objet concerné
* \param i nouvelle valeur
*/
void JSONBoolean_set(JSONBoolean_t self, bool i);
/*! \brief Voir JSONObject_equals()
* \param self Objet concerné
* \param obj Second objet, a comparer.
* \return True si est identique au second.
*/
bool JSONBoolean_equals(JSONBoolean_t self, JSONObject_t obj);
/*! \brief Voir JSONObject_clear()
* \param self Objet concerné
* Remet l'objet a sa valeur par défaut
*/
void JSONBoolean_clear(JSONBoolean_t self);
/*! \brief Voir JSONObject_assign()
* \param self Objet concerné
* \param obj Objet à assigner.
* \return true si l'assignation réussi, false sinon.
* Tente d'assigner un objet à un autre.
*/
bool JSONBoolean_assign(JSONBoolean_t self, JSONObject_t obj);
/*! \brief Voir JSONObject_assignArray()
* \param self Objet concerné
* \param arr Tableau à assigner.
* \return true si l'assignation réussi, false sinon.
* Tente d'assigner un tableau à un objet JSON.
*/
bool JSONBoolean_assignArray(JSONBoolean_t self, Vector_t arr);
/*! \brief Voir JSONObject_intValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
int JSONBoolean_intValue(JSONBoolean_t self);
/*! \brief Voir JSONObject_doubleValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
double JSONBoolean_doubleValue(JSONBoolean_t self);
/*! \brief Voir JSONObject_booleanValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
bool JSONBoolean_booleanValue(JSONBoolean_t self);


/*! \brief Obtenir une copie de l'objet
*
* \param obj Objet à copier
* Retourne une copie de l'objet
*/
JSONBoolean_t JSONBoolean_getCopy(JSONBoolean_t obj);
#ifdef __cplusplus
}
#endif
#endif
