/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONPOCOARRAY_HPP
#define JSONPOCOARRAY_HPP
#include "JSONArray.hpp"
#include "JSONPOCOBase.hpp"
/*! \brief JSONArray sert de base pour les classes devant hériter de JSONArray
* Toute classe devant être un JSONArray pour un fonctionnement similaire à du POJO en C++ doit hériter de JSONPOCOArray.
*/
class JSONPOCOArray : public JSONArray, public JSONPOCOBase
{
protected:
        using JSONArray::set;
        using JSONArray::get;
        using JSONArray::getInt;
        using JSONArray::getString;
        using JSONArray::getDouble;
        using JSONArray::getBoolean;
        using JSONArray::getArray;
        using JSONArray::add;
        using JSONArray::remove;
        using JSONArray::clear;
        using JSONArray::detach;
        using JSONArray::detachAll;
        JSONPOCOArray();
        JSONPOCOArray(JSONObject *obj);
        virtual std::string stringValue(unsigned int n);
	virtual int intValue(unsigned int n);
	virtual double doubleValue(unsigned int n);
	virtual bool booleanValue(unsigned int n);
        virtual int intValue(std::string name);
	virtual double doubleValue(std::string name);
	virtual bool booleanValue(std::string name);
	virtual std::string stringValue();
	virtual int intValue();
	virtual double doubleValue();
	virtual bool booleanValue();
        virtual std::string stringValue(std::string name);

};
#endif
