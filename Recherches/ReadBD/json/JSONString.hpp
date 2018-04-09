/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONString_HPP
#define JSONString_HPP
#include "JSONValue.hpp"
#include <string>
/*! \brief JSONString représente un objet string.
* Correspond a une chaine "" sous forme de texte dans une représentation JSON textuelle.
*/
class JSONString : public JSONValue
{
private:
        std::string value;
public:
        JSONString(std::string i=0);
        virtual ~JSONString();
        using JSONObject::getParent;
        using JSONObject::hasParent;
        virtual std::string asString(unsigned int tabs=0);
	/*! \brief Retourne la valeur de cet objet
	* \return Valeur de l'objet dans le type donné.
	*/
        std::string get();
	/*! \brief Modifie la valeur de cet objet
	* \param i Nouvelle valeur dans le type donné.
	*/
        void set(std::string i);
        virtual bool equals(JSONObject* obj);
        virtual void clear();
	virtual bool assign(JSONObject *obj);
	virtual bool assignArray(std::vector<JSONTuple>& arr);
        virtual std::string stringValue();
        virtual bool booleanValue();
        virtual int intValue();
        virtual double doubleValue();
};
#endif
