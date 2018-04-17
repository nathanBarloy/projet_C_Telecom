#ifndef CLIENT_RUNNER
#define CLIENT_RUNNER
#include <pthread.h>
#include "../utils/PthreadShortcut.h"
#include "RequestTypes.h"

int clientRunner();

int global_clientRunnerContinue(int set, int nvalue);
void signal_clientRunner(int signal);
void initClient();
#endif
