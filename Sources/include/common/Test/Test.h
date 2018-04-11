#ifndef TEST_H
#define TEST_H
/*! \brief Permet de définir une fonction de test.
* Le code: fun; est a placer sur la première ligne d'une fonction de test unitaire pour permettre un affichage correct.
*/
#define fun printf("Test: %s\n", __func__);
/*! \brief Permet de lancer une fonction de test, et interpreter le code de retour.
*
* Usage: run(nomFonction, "Description du test")
* \param a Nom de fonction
* \param s String, deescription du test
*/
#define run(a, s) printf("================================================\n");if(a()){printf("Completed: %s.\n", s);} else {printf("Failed   : %s.\n", s);}
#endif
