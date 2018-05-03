#include "JSONCheck.h"
#include <String/AutoString.h>
#include "JSONShortcut.h"
bool JSON_rightTypeOrNull(JSONObject_t obj, JSONType_t type)
{
	if(obj == 0)
	{
		return true;
	}
	else if(JSONObject_getType(obj) == NULLOBJ)
	{
		return true;
	}
	else if(JSONObject_getType(obj) == type)
	{
		return true;
	}
	return false;
}
bool JSON_rightTypeNotNull(JSONObject_t obj, JSONType_t type)
{
	if(obj == 0)
	{
		return false;
	}
	else if(JSONObject_getType(obj) == type)
	{
		return true;
	}
	return false;
}
bool JSON_checkBasicArray(JSONArray_t arr, JSONType_t type)
{
	size_t c = 0, size;
	bool validType = (arr != 0) && (JSONObject_getType(arr) == ARRAY);
	if(validType)
	{
		size = JSONArray_size(arr);
		while(validType && c < size)
		{
			validType = validType && (JSONObject_getType(JSONArray_get(arr, c)) == type);
			++c;
		}
	}
	return validType;
}
bool JSON_checkUser(JSONObject_t user, bool light)
{
	bool validType = (JSONObject_getType(user) == OBJECT);
	if(validType)
	{
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(user, AS("Name")), STRING);
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(user, AS("FirstName")), STRING);
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(user, AS("Login")), STRING);
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(user, AS("Password")), STRING);
		validType = validType && JSON_checkDate(JSONObject_get(user, AS("Birth")));
		if(!light)
		{
			//Ajouter les autres vérifications pour Preferences et History
			validType = validType && JSON_rightTypeNotNull(JSONObject_get(user, AS("Id")), INT);
		}
	}
	return validType;
}
bool JSON_checkFilm(JSONObject_t film)
{
	bool validType = (JSONObject_getType(film) == OBJECT);
	if(validType)
	{
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(film, AS("Id")), INT);
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(film, AS("Duration")), INT);
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(film, AS("Year")), INT);
		validType = validType && JSON_rightTypeNotNull(JSONObject_get(film, AS("Title")), STRING);
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(film, AS("Type")), STRING);
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(film, AS("Description")), STRING);
		validType = validType && JSON_checkBasicArray(JSONObject_get(film, AS("Actors")), STRING);
		validType = validType && JSON_checkBasicArray(JSONObject_get(film, AS("Directors")), STRING);
		validType = validType && JSON_checkBasicArray(JSONObject_get(film, AS("Genres")), STRING);
	}
	return validType;
}
bool JSON_checkDate(JSONObject_t d)
{
	bool validType = (JSONObject_getType(d) == OBJECT);
	if(validType)
	{
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(d, AS("Day")), INT);
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(d, AS("Month")), INT);
		validType = validType && JSON_rightTypeOrNull(JSONObject_get(d, AS("Year")), INT);
	}
	return false;
}
