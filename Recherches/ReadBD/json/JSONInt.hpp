/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONINT_HPP
#define JSONINT_HPP
#include "JSONValue.hpp"
#include <string>
/*! \brief JSONInt représente un objet integer.
* Correspond a un nombre entier sous forme de texte dans une représentation JSON textuelle.
*/
class JSONInt : public JSONValue
{
private:
        int value;
public:
        JSONInt(int i=0);
        virtual ~JSONInt();
        using JSONObject::getParent;
        using JSONObject::hasParent;
        virtual std::string asString(unsigned int tabs=0);
	/*! \brief Retourne la valeur de cet objet
	* \return Valeur de l'objet dans le type donné.
	*/
        int get();
	/*! \brief Modifie la valeur de cet objet
	* \param i Nouvelle valeur dans le type donné.
	*/
        void set(int i);
        virtual bool equals(JSONObject* obj);
        virtual void clear();
	virtual bool assign(JSONObject *obj);
	virtual bool assignArray(std::vector<JSONTuple>& arr);
        virtual int intValue();
	virtual double doubleValue();
	virtual bool booleanValue();
};
#endif
