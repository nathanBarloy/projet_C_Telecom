#ifndef SERVERUNNER_H
#define SERVERUNNER_H
#include "../utils/BDD.h"
int global_serverRunnerContinue(int set, int nvalue);
void signal_serverRunner(int signal);
int serverRunner(BDD bdd);
void startInfos(BDD bdd);//Affiche les informations de démarrage, et vérifie l'intégrité
#endif
