#include <JSONAll.h>
#include <String/AutoString.h>
#include "utils/BDD.h"
#include "utils/Distance.h"
#include "utils/Distance_utilisateur.h"

int main()
{
	printf("Démarre du programme...\nChargement de la base de données...\n");
	BDD bdd = BDD_load();
	//printf("%s\n", cString(JSONObject_asString(bdd->json, 0)));//Afficher la BDD lue
	/*printf("Sauvegarde...");//Test
	int a = JSONParser_saveFile(bdd->json, "data/test.json");
	printf("Code de retour: %d\n", a);*/
	//printf("Export:\n");//Test
	//printf("%s\n", cString(JSONObject_asString(JSONObject_get(bdd->json, autoString("Users")), 0)));
	double dist = distance_film(bdd,1,1);
	double dist_users = distance_users(bdd,0,1);
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
