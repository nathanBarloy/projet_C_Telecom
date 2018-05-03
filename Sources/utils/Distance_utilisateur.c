#include "Distance_utilisateur.h"

//récupérer les JSON HistoryRates des deux utilisateurs puis de réaliser la corrélation de Pearson pour en déduire la distance entre les deux utilisateurs
double distance_users(BDD bdd_users, int id1, int id2) {
  JSONArray_t users = BDD_Users(bdd_users);
  JSONObject_t users1 = JSONArray_get(users, id1);
  JSONObject_t users2 = JSONArray_get(users, id2);
  JSONArray_t history_rates1 = JSONObject_getArray(JSONObject_get(users1, autoString("History")), autoString("Rates"));
  JSONArray_t history_rates2 = JSONObject_getArray(JSONObject_get(users2, autoString("History")), autoString("Rates"));
  double resultat = pearson_correlation(history_rates1, history_rates2);
  printf("les utilisateurs %d et %d ont une similarité de %f (à partir de la corrélation de Pearson)\n", id1, id1, resultat);
  return resultat;
}

//calcul de la moyenne des notes d'un utilisateur
double mean_rates(JSONArray_t history_rates) {
  int i;
  int total = JSONArray_size(history_rates);
  int somme = 0;
  for (i = 0 ; i < total ; i++) {
    somme = somme + JSONObject_intValueOf(JSONArray_get(history_rates, i), autoString("Rate"));
  }
  double resultat = somme/total;
  return resultat;
}

//calcul de la corréalation de Pearson : on ne prend pas en compte ici les films non notés par les deux utilisateurs.
double pearson_correlation(JSONArray_t hr1, JSONArray_t hr2) {
  double numerateur = (double)0;
  double denominateur1 = (double)0;
  double denominateur2 = (double)0;
  double mean_rates1 = mean_rates(hr1);
  double mean_rates2 = mean_rates(hr2);
  int i;
  for(i = 1 ; i <= 100 ; i++) {
    bool bool_hr1 = check_id(hr1, i);
    bool bool_hr2 = check_id(hr2, i);
    if(bool_hr1 && !bool_hr2) {
      numerateur = numerateur + ((double)JSONObject_intValueOf(JSONArray_get(hr1, i), autoString("Rate"))-mean_rates1)*(-mean_rates2);
      denominateur1 = denominateur1 + pow((double)(JSONObject_intValueOf(JSONArray_get(hr1, i), autoString("Rate"))-mean_rates1), 2);
      denominateur2 = denominateur2 + pow((mean_rates2), 2);
    }
    else if(!bool_hr1 && bool_hr2) {
      numerateur = numerateur + (-mean_rates1)*(JSONObject_intValueOf(JSONArray_get(hr2, i), autoString("Rate"))-mean_rates2);
      denominateur1 = denominateur1 + pow((mean_rates1), 2);
      denominateur2 = denominateur2 + pow((JSONObject_intValueOf(JSONArray_get(hr2, i), autoString("Rate"))-mean_rates2), 2);
    }
    else if(bool_hr1 && bool_hr2) {
      numerateur = numerateur + (JSONObject_intValueOf(JSONArray_get(hr1, i), autoString("Rate"))-mean_rates1)*(JSONObject_intValueOf(JSONArray_get(hr2, i), autoString("Rate"))-mean_rates2);
      denominateur1 = denominateur1 + pow((JSONObject_intValueOf(JSONArray_get(hr1, i), autoString("Rate"))-mean_rates1), 2);
      denominateur2 = denominateur2 + pow((JSONObject_intValueOf(JSONArray_get(hr2, i), autoString("Rate"))-mean_rates2), 2);
    }
  }
  double resultat = numerateur/(sqrt(denominateur1)*sqrt(denominateur2));
  return resultat;
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
    if(JSONObject_intValueOf(JSONArray_get(hr, i), autoString("Id")) == i ) {
      return true;
    }
  }
  return false;
}
