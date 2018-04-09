/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONBOOLEAN_HPP
#define JSONBOOLEAN_HPP
#include "JSONValue.hpp"
#include <string>
/*! \brief JSONBoolean représente un objet booleen.
* Correspond a true ou false sous forme de texte dans une représentation JSON textuelle.
*/
class JSONBoolean : public JSONValue
{
private:
        bool value;
public:
        JSONBoolean(bool i=false);
        virtual ~JSONBoolean();
        using JSONObject::getParent;
        using JSONObject::hasParent;
        virtual std::string asString(unsigned int tabs=0);
	/*! \brief Retourne la valeur de cet objet
	* \return Valeur de l'objet dans le type donné.
	*/
        bool get();
	/*! \brief Modifie la valeur de cet objet
	* \param i Nouvelle valeur dans le type donné.
	*/
        void set(bool i);
        virtual bool equals(JSONObject* obj);
        virtual void clear();
	virtual bool assign(JSONObject *obj);
	virtual bool assignArray(std::vector<JSONTuple>& arr);
        virtual int intValue();
	virtual double doubleValue();
	virtual bool booleanValue();
};
#endif
