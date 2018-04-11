#ifndef JSONINT_H
#define JSONINT_H
#include "JSONValue.h"
#ifdef __cplusplus
#include <JSONAll.hpp>
extern "C"
{
#endif
/*! \brief Voir JSONObject_new()
* \param i Valeur par défaut
*/
JSONInt_t JSONInt_new(int i);
/*! \brief Voir JSONObject_delete()
* \param self Objet concerné
* \return 0
*/
JSONInt_t JSONInt_delete(JSONInt_t self);
/*! \brief Voir JSONObject_getParent()
* \param self Objet concerné
* \return Objet parent
*/
JSONObject_t JSONInt_getParent(JSONInt_t self);
/*! \brief Voir JSONObject_hasParent()
* \param self Objet concerné
* \return True si l'objet à un parent, false sinon
*/
bool JSONInt_hasParent(JSONInt_t self);
/*! \brief Voir JSONObject_asString() */
String_t JSONInt_asString(JSONInt_t self, unsigned int tabs);
/*! \brief Retoure la valeur du type demandé
* \param self Objet concerné
* \return Valeur de l'objet au type demandé
*/
int JSONInt_get(JSONInt_t self);
/*! \brief Assigne la valeur du type demandé à l'objet JSON
* \param self Objet concerné
* \param i nouvelle valeur
*/
void JSONInt_set(JSONInt_t self, int i);
/*! \brief Voir JSONObject_equals()
* \param self Objet concerné
* \param obj Second objet, a comparer.
* \return True si est identique au second.
*/
bool JSONInt_equals(JSONInt_t self, JSONObject_t obj);
/*! \brief Voir JSONObject_clear()
* \param self Objet concerné
* Remet l'objet a sa valeur par défaut
*/
void JSONInt_clear(JSONInt_t self);
/*! \brief Voir JSONObject_assign()
* \param self Objet concerné
* \param obj Objet à assigner.
* \return true si l'assignation réussi, false sinon.
* Tente d'assigner un objet à un autre.
*/
bool JSONInt_assign(JSONInt_t self, JSONObject_t obj);
/*! \brief Voir JSONObject_assignArray()
* \param self Objet concerné
* \param arr Tableau à assigner.
* \return true si l'assignation réussi, false sinon.
* Tente d'assigner un tableau à un objet JSON.
*/
bool JSONInt_assignArray(JSONInt_t self, Vector_t arr);
/*! \brief Voir JSONObject_intValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
int JSONInt_intValue(JSONInt_t self);
/*! \brief Voir JSONObject_doubleValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
double JSONInt_doubleValue(JSONInt_t self);
/*! \brief Voir JSONObject_booleanValue()
* \param self Objet concerné
* \return Type demandé par conversion
*/
bool JSONInt_booleanValue(JSONInt_t self);
#ifdef __cplusplus
}
#endif
#endif
