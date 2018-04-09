/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONDOUBLE_HPP
#define JSONDOUBLE_HPP
#include "JSONValue.hpp"
#include <string>
/*! \brief JSONDouble représente un objet double.
* Correspond a un nombre décimal sous forme de texte dans une représentation JSON textuelle.
*/
class JSONDouble : public JSONValue
{
private:
        double value;
public:
        JSONDouble(double i=0);
        virtual ~JSONDouble();
        using JSONObject::getParent;
        using JSONObject::hasParent;
        virtual std::string asString(unsigned int tabs=0);
	/*! \brief Retourne la valeur de cet objet
	* \return Valeur de l'objet dans le type donné.
	*/
        double get();
	/*! \brief Modifie la valeur de cet objet
	* \param i Nouvelle valeur dans le type donné.
	*/
        void set(double i);
        virtual bool equals(JSONObject* obj);
        virtual void clear();
	virtual bool assign(JSONObject *obj);
	virtual bool assignArray(std::vector<JSONTuple>& arr);
        virtual int intValue();
	virtual double doubleValue();
	virtual bool booleanValue();
};
#endif
