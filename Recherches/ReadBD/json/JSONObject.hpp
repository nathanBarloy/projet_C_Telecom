/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP
#include <string>
#include <vector>
#include <map>
//#include "JSONMap.hpp"
//#include "JSONTuple.hpp"
class JSONMap;
class JSONTuple;
class JSONInt;
class JSONString;
class JSONDouble;
class JSONBoolean;
class JSONArray;
/*!
* \brief JSONObject représente un noeud JSON.
*
* Tous les objets JSON héritent de JSONObject. Cette classe permet d'association de clés et de valeurs pour manipuler des données JSON.
* Tous les objets héritant de JSONObject sont convertibles en texte (json) et inversement.
* Un JSON Object représente ceci en JSON:
* {
*  "cle" : "valeur"
*  ...
* }
*
*
*
*/
class JSONObject
{
public:
	/*! \brief JSONType représente un type d'objet JSON.
	*
	* Permet de différencier par simple comparaison d'enum un type d'objet, les objets héritant de JSON mettent automatiquement à jour leur type pour les identifier plus simplement.
	*/
	typedef enum
	{
		OBJECT, ARRAY, VALUE, STRING, INT, DOUBLE, BOOLEAN, NULLOBJ
	}  JSONType;
protected:
	bool ignoreDead;
	virtual void imDead(JSONObject *child);
	void newParent(JSONObject* np);
	JSONType type;
	friend JSONArray;
private:
	JSONObject* parent;
	JSONMap* childs;
public:
	JSONObject();
	virtual ~JSONObject();
	/*! \brief Changer la valeur d'une clé
	* La clé est mise à jour, ou crée si inexistante.
	* \param name Nom de clé
	* \param child Valeur de clé
	* La valeur de clé peut être un JSONObject (et dérivés), ou un type "primitif".
	* Les types primitifs seront ajoutés sous forme de JSONObject dérivés.
	*/
	void set(std::string name, JSONObject* child);
	/*! \brief Changer la valeur d'une clé
	* La clé est mise à jour, ou crée si inexistante.
	* \param name Nom de clé
	* \param child Valeur de clé
	* La valeur de clé peut être un JSONObject (et dérivés), ou un type "primitif".
	* Les types primitifs seront ajoutés sous forme de JSONObject dérivés.
	*/
	void set(std::string name, int child);
	/*! \brief Changer la valeur d'une clé
	* La clé est mise à jour, ou crée si inexistante.
	* \param name Nom de clé
	* \param child Valeur de clé
	* La valeur de clé peut être un JSONObject (et dérivés), ou un type "primitif".
	* Les types primitifs seront ajoutés sous forme de JSONObject dérivés.
	*/
	void set(std::string name, double child);
	/*! \brief Changer la valeur d'une clé
	* La clé est mise à jour, ou crée si inexistante.
	* \param name Nom de clé
	* \param child Valeur de clé
	* La valeur de clé peut être un JSONObject (et dérivés), ou un type "primitif".
	* Les types primitifs seront ajoutés sous forme de JSONObject dérivés.
	*/
	void set(std::string name, std::string child);
	/*! \brief Changer la valeur d'une clé
	* La clé est mise à jour, ou crée si inexistante.
	* \param name Nom de clé
	* \param child Valeur de clé
	* La valeur de clé peut être un JSONObject (et dérivés), ou un type "primitif".
	* Les types primitifs seront ajoutés sous forme de JSONObject dérivés.
	*/
	void set(std::string name, bool child);
	/*! \brief Supprimer une clé
	* La clé est supprimée, rien ne se passe si la clé n'existait pas.
	* \param name Nom de clé
	* \param destruct Libérer de la mémoire l'objet correspondant (défault: true)
	*/
	virtual void remove(std::string name, bool destruct=true);
	/*! \brief Supprimer une clé
	* La clé est supprimée, rien ne se passe si la clé n'existait pas.
	* \param obj JSONObject à supprimer de la clé correspondante
	* \param destruct Libérer de la mémoire l'objet correspondant (défault: true)
	*/
	virtual void remove(JSONObject* obj, bool destruct=true);
	/*! \brief Détache un objet d'une clé
	* Equivalent de remove avec detruct=true.
	* \param name Nom de clé
	*/
	virtual void detach(std::string name);
	/*! \brief Détache un objet d'une clé
	* Equivalent de remove avec detruct=true.
	* \param obj Objet a supprimer de la clé correspondante
	*/
	virtual void detach(JSONObject* obj);
	/*! \brief Détache tous les objets
	* Détache tous les objets contenus et les libère de la mémoire.
	*/
	virtual void detachAll();
	/*! \brief Obtenir la clé correspondant à un objet
	* Permet de retrouver le nom d'une clé a partir de la valeur.
	* \param child Objet a rechercher
	* \return Clé correspondante
	*/
	std::string get(JSONObject* child);
	/*! \brief Obtenir la valeur d'une clé
	* Permet d'obtenir la valeur d'une clé, retourne 0 si la clé n'existe pas.
	* \param name Nom de la clé pour laquelle obtenir la valeur
	* \return La valeur de la clé, ou 0 si la clé n'existe pas.
	*/
	virtual JSONObject* get(std::string name);
	/*! \brief Obtenir la valeur d'une clé
	* Permet d'obtenir la valeur d'une clé, retourne 0 si la clé n'existe pas.
	* \param name Nom de la clé pour laquelle obtenir la valeur
	* \return La valeur de la clé, ou 0 si la clé n'existe pas.
	*/
	virtual JSONInt* getInt(std::string name);
	/*! \brief Obtenir la valeur d'une clé
	* Permet d'obtenir la valeur d'une clé, retourne 0 si la clé n'existe pas.
	* \param name Nom de la clé pour laquelle obtenir la valeur
	* \return La valeur de la clé, ou 0 si la clé n'existe pas.
	*/
	virtual JSONString* getString(std::string name);
	/*! \brief Obtenir la valeur d'une clé
	* Permet d'obtenir la valeur d'une clé, retourne 0 si la clé n'existe pas.
	* \param name Nom de la clé pour laquelle obtenir la valeur
	* \return La valeur de la clé, ou 0 si la clé n'existe pas.
	*/
	virtual JSONDouble* getDouble(std::string name);
	/*! \brief Obtenir la valeur d'une clé
	* Permet d'obtenir la valeur d'une clé, retourne 0 si la clé n'existe pas.
	* \param name Nom de la clé pour laquelle obtenir la valeur
	* \return La valeur de la clé, ou 0 si la clé n'existe pas.
	*/
	virtual JSONBoolean* getBoolean(std::string name);
	/*! \brief Obtenir la valeur d'une clé
	* Permet d'obtenir la valeur d'une clé, retourne 0 si la clé n'existe pas.
	* \param name Nom de la clé pour laquelle obtenir la valeur
	* \return La valeur de la clé, ou 0 si la clé n'existe pas.
	*/
	virtual JSONArray* getArray(std::string name);
	/*! \brief Obtenir la valeur d'une clé en type primitif
	* Permet d'obtenir la valeur d'une clé, retourne 0 si la clé n'existe pas.
	* \param name Nom de la clé pour laquelle obtenir la valeur
	* \return La valeur de la clé, ou 0 si la clé n'existe pas.
	*/
	virtual std::string stringValue(std::string name);
	/*! \brief Obtenir la valeur d'une clé en type primitif
	* Permet d'obtenir la valeur d'une clé, retourne 0 si la clé n'existe pas.
	* \param name Nom de la clé pour laquelle obtenir la valeur
	* \return La valeur de la clé, ou 0 si la clé n'existe pas.
	*/
	virtual int intValue(std::string name);
	/*! \brief Obtenir la valeur d'une clé en type primitif
	* Permet d'obtenir la valeur d'une clé, retourne 0 si la clé n'existe pas.
	* \param name Nom de la clé pour laquelle obtenir la valeur
	* \return La valeur de la clé, ou 0 si la clé n'existe pas.
	*/
	virtual double doubleValue(std::string name);
	/*! \brief Obtenir la valeur d'une clé en type primitif
	* Permet d'obtenir la valeur d'une clé, retourne 0 si la clé n'existe pas.
	* \param name Nom de la clé pour laquelle obtenir la valeur
	* \return La valeur de la clé, ou 0 si la clé n'existe pas.
	*/
	virtual bool booleanValue(std::string name);
	/*! \brief Retourne le type primitif correspondant pour l'objet actuel
	* Permet d'obtenir la représentation de la valeur JSON de l'objet actuel dans le type primitif correspondant.
	* En cas d'erreur de conversion dans le type demandé, 0 sera retourné.
	* \return Valeur de l'objet dans le type choisi.
	*/
	virtual std::string stringValue();
	/*! \brief Retourne le type primitif correspondant pour l'objet actuel
	* Permet d'obtenir la représentation de la valeur JSON de l'objet actuel dans le type primitif correspondant.
	* En cas d'erreur de conversion dans le type demandé, 0 sera retourné.
	* \return Valeur de l'objet dans le type choisi.
	*/
	virtual int intValue();
	/*! \brief Retourne le type primitif correspondant pour l'objet actuel
	* Permet d'obtenir la représentation de la valeur JSON de l'objet actuel dans le type primitif correspondant.
	* En cas d'erreur de conversion dans le type demandé, 0 sera retourné.
	* \return Valeur de l'objet dans le type choisi.
	*/
	virtual double doubleValue();
	/*! \brief Retourne le type primitif correspondant pour l'objet actuel
	* Permet d'obtenir la représentation de la valeur JSON de l'objet actuel dans le type primitif correspondant.
	* En cas d'erreur de conversion dans le type demandé, 0 sera retourné.
	* \return Valeur de l'objet dans le type choisi.
	*/
	virtual bool booleanValue();
	/*! \brief Transforme l'objet en JSON (texte)
	* L'objet ainsi que son contenu sera transformé dans sa représentation JSON.
	* La sortie générée sera instanciable à nouveau à l'identique avec JSONParser.
	* \param tabs Défini le nombre de tabulations à rajouter, défault: 0
	* \return JSON, texte sous forme de std::string.
	*/
	virtual std::string asString(unsigned int tabs=0);
	/*! \brief Retourne le parent
	* \return JSONObject parent
	*/
	JSONObject* getParent();
	/*! \brief Tester l'existance d'un parent
	* \return Renvoie true si un parent existe pour cet objet, renvoie false sinon.
	*/
	bool hasParent();
	/*! \brief Exporter la liste associative sous forme de tableau
	* Permet d'obtenir un tableau contenant les associations clés/valeurs de l'objet.
	* Ne génère aucune nouvelle instance d'objets.
	* \return Tableau contenant les clés et valeurs de l'objet courant.
	*/
	virtual std::vector<JSONTuple> asVector();
	/*! \brief Obtenir le type JSONType de l'objet
	* Retourne le type de l'objet, permettant des filtrages simplifiés.
	* \return JSONType de l'objet.
	*/
	JSONType getType();
	/*! \brief Teste l'égalité de 2 JSONObject
	* Permet de tester si les données contenues sont identiques ou non.
	*/
	virtual bool equals(JSONObject* obj);
	/*! \brief Nettoie l'objet
	* Nettoie les associations clés/valeurs, ou un tableau dans le cas d'un JSONArray.
	* Permet aussi de réinitialiser des objets de type JSONValue à leur valeur par défaut.
	* Note: Ne libère pas les objets associés de la mémoire.
	*/
	virtual void clear();
	/*! \brief Assigner un JSONObject à un autre
	* Permet de transférer le contenu d'un JSONObject à un autre.
	* Note: Echoue si le pointeur passé est nul.
	* Note: L'objet ajoute les données du nouvel objet aux siennes, ses anciennes données sont préservées.
	* \param obj Objet à copier
	* \return Retourne true en cas de réussite, false en cas d'échec.
	*/
	virtual bool assign(JSONObject *obj);
	/*! \brief Assigner un tableau exporté a un JSONObject
	* Permet de réintégrer un tableau de données dans un JSONObject.
	* Note: L'objet ajoute les données du tableau aux siennes, ses anciennes données sont préservées.
	* \param arr Tableau de données à assigner
	* \return Retourne true en cas de réussite, false en cas d'échec (n'échoue normalement jamais)
	*/
	virtual bool assignArray(std::vector<JSONTuple>& arr);
};
#endif
