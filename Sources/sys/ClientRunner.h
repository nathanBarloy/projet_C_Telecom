#ifndef CLIENT_RUNNER
#define CLIENT_RUNNER
#include <pthread.h>
#include "../utils/PthreadShortcut.h"
#include "RequestTypes.h"
#include "../utils/Connexion.h"
// #include <ncurses.h>
// #include <cdk/cdk.h>
int clientRunner(Connexion_t connexion);

int global_clientRunnerContinue(int set, int nvalue);
void signal_clientRunner(int signal);
void initClient();
#endif
