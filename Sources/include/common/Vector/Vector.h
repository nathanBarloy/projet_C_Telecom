#ifndef VECTOR_H
#define VECTOR_H
/*! \brief Taille de base du tableau contenu dans Vector
*
* Par défaut 50. Le tableau augmentera par multiples de 2, et diminuera par divisions de 2. */
#define VECTOR_BASE_SIZE 50
#include <stdlib.h>
#include <Types/Types.h>
/*! \brief Structure représentant un Vector (ArrayList)
* Il n'est pas conseillé d'y accéder directement. Un ensemble de fonction permet de réaliser toutes les opérations nécessaires sur cette structure.
*/
struct Vector
{
	size_t size;
	size_t allocated;
	void** array;
};
/*! \brief Type représentant la structure de Vector. */
typedef struct Vector* Vector_t;
/*! \brief Raccourci pour caster en Vector_t
* \param a Pointeur
*/
#define Vector(a) (Vector_t)(a)
#ifdef __cplusplus
extern "C"
{
#endif
/*! \brief Alloue un nouveau Vector
* \return Pointeur du nouveau vector
*/
struct Vector* newVector();
/*! \brief Alloue un nouveau Vector a partir d'un autre
* \param vector2 Autre vector
* \return Pointeur du nouveau vector
*/
struct Vector* newVectorFromVector(struct Vector* vector2);
/*! \brief Libère un Vector
* \param vector Objet à libérer
* \return 0
*/
struct Vector* freeVector(struct Vector* vector);
/*! \brief Libère un Vector et le pointeur des valeurs
* \param vector Objet à libérer
* \param freeFunc Fonction à appeller pour libérer les pointeurs des valeurs
* \return 0
*/
struct Vector* freeVectorWithPtr(struct Vector* vector, void (*freeFunc)(void*));
/*! \brief Vide un Vector
* \param vector Objet à vider
* \return 0
*/
struct Vector* clearVector(struct Vector* vector);//Empty the vector
/*! \brief Vide un Vector et le pointeur des valeurs
* \param vector Objet à vider
* \param freeFunc Fonction à appeller pour libérer les pointeurs des valeurs
* \return 0
*/
struct Vector* clearVectorWithPtr(struct Vector* vector, void (*freeFunc)(void*));//Empty the vector and the elements
/*! \brief Ajoute un élement au vector
*
* \param vector Vector concerné
* \param e Element
* \return 1 en cas de réussie, 0 en cas d'échec.
*/
int addToVector(struct Vector* vector, void* e);//Add an element to the vector (Caution: make size change)
/*! \brief Enlève un élement du vector
*
* \param vector Vector concerné
* \param e Element
* \return 1 en cas de réussie, 0 en cas d'échec.
* Ne libère pas le pointeur
*/
int delFromVector(struct Vector* vector, void* e);//Remove an element from the vector (Caution: make size change)
/*! \brief Enlève un élement du vector
*
* \param vector Vector concerné
* \param index Position dans le vector
* \return 1 en cas de réussie, 0 en cas d'échec.
*/
int eraseOnVector(struct Vector* vector, size_t index);//Remove an index from the vector (Caution: Make size change)
/*! \brief Libère un élement du vector
*
* \param vector Vector concerné
* \param index Position dans le vector
* \return 1 en cas de réussie, 0 en cas d'échec.
*/
int freeOnVector(struct Vector* vector, size_t index);//Free an index from the vector (Caution: Make size change)
/*! \brief Place un élement dans vector
*
* \param vector Vector concerné
* \param e Element
* \param index Index dans lequel l'élement doit être placé
* \return 1 en cas de réussie, 0 en cas d'échec.
*/
int setOnVector(struct Vector* vector, size_t index, void* e);//Set a value on the vector
/*! \brief Récupère un élement du vector
*
* \param vector Vector concerné
* \param index Position dans le vector
* \return 1 en cas de réussie, 0 en cas d'échec.
*/
void* getFromVector(struct Vector* vector, size_t index);//Get a value from vector
/*! \brief Ajoute le contenu d'un vector dans le vector
*
* \param vector Vector concerné
* \param nv Vector depuis lequel copier les données
* Les données sont retirées du vector nv.
*/
int appendVectorToVector(struct Vector* vector, struct Vector* nv);//NV is free
/*! \brief Ajoute le contenu d'un vector dans le vector
*
* \param vector Vector concerné
* \param nv Vector depuis lequel copier les données
* Les données ne sont pas retirées du vector nv.
*/
int appendVectorCopyToVector(struct Vector* vector, struct Vector* nv);//NV is not free
/*! \brief Sépare le vector a la position donnée
* \param vector Vector concerné
* \param pos Position donnée dans le vector
* \return Nouveau vector contenant les données de la position pos jusqu'a la fin.
*/
struct Vector* splitVector(struct Vector* vector, size_t pos);//Return the rest, caution: change vector size
/*! \brief Sépare une zone du vector a la position donnée d'une taille donnée
* \param vector Vector concerné
* \param pos Position donnée dans le vector
* \param size Taille à couper
* \return Nouveau vector contenant les données de zone découpée
*/
struct Vector* splitAreaOfVector(struct Vector* vector, size_t pos, size_t size);//Return the area, caution: change vector size
/*! \brief Enlève une zone du vector a la position donnée d'une taille donnée
* \param vector Vector concerné
* \param pos Position donnée dans le vector
* \param size Taille à couper
* \return 1 en cas de réussite, 0 en cas d'échec
*/
int removeAreaFromVector(struct Vector* vector, size_t pos, size_t size);//Remove the selected area, caution: change vector size
/*! \brief Enlève une zone du vector a la position donnée
* \param vector Vector concerné
* \param pos Position donnée dans le vector
* \return 1 en cas de réussite, 0 en cas d'échec
*/
int removeAfterVector(struct Vector* vector, size_t pos);//Remove all elements after the position, caution: change vector size
/*! \brief Enlève une zone du vector a la position donnée d'une taille donnée libère les données
* \param vector Vector concerné
* \param pos Position donnée dans le vector
* \param size Taille à couper
* \return 1 en cas de réussite, 0 en cas d'échec
* Libère le pointeur des données associées
*/
int freeAreaFromVector(struct Vector* vector, size_t pos, size_t size, void (*freeFunc)(void*));//Free the selected area, caution: change vector size
/*! \brief Enlève une zone du vector a la position donnée, libère les données
* \param vector Vector concerné
* \param pos Position donnée dans le vector
* \return 1 en cas de réussite, 0 en cas d'échec
* Libère les pointeurs des données
*/
int freeAfterVector(struct Vector* vector, size_t pos, void (*freeFunc)(void*));//Free all elements after the position, caution: change vector size
/*! \brief Retourne la taille occupée d'un vector
*
* \param vector Vector concerné
* \return Taille occupée
*/
size_t sizeOfVector(struct Vector* vector);//Return vector size
/*! \brief Fonction permettant de supprimer des vector dans des vectors
* \param ptr Vector à supprimer
*/
void freeVoidVector(void* ptr);//Free pour freeFunc
/*! \brief Raccourci pour un free basique.
*
* \param a Vector à libérer
* Equivalent à: a = freeVector(a);
*/
#define fVector(a) a = freeVector(a);
#ifdef __cplusplus
}
#endif
#endif
