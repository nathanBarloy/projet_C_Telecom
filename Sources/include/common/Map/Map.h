#ifndef MAP_H
#define MAP_H
#include <Types/Types.h>
#include <String/String.h>
#include <List/List.h>
#include <Vector/Vector.h>
/*! \brief Taille par défaut du tableau contenant les listes chainées dans Map
*
* Modifiable via newMapWithSize() lors de l'allocation d'une Map*/
#define MAP_DEFAULT_SIZE 100
/*! \brief Structure représentant un Objet contenu dans Map
* Il n'est pas conseillé d'y accéder directement. Un ensemble de fonction permet de réaliser toutes les opérations nécessaires sur cette structure.
* Cet objet a été prévu pour une utilisation interne par cette bibliothèque, il n'est pas conseillé de l'utiliser directement. Cet objet intervient dans la structure interne de Map.
*/
struct MapObject
{
	String_t name;
	void* value;
};
/*! \brief Type représentant la structure de MapObject. */
typedef struct MapObject* MapObject_t;
/*! \brief Structure représentant une Map (Dictionnaire, Tableau associatif)
* Il n'est pas conseillé d'y accéder directement. Un ensemble de fonction permet de réaliser toutes les opérations nécessaires sur cette structure.
*/
struct Map
{
	size_t size;
	List_t* array;
};
/*! \brief Type représentant la structure de Map. */
typedef struct Map* Map_t;
#ifdef __cplusplus
extern "C"
{
#endif
/*! \brief Alloue une nouvelle Map
* \return Pointeur de la nouvelle Map
*/
Map_t newMap();
/*! \brief Alloue une nouvelle Map a partir d'une taille
* \param size Taille initiale de tableau
* \return Pointeur de la nouvelle Map
*/
Map_t newMapWithSize(size_t size);
/*! \brief Libère une Map
* \param map Objet à libérer
* Libère la map, ne libère pas les pointeurs des valeurs associées.
* \return 0
*/
Map_t freeMap(Map_t map);
/*! \brief Libère une Map
* \param map Objet à libérer
* \param freeFunc Fonction a appeler pour libérer la valeur associée
* Libère la map, libère les pointeurs des valeurs associées.
* \return 0
*/
Map_t freeMapWithPtr(Map_t map, void (*freeFunc)(void*));
/*! \brief Vider une Map
* \param map Objet à libérer
* Vider la map, ne libère pas les pointeurs des valeurs associées.
* \return 0
*/
Map_t emptyMap(Map_t map);
/*! \brief Vider une Map
* \param map Objet à libérer
* \param freeFunc Fonction a appeler pour libérer la valeur associée
* Vider la map, libère les pointeurs des valeurs associées.
* \return 0
*/
Map_t emptyMapWithPtr(Map_t map, void (*freeFunc)(void*));
/*! \brief Calcule le hash pour la map, en utilisant la méthode LoseLose
* \param str String
* \return Hash (nombre)
*/
unsigned long hashMap(String_t str);
/*! \brief Obtenir une valeur a partir de sa clé
*
* \param map Map concernée
* \param str Clé
* \return Valeur se trouvant à cette clé, 0 si la clé n'existe pas
*/
void* getMap(Map_t map, String_t str);
/*! \brief Assigner une valeur à une clé
*
* \param map Map concernée
* \param str Clé
* \param e Valeur a mettre dans la clé
* \return map
*/
Map_t setMap(Map_t map, String_t str, void* e);
/*! \brief Retirer une valeur a partir de sa clé
*
* \param map Map concernée
* \param str Clé
* \return map
* Note: La mémoire n'est pas libérée pour le pointeur de la valeur
*/
Map_t removeFromMap(Map_t map, String_t str);
/*! \brief Retirer une valeur a partir de sa clé et libérer le pointeur de la valeur
*
* \param map Map concernée
* \param str Clé
* \param freeFunc Fonction à appeler pour libérer le pointeur de la valeur de la mémoire
* \return map
* Note: La mémoire est libérée pour le pointeur de la valeur
*/
Map_t removeFromMapWithPtr(Map_t map, String_t str, void (*freeFunc)(void*));
/*! \brief Nombre d'élements dans la map
*
* \param map Map concernée
* \return Nombre d'élements dans la map
*/
size_t sizeOfMap(Map_t map);
/*! \brief Crée un vector a partir d'une map
*
* \param map Map concernée
* \return Vector contenant les associations clés/valeurs de la map (type MapObject_t)
*/
Vector_t vectorFromMap(Map_t map);
/*! \brief Créer une map a partir d'un tableau
*
* \param arr Tableau contenant des MapObject_t
* \return Map contenant les associations
*/
Map_t mapFromVector(Vector_t arr);
/*! \brief Créer une List a partir d'une Map
*
* \param map Map concernée
* \return List contenant des MapObject_t pour les associations.
*/
List_t listFromMap(Map_t map);
/*! \brief Créer une map a partir d'une List de MapObject_t
*
* \param list List contenant des MapObject_t
* \return Nouvelle map contenant les associations de List
*/
Map_t mapFromList(List_t list);

/*! \brief Alloue un nouveau MapObject
* \return Pointeur du nouveau MapObject
*/
MapObject_t newMapObject();
/*! \brief Alloue un nouveau MapObject avec un nom de clé
* \param name Nom de clé
* \return Pointeur du nouveau MapObject
*/
MapObject_t newMapObjectWithName(String_t name);
/*! \brief Alloue un nouveau MapObject avec un nom de clé et une valeur
* \param name Nom de clé
* \param e Valeur
* \return Pointeur du nouveau MapObject
*/
MapObject_t newMapObjectFull(String_t name, void *e);
/*! \brief Libère un MapObject
* \param obj MapObject concerné
* \return 0
* Ne libère pas la mémoire de la valeur (pointeur).
*/
MapObject_t freeMapObject(MapObject_t obj);
/*! \brief Libère un MapObject
* \param obj MapObject concerné
* \return 0
* Ne libère pas la mémoire de la valeur (pointeur).
*/
MapObject_t freeMapObjectWithPtr(MapObject_t obj, void (*freeFunc)(void*));
/*! \brief Obtenir le MapObject correspondant a une clé dans un List
* \param name clé
* \param list Liste
* \return MapObject correspondant
* Note: Fonction interne, ne pas utiliser a moins de savoir ce que vous faites.*/
MapObject_t getMapObjectOccurence(List_t list, String_t name);
/*! \brief Obtenir le List contenant le MapObject correspondant a une clé dans un List
* \param name clé
* \param list Liste
* \return List correspondante
* Note: Fonction interne, ne pas utiliser a moins de savoir ce que vous faites.*/
List_t getMapObjectOccurenceList(List_t list, String_t name);
#ifdef __cplusplus
}
#endif
/*! \brief Raccourci pour le cast en Map_t
*
* \param a Pointeur
*/
#define Map(a) (struct Map*)(a)
/*! \brief Raccourci pour le cast en MapObject_t
*
* \param a Pointeur
*/
#define MapObject(a) (struct MapObject*)(a)
/*! \brief Raccourci pour free une map
*
* \param a Map concernée
*
* Equivalent de a = freeMap(a);
*/
#define fMap(a) a = freeMap(a);
/*! \brief Raccourci pour free une map avec libération de pointeurs
*
* \param a Map concernée
* \param f Fonction permettant de libérer les valeurs
*
* Equivalent de a = freeMapWithPtr(a, f);
*/
#define ffMap(a, f) a = freeMapWithPtr(a, f);
/*! \brief Raccourci pour afficher un MapObject
*
* \param a MapObject a afficher
* Fonctionne avec n'importe quel valeur contenue
*/
#define dMapObject(a) printf("[MapObject_t: %s = %p]\n", cString((*a).name), (*a).value);
/*! \brief Raccourci pour afficher un MapObject contenant un String
*
* \param a MapObject a afficher
* Fonctionne seulement si la valeur contenue est un String
*/
#define dsMapObject(a) printf("[MapObject_t: %s = %s]\n", cString((*a).name), cString(String((*a).value)));
#endif
