#ifndef CLIENT_REQUEST_H
#define CLIENT_REQUEST_H
#include "RequestTypes.h"
#include "../utils/Connexion.h"
int clientRequest_error;
RequestAnswer clientRequest(Connexion_t connexion, RequestQuery query);
RequestAnswer clientRequestGetAnswer(int sock, RequestQuery query);
#endif
