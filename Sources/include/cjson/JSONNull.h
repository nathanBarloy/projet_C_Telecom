#ifndef JSONNULL_H
#define JSONNULL_H
#include "JSONValue.h"
#ifdef __cplusplus
#include <JSONAll.hpp>
extern "C"
{
#endif
/*! \brief Voir JSONObject_new() */
JSONNull_t JSONNull_new();
/*! \brief Voir JSONObject_delete()
* \param self Objet concerné
* \return 0
*/
JSONNull_t JSONNull_delete(JSONNull_t self);
/*! \brief Voir JSONObject_getParent()
* \param self Objet concerné
* \return Objet parent
*/
JSONObject_t JSONNull_getParent(JSONNull_t self);
/*! \brief Voir JSONObject_hasParent()
* \param self Objet concerné
* \return True si l'objet à un parent, false sinon
*/
bool JSONNull_hasParent(JSONNull_t self);
/*! \brief Voir JSONObject_asString() */
AutoString_t JSONNull_asString(JSONNull_t self, unsigned int tabs);
/*! \brief Voir JSONObject_equals()
* \param self Objet concerné
* \param obj Second objet, a comparer.
* \return True si est identique au second.
*/
bool JSONNull_equals(JSONNull_t self, JSONObject_t obj);
/*! \brief Voir JSONObject_clear()
* \param self Objet concerné
* Remet l'objet a sa valeur par défaut
*/
void JSONNull_clear(JSONNull_t self);
/*! \brief Voir JSONObject_assign()
* \param self Objet concerné
* \param obj Objet à assigner.
* \return true si l'assignation réussi, false sinon.
* Tente d'assigner un objet à un autre.
*/
bool JSONNull_assign(JSONNull_t self, JSONObject_t obj);
/*! \brief Voir JSONObject_assignArray()
* \param self Objet concerné
* \param arr Tableau à assigner.
* \return true si l'assignation réussi, false sinon.
* Tente d'assigner un tableau à un objet JSON.
*/
bool JSONNull_assignArray(JSONNull_t self, Vector_t arr);
#ifdef __cplusplus
}
#endif
#endif
