#ifndef CLIENT_RUNNER
#define CLIENT_RUNNER
#include "../utils/PthreadShortcut.h"
#include "RequestTypes.h"
#include "../utils/Connexion.h"
#include "ClientRunnerTypes.h"
// #include <ncurses.h>
// #include <cdk/cdk.h>

int clientRunner(Connexion_t connexion);
#endif
