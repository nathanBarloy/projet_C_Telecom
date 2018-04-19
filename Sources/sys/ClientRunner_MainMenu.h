#ifndef CLIENT_RUNNER_MAIN_MENU_H
#define CLIENT_RUNNER_MAIN_MENU_H
#include "../utils/Connexion.h"
#include "ClientRunnerTypes.h"
#include <String/String.h>
#include <String/AutoString.h>
#include <stdio.h>
#include "../utils/JSONShortcut.h"
enum ClientRunnerMode ClientRunner_MainMenu(Connexion_t connexion);
#endif
