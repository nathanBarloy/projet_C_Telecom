/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONPOCO_HPP
#define JSONPOCO_HPP
#include "JSONObject.hpp"
#include "JSONPOCOBase.hpp"
/*! \brief JSONPOCO sert de base pour les classes devant hériter de JSONObject
* Toute classe devant être un JSONObject pour un fonctionnement similaire à du POJO en C++ doit hériter de JSONPOCO.
*/
class JSONPOCO : public JSONObject, public JSONPOCOBase
{
protected:
        using JSONObject::set;
        using JSONObject::get;
        using JSONObject::getInt;
        using JSONObject::getString;
        using JSONObject::getDouble;
        using JSONObject::getBoolean;
        using JSONObject::getArray;
        using JSONObject::clear;
        using JSONObject::remove;
        using JSONObject::detach;
        using JSONObject::detachAll;
        JSONPOCO();
        JSONPOCO(JSONObject *obj);
	virtual ~JSONPOCO();
        virtual int intValue(std::string name);
	virtual double doubleValue(std::string name);
	virtual bool booleanValue(std::string name);
        virtual std::string stringValue(std::string name);
	virtual std::string stringValue();
	virtual int intValue();
	virtual double doubleValue();
	virtual bool booleanValue();
};
#endif
