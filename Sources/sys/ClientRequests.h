#ifndef CLIENT_REQUESTS_H
#define CLIENT_REQUESTS_H
#include "RequestTypes.h"
#include <JSONAll.h>
#include "../utils/Connexion.h"
void prints(Connexion_t connexion, String_t message);
RequestAnswer Client_RegisterUser(Connexion_t connexion, JSONObject_t user);
#endif
