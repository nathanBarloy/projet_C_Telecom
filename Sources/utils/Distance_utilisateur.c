#include "Distance_utilisateur.h"

//récupérer les JSON HistoryRates des deux utilisateurs puis de réaliser la corrélation de Pearson pour en déduire la distance entre les deux utilisateurs
double distance_users(BDD bdd_users, int id1, int id2) {
  JSONArray_t users = BDD_Users(bdd_users);
  JSONObject_t users1 = JSONArray_get(users, id1);
  JSONObject_t users2 = JSONArray_get(users, id2);
  JSONArray_t history_rates1 = JSONObject_getArray(JSONObject_get(users1, autoString("History")), autoString("Rates");
  JSONArray_t history_rates2 = JSONObject_getArray(JSONObject_get(users2, autoString("History")), autoString("Rates");
  double resultat = (double)(0);
  return resultat;
}

//calcul de la moyenne des notes d'un utilisateur
double mean_rates(JSONArray_t history_rates) {
  int i;
  int total = JSONArray_size(history_rates);
  int somme = 0;
  for (i = 0 ; i < total ; i++) {
    somme = somme + JSONObject_intValueOf(JSONObject_get(JSONArray_get(history_rates, i), AutoString("Rate")));
  }
  double resultat = somme/total
  return resultat;
}

//calcul de la corréalation de Pearson : on ne prend pas en compte ici les films non notés par les deux utilisateurs.
double Pearson_correlation(JSONArray_t hr1, JSONArray_t hr2) {
  //recherche des films notés par un utilisateur au moins
  int max = max_length(JSONArray_size(hr1), JSONArray_size(hr2));
  double numerateur = (double)0;
  double denomiteur = (double)0;
  double mean_rates1 = mean_rates(hr1);
  double mean_rates2 = mean_rates(hr2);
  for(int i = 1 ; i <= 100 ; i++) {
    bool bool_hr1 = check_id(hr1, i);
    bool bool_hr2 = check_id(hr2, i);
    if(bool_hr1 || bool_hr2) {

    }
  }
}

//déterminer le max entre les deux (pas utlisé finalement)
int max_length(int a, int b) {
  if(a <= b) {
    return b;
  }
  else {
    return a;
  }
}

//vérifier la présence d'un id film dans history_rates
bool check_id(JSONArray_t hr, int id) {
  int i = 0;
  while (i != JSONArray_size(hr)) {
    if(JSONObject_intValueOf(JSONObject_get(JSONArray_get(hr, i), AS("Id"))) == i ) {
      return true;
    }
  }
  return false;
}
