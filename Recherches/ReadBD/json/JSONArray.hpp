/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONARRAY_HPP
#define JSONARRAY_HPP
#include "JSONValue.hpp"
#include "JSONTuple.hpp"
#include <string>
#include <vector>
/*! \brief JSONArray Représente un tableau en JSON */
class JSONArray : public JSONValue
{
private:
        std::vector<JSONObject*> value;
protected:
        virtual void imDead(JSONObject *child);
        using JSONObject::getInt;
        using JSONObject::getString;
        using JSONObject::getDouble;
        using JSONObject::getBoolean;
        using JSONObject::getArray;
        using JSONObject::remove;
        using JSONObject::detach;
	using JSONObject::newParent;
public:
        JSONArray();
	/*! \brief Construire un tableau JSON a partir d'un tableau C++
	\param arr Tableau d'objet JSONObject*/
        JSONArray(std::vector<JSONObject*> arr);
        virtual ~JSONArray();
        using JSONObject::getParent;
        using JSONObject::hasParent;
        virtual std::string asString(unsigned int tabs=0);
	/*! \brief Retourne l'objet de la position n du tableau
	* Permet d'obtenir un objet du type souhaité du tableau.
	* \return Objet de la case n du tableau.
	*/
        virtual JSONObject* get(unsigned int n);
	/*! \brief Retourne l'objet de la position n du tableau
	* Permet d'obtenir un objet du type souhaité du tableau.
	* \return Objet de la case n du tableau.
	*/
        virtual JSONInt* getInt(unsigned int n);
	/*! \brief Retourne l'objet de la position n du tableau
	* Permet d'obtenir un objet du type souhaité du tableau.
	* \return Objet de la case n du tableau.
	*/
	virtual JSONString* getString(unsigned int n);
	/*! \brief Retourne l'objet de la position n du tableau
	* Permet d'obtenir un objet du type souhaité du tableau.
	* \return Objet de la case n du tableau.
	*/
	virtual JSONDouble* getDouble(unsigned int n);
	/*! \brief Retourne l'objet de la position n du tableau
	* Permet d'obtenir un objet du type souhaité du tableau.
	* \return Objet de la case n du tableau.
	*/
	virtual JSONBoolean* getBoolean(unsigned int n);
	/*! \brief Retourne l'objet de la position n du tableau
	* Permet d'obtenir un objet du type souhaité du tableau.
	* \return Objet de la case n du tableau.
	*/
	virtual JSONArray* getArray(unsigned int n);
	/*! \brief Retourne la valeur de la position n du tableau
	* Permet d'obtenir une valeur du type souhaité du tableau.
	* \return Valeur de l'objet de la case n du tableau.
	*/
        virtual std::string stringValue(unsigned int n);
        virtual void detach(unsigned int n);
        virtual void detach(JSONObject* obj);
        virtual void detachAll();
	/*! \brief Retourne la valeur de la position n du tableau
	* Permet d'obtenir une valeur du type souhaité du tableau.
	* \return Valeur de l'objet de la case n du tableau.
	*/
	virtual int intValue(unsigned int n);
	/*! \brief Retourne la valeur de la position n du tableau
	* Permet d'obtenir une valeur du type souhaité du tableau.
	* \return Valeur de l'objet de la case n du tableau.
	*/
	virtual double doubleValue(unsigned int n);
	/*! \brief Retourne la valeur de la position n du tableau
	* Permet d'obtenir une valeur du type souhaité du tableau.
	* \return Valeur de l'objet de la case n du tableau.
	*/
	virtual bool booleanValue(unsigned int n);
	/*! \brief Changer la valeur d'une case du tableau
	* Met l'objet dans la case choisie du tableau.
	* \param obj Objet à placer
	* \param i Case du tableau
	*/
        void set(unsigned int i, JSONObject* obj);
	/*! \brief Retourne la taille du tableau
	* \return Taille du tableau */
        unsigned int size();
	/*! \brief Supprime un objet du tableau
	* Supprime un objet du tableau, et redimensionne le tableau.
	* Libère l'objet de la mémoire si destruct=true (défault)
	* \param i Position dans le tableau
	* \param destruct Si true, libère la mémoire de l'objet à la case i du tableau.
	*/
        virtual void remove(unsigned int i, bool destruct=true);
	/*! \brief Supprime un objet du tableau
	* Supprime un objet du tableau, et redimensionne le tableau.
	* Libère l'objet de la mémoire si destruct=true (défault)
	* \param obj Objet à supprimer
	* \param destruct Si true, libère la mémoire de l'objet à supprimer.
	*/
        virtual void remove(JSONObject* obj, bool destruct=true);
	/*! \brief Ajouter un objet au tableau
	* Ajoute le nouvel objet à la fin du tableau.
	* \param obj Objet à ajouter
	*/
        void add(JSONObject* obj);
	/*! \brief Ajouter un objet au tableau
	* Ajoute le nouvel objet à la fin du tableau.
	* \param child Objet à ajouter
	*/
        void add(int child);
	/*! \brief Ajouter un objet au tableau
	* Ajoute le nouvel objet à la fin du tableau.
	* \param child Objet à ajouter
	*/
	void add(double child);
	/*! \brief Ajouter un objet au tableau
	* Ajoute le nouvel objet à la fin du tableau.
	* \param child Objet à ajouter
	*/
	void add(std::string child);
	/*! \brief Ajouter un objet au tableau
	* Ajoute le nouvel objet à la fin du tableau.
	* \param child Objet à ajouter
	*/
	void add(bool child);
        virtual void clear();
        virtual bool assignArray(std::vector<JSONTuple> &arr);
        virtual bool assignArray(std::vector<JSONObject*> &arr);
        virtual bool equals(JSONObject* obj);
        virtual std::vector<JSONTuple> asVector();
};
#endif
