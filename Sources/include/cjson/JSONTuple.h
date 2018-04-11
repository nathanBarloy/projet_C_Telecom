#ifndef JSONTUPLE_H
#define JSONTUPLE_H
#include <String/String.h>
#include <String/AutoString.h>

struct JSONTuple_s
{
	String_t name;
	void* obj;
};
typedef struct JSONTuple_s* JSONTuple_t;
#ifdef __cplusplus
extern "C"
{
#endif
/*! \brief Alloue un nouveau JSONTuple_s
* \return Adresse du pointeur*/
JSONTuple_t newJSONTuple();
/*! \brief Alloue un nouveau JSONTuple_s avec des données
* \param name Nom de la clé
* \param obj JSONObject_t représentant la valeur
* \return Adresse du pointeur*/
JSONTuple_t newJSONTupleFull(String_t name, void* obj);
/*! \brief Libérer un JSONTuple
* \param tuple Objet à libérer
* \return 0*/
JSONTuple_t freeJSONTuple(JSONTuple_t tuple);
/*! \brief Libérer un JSONTuple et libérer le pointeur associé a la valeur
* \param tuple Objet à libérer
* \return 0*/
JSONTuple_t freeJSONTupleWithPtr(JSONTuple_t tuple);
/*! \brief Obtenir le nom de la clé du tuple
* \param tuple Tuple concerné
* \return Clé */
String_t getJSONTupleName(JSONTuple_t tuple);
/*! \brief Obtenir le nom de la clé du tuple
* \param tuple Tuple concerné
* \return Clé */
String_t getJSONTupleKey(JSONTuple_t tuple);
/*! \brief Obtenir la valeur de la clé du tuple
* \param tuple Tuple concerné
* \return Valeur */
void* getJSONTupleObject(JSONTuple_t tuple);
/*! \brief Obtenir la valeur de la clé du tuple
* \param tuple Tuple concerné
* \return Valeur */
void* getJSONTupleValue(JSONTuple_t tuple);
/*! \brief Définir le nom de la clé du tuple
* \param tuple Tuple concerné
* \param name Clé */
void setJSONTupleName(JSONTuple_t tuple, String_t name);
/*! \brief Définir le nom de la clé du tuple
* \param tuple Tuple concerné
* \param name Clé */
void setJSONTupleKey(JSONTuple_t tuple, String_t name);
/*! \brief Définir la valeur de la clé du tuple
* \param tuple Tuple concerné
* \param obj Valeur */
void setJSONTupleValue(JSONTuple_t tuple, void* obj);
/*! \brief Définir la valeur de la clé du tuple
* \param tuple Tuple concerné
* \param obj Valeur */
void setJSONTupleObject(JSONTuple_t tuple, void* obj);
#ifdef __cplusplus
}
#endif
#endif
