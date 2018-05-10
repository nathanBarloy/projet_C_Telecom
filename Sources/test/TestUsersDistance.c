#include <JSONAll.h>
#include <String/AutoString.h>
#include "../utils/BDD.h"
#include "../utils/Distance_utilisateur.h"

int main() {
  BDD bdd = BDD_load();
  double dist_users = distance_users(bdd,0,1);
  BDD_free(bdd);
	freeAutoString();
  printf("FIN\n");
  return 0;
}
