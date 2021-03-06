#ifndef CLIENT_RUNNER_MAIN_MENU_H
#define CLIENT_RUNNER_MAIN_MENU_H
#include "../utils/Connexion.h"
#include "ClientRunnerTypes.h"
#include <String/String.h>
#include <String/AutoString.h>
#include <stdio.h>
#include "../utils/JSONShortcut.h"
enum ClientRunnerMode ClientRunner_MainMenu(Connexion_t connexion);
enum ClientRunnerMode ClientRunner_ShowFilms(Connexion_t connexion);
void ClientRunner_showFilm(Connexion_t connexion, int id);
void ClientRunner_export(JSONObject_t e);
void ClientRunner_noter(Connexion_t connexion, int id);
enum ClientRunnerMode ClientRunner_ShowMyFilms(Connexion_t connexion);
enum ClientRunnerMode ClientRunner_ShowTrends(Connexion_t connexion);
enum ClientRunnerMode ClientRunner_ShowRandom(Connexion_t connexion);
enum ClientRunnerMode ClientRunner_ShowRecommendations(Connexion_t connexion);
#endif
