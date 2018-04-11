#ifndef STRING_H
#define STRING_H
#include <stdlib.h>
#include <stdio.h>
#include <Types/Types.h>
/*! \brief Structure représentant un String (Chaine de caractères)
* Il n'est pas conseillé d'y accéder directement. Un ensemble de fonction permet de réaliser toutes les opérations nécessaires sur cette structure.
*/
struct String
{
	char* str;
	size_t len;
};
/*! \brief Type représentant la structure de String. */
typedef struct String* String_t;
#ifdef __cplusplus
extern "C"
{
#endif
/*! \brief Alloue un nouveau String
* \return Pointeur du nouveau String
*/
struct String* newString();//Test OK
/*! \brief Alloue un nouveau String a partir d'un String
* \param str String
* \return Pointeur du nouveau String
*/
struct String* newStringFromString(const struct String* str);//Test OK
/*! \brief Alloue un nouveau String a partir d'un String
* \param str String
* \return Pointeur du nouveau String
*/
struct String* newStringFromCharStar(const char *str);//Test OK
/*! \brief Alloue un nouveau String a partir d'un String en spécifiant la longueur max
* \param str String
* \param size Longueur max a recopier
* \return Pointeur du nouveau String
*/
struct String* newStringFromCharStarSize(const char *str, size_t size);
/*! \brief Alloue un nouveau String a partir d'un char
* \param c Char
* \return Pointeur du nouveau String
*/
struct String* newStringFromChar(const char c);
/*! \brief Alloue un nouveau String en lowercase a partir d'un String
* \param str String
* \return Pointeur du nouveau String
*/
struct String* newLowerString(const struct String* str);
/*! \brief Alloue un nouveau String en uppercase a partir d'un String
* \param str String
* \return Pointeur du nouveau String
*/
struct String* newUpperString(const struct String* str);
/*! \brief Alloue un nouveau String avec invercase a partir d'un String
* \param str String
* \return Pointeur du nouveau String
*/
struct String* newInvertCaseString(const struct String* str);
/*! \brief Alloue un nouveau String a partir du reverse d'un String
* \param str String
* \return Pointeur du nouveau String
*/
struct String* newReverseString(const struct String* str);
/*! \brief Libère un String
* \param str Objet à libérer
* Libère le String
* \return 0
*/
struct String* freeString(struct String* str);//Test OK
/*! \brief Assigne la valeur d'un String a un autre
*
* \param str String concerné
* \param value String a copier
*/
void setString(struct String* str, struct String* value);//Change la valeur d'un string (copie)
/*! \brief Vide une chaine de caractère
*
* \param str Chaine concernée
*/
void emptyString(struct String* str);//Remet a zéro une chaine
/*! \brief Renvoie la longueur d'une chaine
*
* \param str String concernée
* \return Longueur de la chaine
*/
size_t sizeOfString(const struct String* str);//Test OK
/*! \brief Renvoie l'équivalent en char* (C String, chaine C standard)
*
* \param str String concerné
* \return Pointeur de chaine standard pour la chaine. Note: Pointeur interne, sa modification peut entrainer des erreurs dans la structure.*/
char* cString(const struct String* str);//Test OK
/*! \brief Concaténer 2 chaines
*
* \param str Chaine concernée (reçoit le total)
* \param str2 Chaine a ajouter à la précédente
*/
void concatString(struct String* str, const struct String* str2);//Test OK
/*! \brief Concaténer N chaines
*
* \param str Chaine concernée (reçoit le total)
* \param n Nombre de chaines a concaténer
* \param ... Chaines a ajouter à la précédente, respecter le nombre saisi précédement
*/
void concatMString(struct String* str, int n, ...);//Test OK
/*! \brief Copie une chaine dans une autre
*
* \param str Chaine concernée (reçoit la valeur)
* \param str2 Chaine sourcée (ne sera pas modifiée)
*/
void copyString(struct String* str, const struct String* str2);//Test OK
/*! \brief Coupe une chaine a la position donnée.
*
* \param str Chaine concernée pour être coupée
* \param pos Position de coupe
* \return Nouvelle chaine contenant la partie coupée (après la position de coupe)
*/
struct String* cutString(struct String* str, const size_t pos);//Retourne la 2e chaine //Test OK
/*! \brief Couper une zone d'une chaine
*
* \param str Chaine concernée pour être coupée
* \param pos Position de base de la coupure
* \param size Longueur de la coupure (zone a couper)
* \return Nouvelle chaine contenant la zone coupée
*/
struct String* cutAreaOfString(struct String* str, const size_t pos, const size_t size);//Retourne la partie enlevée//Test OK
/*! \brief Réduit une chaine a la position donnée (longueur)
*
* \param str Chaine concernée pour être coupée
* \param pos Position de coupe (longueur restante)
* Le morceau restant est libéré de la mémoire
*/
void reduceString(struct String* str, const size_t pos);//Vire un morceau de la chaine (après une certaine position) // Test OK
/*! \brief Réduire une zone d'une chaine (libérer une zone d'une chaine)
*
* \param str Chaine concernée pour être coupée
* \param pos Position de base de la coupure
* \param size Longueur de la coupure (zone a couper)
* Le morceau coupé est libéré de la mémoire
*/
void reduceAreaOfString(struct String* str, const size_t pos, const size_t size);//Vire un morceau de la chaine (n'importe où)
/*! \brief Met la chaine en uppercase
*
* \param str Chaine concernée
*/
void upperString(struct String* str);//Test OK
/*! \brief Met la chaine en lowercase
*
* \param str Chaine concernée
*/
void lowerString(struct String* str);//Test OK
/*! \brief Met la chaine en invertcase (inverse miniscules et majuscules)
*
* \param str Chaine concernée
*/
void invertCaseString(struct String* str);//Test OK
/*! \brief Met la chaine en reversestring (inverse le sens de la chaine)
*
* \param str Chaine concernée
*/
void reverseString(struct String* str);//Test OK
/*! \brief Teste l'égalité entre 2 chaines
*
* \param str Chaine concernée
* \param str2 Chaine servant de comparaison
* \return 1 si égales, 0 sinon.
*/
int equalsString(const struct String* str, const struct String* str2);//Test OK
/*! \brief Teste l'égalité entre N chaines
*
* \param n Nombre de chaines a comparer
* \param ... Chaines servant de comparaison
* \return 1 si toutes égales, 0 sinon.
* Note: Pour comparer 2 chaines il faut entrer 2 pour n, et entrer le nom des 2 chaines.
*/
int equalsMString(int n, ...);//Test OK
/*! \brief Raccourci pour le cast en String
*
* \param a Pointeur
*/
#define String(a) (struct String*)(a)//Test OK
/*! \brief Raccourci pour le freeString
*
* \param a Pointeur
* Note: Equivalent a: a = freeString(a);
*/
#define fString(a) a = freeString(a);//Test OK
/*! \brief Raccourci pour afficher une chaine
*
* \param a String
* Note: Affiche la chaine dans le terminal, puis passe une ligne.
*/
#define dString(a) printf("%s\n", cString(a));//Test OK
/*! \brief Libérer N chaines
*
* \param n Nombre de chaines a libérer
* \param ... Chaines à libérer
* Note: Pour libérer 2 chaines il faut entrer 2 pour n, et entrer le nom des 2 chaines.
*/
void fmString(int n, ...);//Nombre, String_t*, String_t*, .... //Test OK
/*! \brief Libérer une chaine avec WithPtr
*
* \param str Chaine a libérer
* Note: Cette fonction est prévue pour être utilisée avec Map, List, Vector, etc... dans les fonctions free...WithPtr, elle permet de libérer proprement des String
*/
void freeVoidString(void* str);//Utile pour free a travers un pointeur de fonction
#ifdef __cplusplus
}
#endif
#endif
