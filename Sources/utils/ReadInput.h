#ifndef READ_INPUT_H
#define READ_INPUT_H
#include <String/String.h>
#include <String/AutoString.h>
#include "Date.h"
AutoString_t ReadInput();//Utilise autoString
AutoString_t ReadInputWithMsg(String_t dsp);
AutoString_t ReadPassword();
AutoString_t ReadPasswordWithMsg(String_t dsp);
AutoString_t Recognize(Vector_t propositions, String_t word);
AutoString_t StandardPrompt(Vector_t propositions);
Date_t ReadDate();
Date_t ReadDateWithMsg(String_t dsp);
void clearTerminal();
#endif
