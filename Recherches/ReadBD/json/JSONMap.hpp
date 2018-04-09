/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONMAP_HPP
#define JSONMAP_HPP
#include <map>
#include <string>
#include <vector>
#define JSONMapIterator std::map<std::string, JSONObject*>::iterator
//#include "JSONObject.hpp"
//#include "JSONTuple.hpp"
class JSONObject;
class JSONTuple;
class JSONMap
{
private:
	std::map<std::string, JSONObject*> map;
public:
	JSONMap();
	~JSONMap();
	void set(std::string name, JSONObject* obj);
	JSONObject* get(std::string name);
	std::string get(JSONObject* obj);
	void remove(JSONObject* obj);
	void remove(std::string name);
	size_t size();
	void clear();
	std::vector<JSONTuple> asVector();
};
#endif
