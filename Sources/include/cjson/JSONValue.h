#ifndef JSONVALUE_H
#define JSONVALUE_H
#include "JSONObject.h"
#include <String/String.h>
#include <Vector/Vector.h>
#include <String/AutoString.h>
#ifdef __cplusplus
#include <JSONAll.hpp>
extern "C"
{
#endif
/*! \brief Voir JSONObject_asString() */
String_t JSONValue_asString(JSONValue_t self, unsigned int tabs);
/*! \brief Voir JSONObject_asVector() */
Vector_t JSONValue_asVector(JSONValue_t self);
#ifdef __cplusplus
}
#endif
#endif
