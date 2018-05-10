#ifndef REPLACE_H
#define REPLACE_H
#include <stddef.h>
#include <String/String.h>
#include <JSONAll.h>
void replace(char* str, char oc, char nc);
int getFirstChar(String_t str, char c);
void transformValue(String_t str);//Remplace les valeurs hexa des adresses http par des caractères
#endif
