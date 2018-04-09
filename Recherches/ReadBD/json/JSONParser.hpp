/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP
#include "JSONAll.hpp"
#include <string>
/*! \brief JSONParser permet de parser des chaines ou fichiers en JSON.
*/
class JSONParser
{
private:
	typedef enum
	{
		DETECTION, READSTRING, READNUMBER, READBOOLEAN, READNULL, SEPARATOR
	} JSONParseState;
	typedef enum
	{
		KEY, VALUE
	}
	JSONParseObject;
	static void newLine(size_t& line, size_t& col);
	static void error(size_t& line, size_t& col, std::string msg=std::string());
	static void goBack(size_t& line, size_t& col, size_t& entityCursor, char* str);
public:
	/*! \brief Parser une chaine JSON
	* \param str Chaine à parser
	* \return Structure JSONObject correspondante
	*/
	static JSONObject* parse(const char * str);
	/*! \brief Parser une chaine JSON
	* \param str Chaine à parser
	* \return Structure JSONObject correspondante
	*/
	static JSONObject* parse(std::string str);
	/*! \brief Parser un fichier JSON
	* \param fileName Fichier à parser
	* \return Structure JSONObject correspondante
	*/
	static JSONObject* parseFile(const char *fileName);
	/*! \brief Parser un fichier JSON
	* \param fileName Fichier à parser
	* \return Structure JSONObject correspondante
	*/
	static JSONObject* parseFile(std::string fileName);
	/*! \brief Sauvegarder un fichier JSON
	* \param obj Structure JSON à sauvegarder
	* \param fileName Fichier de destination
	*/
	static bool saveFile(JSONObject* obj, const char* fileName);
	/*! \brief Sauvegarder un fichier JSON
	* \param obj Structure JSON à sauvegarder
	* \param fileName Fichier de destination
	*/
	static bool saveFile(JSONObject* obj, std::string fileName);
};
#endif
