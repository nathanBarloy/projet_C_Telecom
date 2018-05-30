#include "Distance_utilisateur.h"

//récupérer les JSON HistoryRates des deux utilisateurs puis de réaliser la corrélation de Pearson pour en déduire la distance entre les deux utilisateurs
double distance_users(BDD bdd, int id1, int id2)
{
	JSONObject_t user1 = BDD_getUserById(bdd, id1);
	JSONObject_t user2 = BDD_getUserById(bdd, id2);
	if(user1 == 0 || user2 == 0)
	{
		return -2;
	}
	else
	{
		//printf("%s\n", cString(JSONObject_asString(users2, 0)));
		JSONObject_t histo1 = JSONObject_get(user1, autoString("History"));
		JSONObject_t histo2 = JSONObject_get(user2, autoString("History"));
		//printf("%s\n", cString(JSONObject_asString(histo1, 0)));
		if(histo1 == 0 || histo2 == 0)
		{
			return -2;
		}
		else
		{
			JSONArray_t history_rates1 = JSONObject_getArray(histo1, autoString("Rates"));
			JSONArray_t history_rates2 = JSONObject_getArray(histo2, autoString("Rates"));
			if(history_rates1 == 0 || history_rates2 == 0)
			{
				return -2;
			}
			else{
				//printf("LISTE 1 :\n %s\n", cString(JSONArray_asString(history_rates1,0)));
				//printf("LISTE 2 :\n %s\n", cString(JSONArray_asString(history_rates2,0)));
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
	//printf("moyenne 1 : %f\n moyenne 2 : %f \n", mean_rates1, mean_rates2);
	int i;
	int pos1;
	int pos2;
	for(i = 0 ; i < JSONArray_size(hr1) ; i++) {
		int id = JSONObject_intValueOf(JSONArray_get(hr1, i), autoString("Id"));
		pos2 = get_position(hr2, id);
		if(pos2 != -1) {
			double x = JSONObject_intValueOf(JSONArray_get(hr1, i), autoString("Rate"));
			double y = JSONObject_intValueOf(JSONArray_get(hr2, pos2), autoString("Rate"));
			numerateur = numerateur + (x-mean_rates1)*(y-mean_rates2);
			denominateur1 = denominateur1 + pow((JSONObject_intValueOf(JSONArray_get(hr1, i), autoString("Rate"))-mean_rates1), 2);
			denominateur2 = denominateur2 + pow((JSONObject_intValueOf(JSONArray_get(hr2, pos2), autoString("Rate"))-mean_rates2), 2);
			//printf("numerateur : %f, denom\n", );
		}
	}
	double resultat = numerateur/(sqrt(denominateur1 == 0.0 ? 1.0 : denominateur1)*sqrt(denominateur2 == 0.0 ? 1.0 : denominateur2));
	//printf("numerateur : %f, denominateur : %f\n", numerateur, sqrt(denominateur1)*sqrt(denominateur2));
	return 0.5 + resultat/2.f;
	//return resultat;
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

double get_similarite(JSONArray_t distances, int user_id)
{
	int i = 0;
	int id;
	while(i<JSONArray_size(distances))
	{
		id = JSONObject_intValueOf(JSONArray_get(distances, i), autoString("Id"));
		if(id == user_id)
		{
			return JSONObject_doubleValueOf(JSONArray_get(distances, i), autoString("Sim"));
		}
		i++;
	}
	printf("Erreur dans get_similarite : pas de résultat\n");
	return 0.f;
}

JSONArray_t rates_estimations(BDD bdd, int id_user)
{
	//récuperer les notes de l'utilisateur cible
	JSONArray_t result = JSONArray_new();
	JSONObject_t user = BDD_getUserById(bdd, id_user);
	JSONObject_t user_history = JSONObject_get(user, autoString("History"));
	if(user_history == 0)
	{
		printf("Aucun historique pour cet utilisateur : recommandation impossible\n");
		return result;
	}
	JSONArray_t user_rates = JSONObject_get(user_history, autoString("Rates"));
	if(user_rates == 0)
	{
		printf("L'utilisateur n'a noté aucun film : recommandation impossible\n");
		return result;
	}
	//récuperer la bdd des films
	JSONArray_t bdd_movies = BDD_Films(bdd);
	int bdd_movies_size = JSONArray_size(bdd_movies);
	JSONArray_t users = BDD_Users(bdd);

	//obtenir les distances entre l'utilisateur et les autres
	JSONArray_t dist = all_distances(bdd, id_user);
	int i, j, c, d, id_movie;
	int note = 0;
	int rates_size = JSONArray_size(user_rates);
	int est_vu;
	double sim = 0.f;
	//printf("Début algo\n");
	for(i=0 ; i<bdd_movies_size ; i++)
	{
		//printf("Pour le film %d\n", i);
		id_movie = JSONObject_intValueOf(JSONArray_get(bdd_movies, i), autoString("Id"));
		c = 0;
		est_vu = 0;
		//vérifie si l'utilisateur (cible) à vu le film.
		while(c < rates_size)
		{
			if(JSONObject_intValueOf(JSONArray_get(user_rates, c), autoString("Id")) == id_movie)
			{
				est_vu = 1;
				break;
			}
			++c;
		}
		if(est_vu != 1)
		{
			//printf("L'utilisateur n'a pas vu le film %d\n", id_movie);
			double numerateur = 0.0;
			double denominateur = 0.0;
			double moyenne = 0.0;
			for(j=0 ; j<JSONArray_size(users) ; j++)
			{
				JSONObject_t user_courant = JSONArray_get(users, j);
				int id_user_courant = JSONObject_intValueOf(user_courant, autoString("Id"));
				if(id_user_courant != id_user)
				{
					//printf("Est ce que l'utilisateur %d a vu ce film ?\n", id_user_courant);
					JSONArray_t rates_courant = JSONObject_get(JSONObject_get(user_courant, autoString("History")), autoString("Rates"));
					if(rates_courant != 0)
					{
						//printf("L'utilisateur %d a noté des films\n", id_user_courant);
						int rates_size_courant = JSONArray_size(rates_courant);
						d = 0;
						note = 0;
						while(d < rates_size_courant)
						{
							if(JSONObject_intValueOf(JSONArray_get(rates_courant, d), autoString("Id")) == id_movie)
							{
								note = JSONObject_intValueOf(JSONArray_get(rates_courant, d), autoString("Rate"));
								//printf("Note de l'utilisateur %d sur le film %d: %d\n", id_user_courant, id_movie, note);
								break;
							}
							d++;
						}
						//l'utilisateur j à noté le film d
						if(note > 0)
						{
							//printf("Calcul de la note estimé\n");
							//élévation à la puissance 2.5
							sim = get_similarite(dist, id_user_courant);
							// printf("SIMI avant : %f\n", sim);
							// sim = sim * pow(sim, 1.5);
							// printf("SIMI après%f\n", sim);
							numerateur = numerateur + sim*note;
							denominateur = denominateur + fabs(sim);
						}
					}
					else
					{
						//printf("Pas de notes pour cet utilisateur\n");
					}
				}
				//printf("numérateur : %f\n", numerateur);
				//printf("dénominateur : %f\n", denominateur);
			}
			moyenne = numerateur/(denominateur==0.0 ? 1.0 : denominateur);
			JSONObject_t film = JSONObject_getCopy(JSONArray_get(bdd_movies, i));
			JSONObject_setDouble(film, autoString("Moyenne"), moyenne);
			JSONArray_add(result, film);
		}
	}
	return result;
}

JSONArray_t collaborative_recommendation(BDD bdd, int user_id)
{
	JSONArray_t array = rates_estimations(bdd, user_id);
	Vector_t vector = fromArrayToVector(array);
	Vector_t sorted_vector = quick_sort(vector);
	JSONArray_t sorted_array = fromVectorToArray(sorted_vector);
	return sorted_array;
}
