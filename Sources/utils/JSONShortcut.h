#ifndef JSONSHORTCUT_H
#define JSONSHORTCUT_H
#include <String/String.h>
#include <JSONAll.h>

#define cStringValueOf(obj, key) cString(JSONObject_stringValueOf(obj, autoString(key)))
#define cStringValue(obj) cString(JSONObject_stringValueOf(obj))

#define ValueOf(obj, key, type) JSONObject_ ## type ## ValueOf(obj, autoString(key))
#define Value(obj, type) JSONObject_ ## type ## ValueOf(obj)
#endif
