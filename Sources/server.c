#include <JSONAll.h>
#include <String/AutoString.h>
#include "utils/BDD.h"
#include "utils/Distance.h"
#include "utils/Distance_utilisateur.h"
#include "sys/ServerRunner.h"
#include <time.h>

int main()
{
	printf("Démarre du programme...\nChargement de la base de données...\n");
	srand(time(0));
	BDD bdd = BDD_load();
	//printf("%s\n", cString(JSONObject_asString(bdd->json, 0)));//Afficher la BDD lue
	/*printf("Sauvegarde...");//Test
	int a = JSONParser_saveFile(bdd->json, "data/test.json");
	printf("Code de retour: %d\n", a);*/
	//printf("Export:\n");//Test
	//printf("%s\n", cString(JSONObject_asString(JSONObject_get(bdd->json, autoString("Users")), 0)));

	/*
	//JE ME REPETE: NE PAS METTRE VOS TESTS UNITAIRES DANS LE MAIN DU SERVEUR
	Vector_t listeFilms = liste_recommandation(bdd,0);
	int i;
	for (i=0;i<10;i++) {
		printf("%s\n",cString(JSONObject_asString(getFromVector(listeFilms,i), 0)));
	}
	freeVector(listeFilms);*/
	int r = serverRunner(bdd);
	printf("Le serveur à terminé avec le code: %d\n", r);
	if(r >= 0)
	{
		printf("Sauvegarde de la base de données...\n");
		r = BDD_save(bdd);
		if(r)
		{
			printf("Base de données sauvegardée.\n");
		}
		else
		{
			printf("Une erreur est survenue lors de l'enregistrement de la base de données !\n");
		}
	}
	else
	{
		printf("Une erreur est survenue pendant l'execution du serveur.\nLa base de donnée n'a pas été sauvegardée suite à l'arrêt d'urgence du serveur.\n");
	}
	BDD_free(bdd);
	freeAutoString();
	return 0;
}
