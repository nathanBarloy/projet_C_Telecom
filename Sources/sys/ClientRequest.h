#ifndef CLIENT_REQUEST_H
#define CLIENT_REQUEST_H
#include "RequestTypes.h"
int clientRequest_error;
RequestAnswer clientRequest(const char* addr_s, RequestQuery query);
RequestAnswer clientRequestGetAnswer(int sock, RequestQuery query);
#endif
