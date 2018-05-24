#include "Distance_utilisateur.h"

//récupérer les JSON HistoryRates des deux utilisateurs puis de réaliser la corrélation de Pearson pour en déduire la distance entre les deux utilisateurs
double distance_users(BDD bdd, int id1, int id2)
{
	JSONObject_t user1 = BDD_getUserById(bdd, id1);
	JSONObject_t user2 = BDD_getUserById(bdd, id2);
	if(user1 == 0 || user2 == 0)
	{
		return -1;
	}
	else
	{
		//printf("%s\n", cString(JSONObject_asString(users2, 0)));
		JSONObject_t histo1 = JSONObject_get(user1, autoString("History"));
		JSONObject_t histo2 = JSONObject_get(user2, autoString("History"));
		//printf("%s\n", cString(JSONObject_asString(histo1, 0)));
		if(histo1 == 0 || histo2 == 0)
		{
			return -1;
		}
		else
		{
			JSONArray_t history_rates1 = JSONObject_getArray(histo1, autoString("Rates"));
			JSONArray_t history_rates2 = JSONObject_getArray(histo2, autoString("Rates"));
			if(history_rates1 == 0 || history_rates2 == 0)
			{
				return -1;
			}
			else{
				double resultat = pearson_correlation(history_rates1, history_rates2);
				return resultat;
			}
		}
		//printf("les utilisateurs %d et %d ont une distance de %f (à partir de la corrélation de Pearson)\n", id1, id2, resultat);

	}
}

//calcul de la moyenne des notes d'un utilisateur
double mean_rates(JSONArray_t history_rates)
{
	int i;
	int total = JSONArray_size(history_rates);
	int somme = 0;
	for (i = 0 ; i < total ; i++)
	{
		//printf("ID du film : %d\n", JSONObject_intValueOf(JSONArray_get(history_rates, i), autoString("Id")) );
		//printf("Note du film : %d\n", JSONObject_intValueOf(JSONArray_get(history_rates, i), autoString("Rate")));
		somme = somme + JSONObject_intValueOf(JSONArray_get(history_rates, i), autoString("Rate"));
	}
	double resultat = (double)(somme)/(double)total;
	//printf("La moyenne est de %f\n", resultat);
	return resultat;
}


//calcul de la corréalation de Pearson : on ne prend pas en compte ici les films non notés par les deux utilisateurs.
double pearson_correlation(JSONArray_t hr1, JSONArray_t hr2) {
	double numerateur = 0.0;
	double denominateur1 = 0.0;
	double denominateur2 = 0.0;
	//printf("%s\n", cString(JSONObject_asString(hr1, 0)));
	double mean_rates1 = mean_rates(hr1);
	double mean_rates2 = mean_rates(hr2);
	printf("TOTO2\n");
	//printf("moyenne 1 : %f\n moyenne 2 : %f \n", mean_rates1, mean_rates2);
	int i;
	int pos1;
	int pos2;
	for(i = 0 ; i < JSONArray_size(hr1) ; i++) {
		int id = JSONObject_intValueOf(JSONArray_get(hr1, i), autoString("Id"));
		pos2 = get_position(hr2, i);
		if(pos2 != -1) {
			numerateur = numerateur + (JSONObject_intValueOf(JSONArray_get(hr1, i), autoString("Rate"))-mean_rates1)*(JSONObject_intValueOf(JSONArray_get(hr2, pos2), autoString("Rate"))-mean_rates2);
			denominateur1 = denominateur1 + pow((JSONObject_intValueOf(JSONArray_get(hr1, i), autoString("Rate"))-mean_rates1), 2);
			denominateur2 = denominateur2 + pow((JSONObject_intValueOf(JSONArray_get(hr2, pos2), autoString("Rate"))-mean_rates2), 2);
		}
	}
	double resultat = numerateur/(sqrt(denominateur1 == 0.0 ? 1.0 : denominateur1)*sqrt(denominateur2 == 0.0 ? 1.0 : denominateur2));
	return 0.5 + resultat/2.f;
}


// retourne la position du film d'id passé en paramètre s'il existe et renvoi -1 sinon
int get_position(JSONArray_t hr, int id)
{
	int i = 0;
	int found = -1;
	while(i != JSONArray_size(hr)) {
		if(id == JSONObject_intValueOf(JSONArray_get(hr, i), autoString("Id"))) {
			found = i;
			break;
		}
		i++;
	}
	return found;
}

//remarque, ici user_id ne correspond pas au réel ID de l'utilisateur mais de sa position dans la liste. A MODIFIER
JSONArray_t all_distances(BDD bdd, int user_id)
{
	JSONArray_t users_bdd = BDD_Users(bdd);
	JSONArray_t list = JSONArray_new();
	int i;
	for (i=0 ; i<JSONArray_size(users_bdd) ; i++)
	{
		JSONObject_t obj = JSONObject_new();
		int id_user = JSONObject_intValueOf(JSONArray_get(users_bdd, i), autoString("Id"));
		//printf("id_user : %d\n", id_user);
		if(id_user != user_id)
		{
			JSONObject_setInt(obj, autoString("Id"), id_user);
			double distance = distance_users(bdd, user_id, id_user);
			JSONObject_setDouble(obj, autoString("Sim"), distance);
			JSONArray_add(list, obj);
		}
	}
	return list;
}
