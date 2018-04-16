#ifndef CLIENT_RUNNER
#define CLIENT_RUNNER
#include <pthread.h>
#include "../utils/PthreadShortcut.h"
#include "RequestTypes.h"
struct ClientSock
{
	int sock;
	pthread_mutex_t mutex;
};
typedef struct ClientSock* ClientSock_t;
ClientSock_t newClientSock(int sock);
ClientSock_t freeClientSock(ClientSock_t clientSock);
int clientRunner(ClientSock_t clientSock);

int global_clientRunnerContinue(int set, int nvalue);
void signal_clientRunner(int signal);
#endif
