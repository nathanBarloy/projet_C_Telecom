/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONEXCEPTION_HPP
#define JSONEXCEPTION_HPP
#include <string>
/*! \brief JSONException est lancée en cas d'exception avec JSONParser */
class JSONException
{
        size_t line, col;
        std::string msg;
public:
        JSONException(size_t line, size_t col, std::string msg=std::string());
	/*! \brief Obtenir la ligne de l'erreur dans le JSON
	* \return Ligne dans le JSON à parser
	*/
        size_t getLine();
	/*! \brief Obtenir la colonne de l'erreur dans le JSON
	* \return Colonne dans le JSON à parser
	*/
        size_t getCol();
	/*! \brief Retourne l'erreur sous forme de string.
	* Il est recommandé d'utiliser cette fonction pour générer des messages propres.
	* \return String contenant le détail de l'erreur produite. */
        std::string asString();
	/*! \brief Retourne le message d'erreur sans informations complémentaires
	* Retourne le message de l'erreur obtenue, ne renvoie aucune autre information comme par exemple la ligne ou la colonne.
	*  \return Message d'erreur
	*/
        std::string getMsg();
};
#endif
