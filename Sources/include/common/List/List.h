#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <Types/Types.h>
/*! \brief Structure représentant une List (Liste doublement chainée)
* Il n'est pas conseillé d'y accéder directement. Un ensemble de fonction permet de réaliser toutes les opérations nécessaires sur cette structure.
*/
struct List
{
	struct List* prev;
	struct List* next;
	void* value;
};
/*! \brief Type représentant la structure de List. */
typedef struct List* List_t;
/*! \brief Raccourci pour le cast en List_t
*
* \param a Pointeur
*/
#define List(a) (struct List*)(a)
#ifdef __cplusplus
extern "C"
{
#endif
/*! \brief Alloue une nouvelle List
* \return Pointeur de la nouvelle List
*/
struct List* newList();
/*! \brief Alloue une nouvelle List a partir d'une autre
* \param ptr Autre List
* \return Pointeur de la nouvelle List
*/
struct List* newListFromPtr(void* ptr);
/*! \brief Libère une Liste
* \param ptr Objet à libérer
* Ne libère ni les suivants, ni les précédents.
* \return 0
*/
struct List* freeList(struct List* ptr);
/*! \brief Libère une Liste
* \param ptr Objet à libérer
* Libère les élements précédents et suivants, ne libère pas la valeur associée.
* \return 0
*/
struct List* freeFullList(struct List* ptr);
/*! \brief Libère une Liste
* \param ptr Objet à libérer
* Libère uniquement les éléments suivants, ne libère pas la valeur associée.
* \return 0
*/
struct List* freeNextList(struct List* ptr);
/*! \brief Libère une Liste
* \param ptr Objet à libérer
* Libère uniquement les éléments précédents, ne libère pas la valeur associée.
* \return 0
*/
struct List* freePrevList(struct List* ptr);
/*! \brief Libère une Liste
* \param ptr Objet à libérer
* \param freeFunc Fonction a appeler pour libérer la valeur associée
* Ne libère ni les suivants, ni les précédents, libère aussi le pointeur de la valeur associée.
* \return 0
*/
struct List* freeListWithPtr(struct List* ptr, void (*freeFunc)(void*));
/*! \brief Libère une Liste
* \param ptr Objet à libérer
* \param freeFunc Fonction a appeler pour libérer la valeur associée
* Libère l'élement courant, ainsi que les précédents et suivants, libère aussi le pointeur de la valeur associée.
* \return 0
*/
struct List* freeFullListWithPtr(struct List* ptr, void (*freeFunc)(void*));
/*! \brief Libère une Liste
* \param ptr Objet à libérer
* \param freeFunc Fonction a appeler pour libérer la valeur associée
* Ne libère que les élements suivants, libère aussi le pointeur de la valeur associée.
* \return 0
*/
struct List* freeNextListWithPtr(struct List* ptr, void (*freeFunc)(void*));
/*! \brief Libère une Liste
* \param ptr Objet à libérer
* \param freeFunc Fonction a appeler pour libérer la valeur associée
* Ne libère que les élements précédents, libère aussi le pointeur de la valeur associée.
* \return 0
*/
struct List* freePrevListWithPtr(struct List* ptr, void (*freeFunc)(void*));
/*! \brief Détache une Liste
* \param ptr Objet à détacher
* Ne détache que l'élement courant, et accroche les précédents et suivants entre eux pour reboucher le "trou" dans la liste si nécessaire.
* \return ptr
*/
struct List* detachList(struct List* ptr);//Détache un élément et reconnecte les autres ensemble
/*! \brief Détache la Liste précédente
* \param ptr Objet à détacher
* Ne détache que les élements précédents
* \return Liste précédente (peut être 0)
*/
struct List* detachListPrev(struct List* ptr);//Détache les élements précédents comme liste, retourne la liste précédente
/*! \brief Détache la Liste suivante
* \param ptr Objet à détacher
* Ne détache que les élements suivants
* \return Liste suivants (peut être 0)
*/
struct List* detachListNext(struct List* ptr);//Détache les éléments suivants comme liste, retourne la liste suivante
/*! \brief Connecte comme element suivant direct, remplace le suivant
*
* \param ptr List concernée
* \param next Element a mettre comme suivant
* \return ptr
* Déconnecte le suivant, et le remplace: Attention, ne libère pas la mémoire du suivant, remplace TOUTE LA LISTE SUIVANTE.
*/
struct List* connectAsNextList(struct List* ptr, struct List* next);//Connecte comme suivant direct, remplace le suivant
/*! \brief Connecte comme element précédent direct, remplace le précédent
*
* \param ptr List concernée
* \param prev Element a mettre comme précédent
* \return ptr
* Déconnecte le précédent, et le remplace: Attention, ne libère pas la mémoire du précédent, remplace TOUTE LA LISTE SUIVANTE.
* Voir connectList() pour ajouter une liste à la suite.
*/
struct List* connectAsPrevList(struct List* ptr, struct List* prev);//Connecte comme précédent direct, remplace le précédent
/*! \brief Connecte 2 listes ensemble
*
* \param ptr Liste
* \param nl Liste à connecter a la suite
* Connecte la fin de la première liste au début de la suivante.
* Voir connectList() pour ajouter une liste à la suite.
*/
struct List* connectList(struct List* ptr, struct List* nl);//Ajoute a la fin de la liste, la nouvelle liste
/*! \brief Connecte comme element précédent et suivant direct, remplace le précédent et le suivant
*
* \param ptr List concernée
* \param next Element a mettre comme suivant
* \param prev Element a mettre comme précédent
* \return ptr
* Déconnecte le précédent et le suivant, et les remplacent: Attention, ne libère pas la mémoire du précédent ni du suivant, remplace TOUTE LA LISTE SUIVANTE et TOUTE LA LISTE PRECEDENTE.
* Voir connectList() pour ajouter une liste à la suite.
*/
struct List* joinList(struct List* ptr, struct List* next, struct List* prev);//Connecte comme précédent et suivant direct, remplace les connexions existantes
/*! \brief Renvoie le dernier element de la liste
*
* \param ptr Liste concernée
* \return Dernier élement de ptr, peut être ptr. Si ptr != 0 alors ne renvoie pas 0.
*/
struct List* lastList(struct List* ptr);//Renvoie le dernier element de la liste
/*! \brief Renvoie le premier element de la liste
*
* \param ptr Liste concernée
* \return Premier élement de ptr, peut être ptr. Si ptr != 0 alors ne renvoie pas 0.
*/
struct List* firstList(struct List* ptr);//Renvoie le 1er element de la liste
/*! \brief Copie une liste (1 seul élement)
*
* \param ptr Element à cloner
* \return Clone de 1 List. Un List, ici 1 seul élement, sans ses liaisons.
* Voir copyFullList() pour copier toute une liste.
*/
struct List* copyList(struct List* ptr);//Clone une Liste (1 seul element, sans ses liaisons)
/*! \brief Copie une liste (Tous les élements)
*
* \param ptr Liste à cloner
* \return Clone complet de la liste, en reproduisant les liaisons et en conservant l'ordre des valeurs dans la liste.
*/
struct List* copyFullList(struct List* ptr);//Clone entièrement une liste, renvoie le 1er élement
/*! \brief Renvoie l'élement suivant
*
* Permet d'accéder à l'élement suivant.
* \param ptr Liste concernée
* \return Element suivant (0 si aucun suivant)
*/
struct List* nextList(struct List* ptr);//Renvoie l'élement suivant
/*! \brief Renvoie l'élement précédent
*
* Permet d'accéder à l'élement précédent.
* \param ptr Liste concernée
* \return Element suivant (0 si aucun précédent)
*/
struct List* prevList(struct List* ptr);//Renvoie l'élement précédent
/*! \brief Tester l'existance d'un suivant
*
* \param ptr Liste concernée
* \return 1 si la liste à un suivant, 0 sinon.
*/
int hasNextList(struct List* ptr);//Renvoie vrai si un suivant est disponible
/*! \brief Tester l'existance d'un précédent
*
* \param ptr Liste concernée
* \return 1 si la liste à un précédent, 0 sinon.
*/
int hasPrevList(struct List* ptr);//Renvoie vrai si un précédent est disponible
/*! \brief Comparer 2 élements d'une liste
*
* \param ptr Element 1
* \param ptr2 Element 2
* \return 1 si les 2 pointeurs de valeurs sont égaux, 0 sinon.
*/
int equalsOneList(struct List* ptr, struct List* ptr2);//Compare 1 element par leur valeur
/*! \brief Comparer toute une liste, élément par élément
*
* \param ptr List 1
* \param ptr2 List 2
* \return 1 si les 2 listes ont même taille, et les élements aux mêmes positions ont les mêmes pointeurs de valeur, 0 sinon.
*/
int equalsList(struct List* ptr, struct List* ptr2);//Compare toute une liste par leur valeurs
/*! \brief Comparer toute une liste, élément par élément
*
* \param ptr List 1
* \param ptr2 List 2
* \return 1 si les élements aux mêmes positions ont les mêmes pointeurs de valeur, 0 sinon.
* Note: Ignore la longueur des listes, et s'arrête de comparer une fois la liste la plus courte parcourue. Considère comme identique tout ce qui n'a pas pu être comparé.
*/
int equalsListWithoutSize(struct List* ptr, struct List* ptr2);//Compare toute une liste par leur valeurs, considère comme vraie 2 listes de taille différentes tant que les elements communs sont égaux
/*! \brief Renvoie la longueur d'une List
*
* \param ptr Liste concernée
* \return Longueur de la liste
*/
size_t sizeOfList(struct List* ptr);//Taille complete d'une liste depuis le début a la fin
/*! \brief Renvoie la longueur de la Liste de la position actuelle à la fin
*
* \param ptr Liste concernée
* \return Longueur de la liste jusqu'a la fin depuis l'élement actuel.
*/
size_t sizeToEndList(struct List* ptr);//Taille d'une liste avant sa fin
/*! \brief Renvoie la longueur de la Liste de la position actuelle au début
*
* \param ptr Liste concernée
* \return Longueur de la liste jusqu'au début depuis l'élement actuel.
*/
size_t sizeToBeginList(struct List* ptr);//Taille d'une liste avant son début
/*! \brief Détacher les N élements suivants
*
* \param ptr List concerné (élement)
* \param n id de l'élement pour lequel détacher les suivants
* \return Liste contenant les N éléments suivants.
* Note: Les éléments se trouvant après les N sont rattachés a l'élement qui sert de point de coupure (en tant que suivant).
* Cette fonction permet d'exporter une zone d'une liste dans une autre Liste.
*/
struct List* detachNextNList(struct List* ptr, size_t n);//Détache les N elements suivants
/*! \brief Détacher les N élements précédents
*
* \param ptr List concerné (élement)
* \param n id de l'élement pour lequel détacher le précédent
* \return Liste contenant les N éléments précédents.
* Note: Les éléments se trouvant avant les N sont rattachés a l'élement qui sert de point de coupure (en tant que précédent).
* Cette fonction permet d'exporter une zone d'une liste dans une autre Liste.
*/
struct List* detachPrevNList(struct List* ptr, size_t n);//Détache les N elements précédents
/*! \brief Libérer les N élements suivants
*
* \param ptr List concerné (élement)
* \param n id de l'élement pour lequel free les suivants
* \return 0
* Note: Les éléments se trouvant après les N sont rattachés a l'élement qui sert de point de coupure (en tant que suivant).
* Cette fonction permet de couper une zone dans une liste.
* Les éléments selectionnés sont libérés, pas le pointeur de leurs valeurs.
*/
struct List* freeNextNList(struct List* ptr, size_t n);//Supprime les N élements suivants
/*! \brief Libérer les N élements précédents
*
* \param ptr List concerné (élement)
* \param n id de l'élement pour lequel free les précédents
* \return 0
* Note: Les éléments se trouvant avant les N sont rattachés a l'élement qui sert de point de coupure (en tant que précédent).
* Cette fonction permet de couper une zone dans une liste.
* Les éléments selectionnés sont libérés, pas le pointeur de leurs valeurs.
*/
struct List* freePrevNList(struct List* ptr, size_t n);//Supprime les N éléments précédents
/*! \brief Libérer les N élements suivants et les pointeurs de valeurs
*
* \param ptr List concerné (élement)
* \param n id de l'élement pour lequel free les suivants avec freeFunc
* \param freeFunc Fonction a appeler pour libérer le pointeur de la valeur
* \return 0
* Note: Les éléments se trouvant après les N sont rattachés a l'élement qui sert de point de coupure (en tant que suivant).
* Cette fonction permet de couper une zone dans une liste.
* Les éléments selectionnés sont libérés, le pointeur de leurs valeurs aussi.
*/
struct List* freeNextNListWithPtr(struct List* ptr, size_t n, void (*freeFunc)(void*));//Supprime les N élements suivants, désalloue aussi la valeur de l'élement.
/*! \brief Libérer les N élements précédents et les pointeurs de valeurs
*
* \param ptr List concerné (élement)
* \param n id de l'élement pour lequel free les précédents avec freeFunc
* \param freeFunc Fonction a appeler pour libérer le pointeur de la valeur
* \return 0
* Note: Les éléments se trouvant avant les N sont rattachés a l'élement qui sert de point de coupure (en tant que précédent).
* Cette fonction permet de couper une zone dans une liste.
* Les éléments selectionnés sont libérés, le pointeur de leurs valeurs aussi.
*/
struct List* freePrevNListWithPtr(struct List* ptr, size_t n, void (*freeFunc)(void*));//Supprime les N éléments précédents, désalloue aussi la valeur de l'élement.
/*! \brief Retourne la valeur de l'élément d'une List
*
* \param ptr List concerné (element)
* \return void* Pointeur sur la valeur
*/
void* valueOfList(struct List* ptr);//Renvoie la valeur d'un élement
/*! \brief Libérer un élement (fonction prévue pour fonctionner comme freeFunc)
*
* \param ptr Pointeur vers un List_t
* Fonction a passer aux fonctions free...WithPtr si valeur a supprimer est une structure de type List (1 seul élément)
*/
void freeVoidList(struct List* ptr);//Free un element, pour être utilisé comme ptr
/*! \brief Libérer un List complète (fonction prévue pour fonctionner comme freeFunc)
*
* \param ptr Pointeur vers un List_t
* Fonction a passer aux fonctions free...WithPtr si valeur a supprimer est une structure de type List (1 seul élément ou une liste complète)
*/
void freeVoidFullList(struct List* ptr);//Free toute la liste, pour être utilisé comme ptr
#ifdef __cplusplus
}
#endif
/*! \brief Raccourci pour free une liste entièrement
*
* \param a List_t
* Equivalent à: a = freeFullList(a);
*/
#define fList(a) a = freeFullList(a);
/*! \brief Raccourci pour l'élement suivant dans une liste
*
*  \param a List_t
*  Remplace l'element actuel par son suivant.
* Equivalent a: a = a->next;
*/
#define nList(a) a = a->next;
/*! \brief Raccourci pour l'élement précédent dans une liste
*
*  \param a List_t
*  Remplace l'element actuel par son précédent.
* Equivalent a: a = a->prev;
*/
#define pList(a) a = a->prev;
#endif
