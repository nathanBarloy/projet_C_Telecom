/*******************************************************************************
********************************************************************************
******************        libjson, C++  Library        *************************
******************     ©2017 - 2018 Valentin CRÔNE     *************************
******************         All Rights Reserved         *************************
****************** This is a part of the JSON project. *************************
********************************************************************************
********************************************************************************
*******************************************************************************/


#ifndef JSONPOCOBASE_HPP
#define JSONPOCOBASE_HPP
/*! \brief JSONPOCOBase sert de tronc commun entre les classes POCO
* POCO pour plain old C++ Object, similaire au POJO.
* Cette classe permet d'avoir un tronc commun entre les 2 classes de base servant au POCO.
* Cela permet d'avoir un type statique commun n'étant pas un JSONObject et concernant uniquement les classes POCO.
*/
class JSONPOCOBase
{
	public:
	virtual ~JSONPOCOBase();
};
#endif
