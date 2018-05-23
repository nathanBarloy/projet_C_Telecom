#include "Distance_utilisateur.h"

//récupérer les JSON HistoryRates des deux utilisateurs puis de réaliser la corrélation de Pearson pour en déduire la distance entre les deux utilisateurs
double distance_users(JSONArray_t users, int id1, int id2) {
  JSONObject_t users1 = JSONArray_get(users, id1);
  JSONObject_t users2 = JSONArray_get(users, id2);
  JSONArray_t history_rates1 = JSONObject_getArray(JSONObject_get(users1, autoString("History")), autoString("Rates"));
  JSONArray_t history_rates2 = JSONObject_getArray(JSONObject_get(users2, autoString("History")), autoString("Rates"));
  double resultat = pearson_correlation(history_rates1, history_rates2);
  //printf("les utilisateurs %d et %d ont une distance de %f (à partir de la corrélation de Pearson)\n", id1, id2, resultat);
  return resultat;
}

//calcul de la moyenne des notes d'un utilisateur
double mean_rates(JSONArray_t history_rates) {
  int i;
  int total = JSONArray_size(history_rates);
  int somme = 0;
  for (i = 0 ; i < total ; i++) {
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
  double numerateur = (double)0;
  double denominateur1 = (double)0;
  double denominateur2 = (double)0;
  double mean_rates1 = mean_rates(hr1);
  double mean_rates2 = mean_rates(hr2);
  //printf("moyenne 1 : %f\n moyenne 2 : %f \n", mean_rates1, mean_rates2);
  int i;
  int pos1;
  int pos2;
  for(i = 1 ; i <= 100 ; i++) {
    pos1 = get_position(hr1, i);
    pos2 = get_position(hr2, i);
    // if(pos1 != (-1) && pos2 == (-1)) {
    //   numerateur = numerateur + ((double)JSONObject_intValueOf(JSONArray_get(hr1, pos1), autoString("Rate"))-mean_rates1)*(-mean_rates2);
    //   denominateur1 = denominateur1 + pow((double)(JSONObject_intValueOf(JSONArray_get(hr1, pos1), autoString("Rate"))-mean_rates1), 2);
    //   denominateur2 = denominateur2 + pow((mean_rates2), 2);
    // }
    // else if(pos1 == (-1) && pos2 != (-1)) {
    //   numerateur = numerateur + (-mean_rates1)*(JSONObject_intValueOf(JSONArray_get(hr2, pos2), autoString("Rate"))-mean_rates2);
    //   denominateur1 = denominateur1 + pow((mean_rates1), 2);
    //   denominateur2 = denominateur2 + pow((JSONObject_intValueOf(JSONArray_get(hr2, pos2), autoString("Rate"))-mean_rates2), 2);
    // }
    if(pos1 != (-1) && pos2 != (-1)) {
      numerateur = numerateur + (JSONObject_intValueOf(JSONArray_get(hr1, pos1), autoString("Rate"))-mean_rates1)*(JSONObject_intValueOf(JSONArray_get(hr2, pos2), autoString("Rate"))-mean_rates2);
      denominateur1 = denominateur1 + pow((JSONObject_intValueOf(JSONArray_get(hr1, pos1), autoString("Rate"))-mean_rates1), 2);
      denominateur2 = denominateur2 + pow((JSONObject_intValueOf(JSONArray_get(hr2, pos2), autoString("Rate"))-mean_rates2), 2);
      //printf("numerateur : %f\n deno1 : %f\n deno2 : %f\n\n", numerateur, denominateur1, denominateur2);
    }
    // else if(pos1 == -1 && pos2 == -1) {
    //   numerateur = numerateur + (-mean_rates1)*(-mean_rates2);
    //   denominateur1 = denominateur1 + pow(mean_rates1, 2);
    //   denominateur2 = denominateur2 + pow(mean_rates2, 2);
    // }
  }
  double resultat = numerateur/(sqrt(denominateur1)*sqrt(denominateur2));
  //return 0.5 + resultat/2;
  return resultat;
}

// retourne la position du film d'id passé en paramètre s'il existe et renvoi -1 sinon
int get_position(JSONArray_t hr, int id) {
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
  int users_size = JSONArray_size(users_bdd);
  int i;
  for (i=0 ; i<users_size ; i++)
  {
    JSONObject_t obj = JSONObject_new();
    JSONObject_setInt(obj, autoString("Id"), JSONObject_intValueOf(JSONArray_get(users_bdd, i), autoString("Id")));
    JSONObject_setDouble(obj, autoString("Sim"), distance_users(users_bdd, user_id, i));
    JSONArray_add(list, obj);
    //question sur les fuites mémoires de obj ???
  }
  return list;
}
