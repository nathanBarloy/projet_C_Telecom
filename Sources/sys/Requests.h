#ifndef REQUESTS_H
#define REQUESTS_H
#include <Map/Map.h>
#include <JSONAll.h>
#include "../utils/Client.h"
#include "RequestTypes.h"

//Assignations
Map_t getRequestsMap();//Renvoie les assignations nom/fonction

//Génération de JSON
JSONObject_t newJSONRequestAnswer(int id, int code, String_t error, JSONObject_t content);

//Execution
RequestAnswer execRequest(Client client, RequestQuery request);//Execute une requête


//Requêtes
RequestAnswer ServerRequest_prints(Client client, RequestQuery request);
RequestAnswer ServerRequest_exists(Client client, RequestQuery request);



//MACROS DE FACILITES

//Pour la RequestQuery request, crée la variable du nom défini par le paramètre query, et lui assigne le détail de la requête, renvoie une erreur au client si Query n'existe pas.
#define RequestQuery(request,query) JSONObject_t query = JSONObject_get(request->obj, autoString("Query")); if(query == 0){return newRequestAnswer(5, newJSONRequestAnswer(request->id, 5, autoString("Impossible de trouver l'attribut de requête: Query."), JSONObject_new()));}
//Pour RequestQuery request, crée la variable du nom défini par le paramètre varName a partir de la clé "keyName" (char*) de JSONObject_t obj.
#define RequestObject(request,obj,keyName,varName) JSONObject_t varName = JSONObject_get(obj, autoString(keyName)); if(varName == 0){return newRequestAnswer(5, newJSONRequestAnswer(request->id, 5, autoConcatNString(3, "Impossible de trouver l'attribut de requête: ", keyName, "."), JSONObject_new()));}
//Pour RequestQuery request, et JSONObject_t content (peut être nul), retourner une réponse affirmative a un client.
#define RequestAnswerOk(request,content) newRequestAnswer(0, newJSONRequestAnswer(request->id, 0, autoString(""), (content == 0 ? JSONObject_new() : content)));
//Pour RequestQuery request, et JSONObject_t content (peut être nul), errorCode (int), errorString String_t, retourner une réponse négative avec un code d'erreur et un message d'erreur
#define RequestAnswerError(request,content,errorCode, errorString) newRequestAnswer(errorCode, newJSONRequestAnswer(request->id, 0, errorString, (content == 0 ? JSONObject_new() : content)));
#endif
