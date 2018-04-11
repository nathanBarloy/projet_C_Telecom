#ifndef JSONDOUBLE_H
#define JSONDOUBLE_H
#include "JSONValue.h"
#ifdef __cplusplus
#include <JSONAll.hpp>
extern "C"
{
#endif
/*! \brief Voir JSONObject_new()
* \param i Valeur par défaut
*/
JSONDouble_t JSONDouble_new(double i);
/*! \brief Voir JSONObject_delete()
* \param self Objet concerné
* \return 0
*/
JSONDouble_t JSONDouble_delete(JSONDouble_t self);
/*! \brief Voir JSONObject_getParent()
* \param self Objet concerné
* \return Objet parent
*/
JSONObject_t JSONDouble_getParent(JSONDouble_t self);
/*! \brief Voir JSONObject_hasParent()
* \param self Objet concerné
* \return True si l'objet à un parent, false sinon
*/
bool JSONDouble_hasParent(JSONDouble_t self);
/*! \brief Voir JSONObject_asString() */
String_t JSONDouble_asString(JSONDouble_t self, unsigned int tabs);
/*! \brief Retoure la valeur du type demandé
* \param self Objet concerné
* \return Valeur de l'objet au type demandé
*/
double JSONDouble_get(JSONDouble_t self);
/*! \brief Assigne la valeur du type demandé à l'objet JSON
* \param self Objet concerné
* \param i nouvelle valeur
*/
void JSONDouble_set(JSONDouble_t self, double i);
/*! \brief Voir JSONObject_equals()
* \param self Objet concerné
* \param obj Second objet, a comparer.
* \return True si est identique au second.
*/
bool JSONDouble_equals(JSONDouble_t self, JSONObject_t obj);
/*! \brief Voir JSONObject_clear()
* \param self Objet concerné
* Remet l'objet a sa valeur par défaut
*/
void JSONDouble_clear(JSONDouble_t self);
/*! \brief Voir JSONObject_assign()
* \param self Objet concerné
* \param obj Objet à assigner.
* \return true si l'assignation réussi, false sinon.
* Tente d'assigner un objet à un autre.
*/
bool JSONDouble_assign(JSONDouble_t self, JSONObject_t obj);
/*! \brief Voir JSONObject_assignArray()
* \param self Objet concerné
* \param arr Tableau à assigner.
* \return true si l'assignation réussi, false sinon.
* Tente d'assigner un tableau à un objet JSON.
*/
bool JSONDouble_assignArray(JSONDouble_t self, Vector_t arr);
/*! \brief Voir JSONObject_intValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
int JSONDouble_intValue(JSONDouble_t self);
/*! \brief Voir JSONObject_doubleValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
double JSONDouble_doubleValue(JSONDouble_t self);
/*! \brief Voir JSONObject_booleanValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
bool JSONDouble_booleanValue(JSONDouble_t self);
#ifdef __cplusplus
}
#endif
#endif
