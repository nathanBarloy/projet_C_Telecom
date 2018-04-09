/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONTUPLE_HPP
#define JSONTUPLE_HPP
#include <string>
class JSONObject;
/*! \brief JSONTuple représente un couple de clé/valeur
*/
class JSONTuple
{
private:
        std::string name;
        JSONObject* obj;
public:
        JSONTuple();
	/*! \brief Construire un couple a partie d'une clé et d'une valeur
	* \param name Clé
	* \param obj valeur
	*/
        JSONTuple(std::string name, JSONObject* obj);
        JSONTuple(const JSONTuple& t);
	/*! \brief Retourne la valeur
	\return Valeur
	*/
        JSONObject* getObject();
	/*! \brief Retourne la valeur
	\return Valeur
	*/
        JSONObject* getValue();
	/*! \brief Défini la valeur
	\param obj Valeur
	*/
        void setObject(JSONObject* obj);
	/*! \brief Défini la valeur
	\param obj Valeur
	*/
        void setValue(JSONObject* obj);
	/*! \brief Retourne la clé
	\return Clé
	*/
        std::string getName();
	/*! \brief Retourne la clé
	\return Clé
	*/
        std::string getKey();
	/*! \brief Défini la clé
	\param obj Clé
	*/
        void setName(std::string name);
	/*! \brief Défini la clé
	\param obj Clé
	*/
        void setKey(std::string key);

};
#endif
