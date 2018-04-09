/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONVALUE_HPP
#define JSONVALUE_HPP
#include "JSONObject.hpp"
#include "JSONTuple.hpp"
#include <string>
/*! \brief JSONValue représente un valeur en JSON.
* Cette classe sert de tronc commun a toutes les valeurs en JSON.
*/
class JSONValue : public JSONObject
{
protected:
        JSONValue();
        virtual ~JSONValue();
        using JSONObject::set;
        using JSONObject::get;
        using JSONObject::asVector;
        using JSONObject::getInt;
        using JSONObject::getString;
        using JSONObject::getDouble;
        using JSONObject::getBoolean;
        using JSONObject::getArray;
        using JSONObject::remove;
        using JSONObject::detach;
        using JSONObject::detachAll;
	using JSONObject::newParent;
public:
        virtual std::string asString(unsigned int tabs=0);
        virtual std::vector<JSONTuple> asVector();
};
#endif
