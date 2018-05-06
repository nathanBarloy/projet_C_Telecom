#ifndef CLIENT_RUNNER_LOGIN_H
#define CLIENT_RUNNER_LOGIN_H
#include "../utils/Connexion.h"
#include "ClientRunnerTypes.h"
#include <String/String.h>
#include <String/AutoString.h>
#include <stdio.h>
#include "../utils/JSONShortcut.h"
enum ClientRunnerMode ClientRunner_Login(Connexion_t connexion);
enum ClientRunnerMode ClientRunner_Logout(Connexion_t connexion);
enum ClientRunnerMode ClientRunner_Register(Connexion_t connexion);
#endif
