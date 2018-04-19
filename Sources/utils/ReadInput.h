#ifndef READ_INPUT_H
#define READ_INPUT_H
#include <String/String.h>
#include <String/AutoString.h>
String_t ReadInput();//Utilise autoString
String_t ReadInputWithMsg(String_t dsp);
String_t Recognize(Vector_t propositions, String_t word);
String_t StandardPrompt(Vector_t propositions);
void clearTerminal();
#endif
