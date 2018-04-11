#ifndef AUTOSTRING_H
#define AUTOSTRING_H
#include "String.h"
#include <Vector/Vector.h>
#ifdef __cplusplus
extern "C"
{
#endif
/*! \brief Fonction gérant le tableau global d'autoString
*
* \param s Variable gérant l'allocation.
*
* Ne pas utiliser directement.
*/
struct Vector* global_AutoString(int s);
/*! \brief Fonction d'initialisation de autoString
*
* Appellée automatiquement par les composants qui en ont besoin.
* Inutile de l'appeler vous même.
*/
void initAutoString();
/*! \brief Fonction interne pour l'obtention de chaines
*
* \param str Chaine a obtenir/stocker
* \return Chaine
* Note: Ne pas utiliser, utiliser autoString pour gérer vos chaines.
*/
String_t getAutoString(char* str);//Ne pas utiliser, utiliser autoString()
/*! \brief Gérer automatiquement l'allocation mémoire des chaines de type String.
*
* \param str char* a gérer.
* \return String
* autoString se charge d'allouer une et une seule fois les chaines que vous lui donnez. Si une chaine identique existe déjà, autoString ne la réallouera pas.
* Note: Il est de votre responsabilité de free le char* si celui ci n'est pas une constante.
* freeAutoString permettra de libérer l'intégralité des chaines gérées.
*/
String_t autoString(char *str);
/*! \brief Gérer automatiquement les pointeurs pour les chaines de type String déjà alloueés.
*
* \param str String à gérer
* \return String
* autoStringAllocated se charge de gérer un pointeur que vous avez déjà alloué vous même (type String_t), il saura lui même la garder ou le libérer si nécessaire, quoi qu'il arrive il vous retournera une chaine identique exploitable, et pour laquelle il conserve le pointeur.
* Comme pour autoString, si la chaine existe déjà il la libérera et vous renverra celle qui existe déjà.
* Les String de autoString et autoStringAllocated sont partagées.
*/
String_t autoStringAllocated(String_t str);
/*! \brief Gérer automatiquement la concaténation de 2 chaines
*
* \param str Chaine 1
* \param str2 Chaine 2
* Cette fonction ne modifie pas str, ni str 2.
* Cette fonction renvoie un nouveau String contenant la concaténation de str et str2.
* Le pointeur nouvellement crée est gardé par autoString, vous n'avez pas à le libérer, cela sera fait automatiquement.
*/
String_t autoConcatString(String_t str, String_t str2);
/*! \brief Gérer automatiquement la concaténation de N chaines (char*)
*
* \param n Nombre de chaine a concaténer
* \param ... Chaines a concaténer (char*)
* Cette fonction ne modifie pas les chaines.
* Cette fonction renvoie un nouveau String contenant la concaténation de str et str2.
* Le pointeur nouvellement crée est gardé par autoString, vous n'avez pas à le libérer, cela sera fait automatiquement.
* Fonctionnement identique a autoConcatString mais avec N String.
*/
String_t autoConcatNString(int n, ...);
/*! \brief Gérer automatiquement la concaténation de N chaines déjà allouées (String_t)
*
* \param n Nombre de chaine a concaténer
* \param ... Chaines a concaténer (String_t)
* Cette fonction ne modifie pas les chaines.
* Cette fonction renvoie un nouveau String contenant la concaténation de str et str2.
* Le pointeur nouvellement crée est gardé par autoString, vous n'avez pas à le libérer, cela sera fait automatiquement.
* Fonctionnement identique a autoConcatString mais avec N String.
*/
String_t autoConcatNStringAllocated(int n, ...);
/*! \brief Libérer l'intégralité des chaines gérées automatiquement
*
* Note: Assurez vous de ne plus utiliser de pointeurs provenant de autoString() avant d'appeller cette fonction.
* Appellez cette fonction avant le return 0; de votre main pour libérer correctement toutes les chaines.
*/
void freeAutoString();
/*! \brief Afficher l'intégralité des chaines gérées automatiquement
*
* Note: Affiche dans le terminal
*/
void showAutoString();
#ifdef __cplusplus
}
#endif
#endif
