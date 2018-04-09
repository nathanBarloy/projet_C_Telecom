/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONNULL_HPP
#define JSONNULL_HPP
#include "JSONInt.hpp"
#include <string>
/*! \brief JSONNull représente un objet null.
* Correspond a null sous forme de texte dans une représentation JSON textuelle.
*/
class JSONNull : public JSONInt
{
private:
        using JSONInt::set;
public:
        JSONNull();
        virtual ~JSONNull();
        virtual std::string asString(unsigned int tabs=0);
        virtual bool equals(JSONObject* obj);
        virtual void clear();
	virtual bool assign(JSONObject *obj);
	virtual bool assignArray(std::vector<JSONTuple>& arr);
};
#endif
