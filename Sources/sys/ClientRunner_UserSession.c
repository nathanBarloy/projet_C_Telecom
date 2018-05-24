#include "ClientRunner_UserSession.h"
#include "../utils/ReadInput.h"
#include "RequestTypes.h"
#include "ClientRequests.h"
#include <unistd.h>
enum ClientRunnerMode ClientRunner_Login(Connexion_t connexion)
{

	if(connexion->user == 0)
	{
		AutoString_t login, password;
		printf("Connexion à un compte utilisateur:\n");
		login = ReadInputWithMsg(autoString("Login: "));
		password = ReadPasswordWithMsg(autoString("Mot de passe: "));
		JSONObject_t obj = JSONObject_new();
		JSONObject_set(obj, AS("Login"), JSONString_new(login));
		JSONObject_set(obj, AS("Password"), JSONString_new(password));
		RequestAnswer a = Client_Login(connexion, obj);
		if(a != 0)
		{
			if(a->code == 0)
			{
				if(connexion->sid != 0)
				{
					fString(connexion->sid);
				}

				JSONObject_t ans = JSONObject_get(a->obj, AS("Answer")), u = 0;
				if(ans != 0)
				{
					u = JSONObject_get(ans, AS("User"));
				}
				if(u != 0)
				{
					connexion->user = JSONObject_getCopy(u);
					connexion->sid = newStringFromString(JSONObject_stringValueOf(ans, AS("SessionId")));
					printf("Connexion réussie !\n");
				}
				else
				{
					printf("Réponse invalide du serveur....\n");
				}
			}
			else
			{
				printf("Erreur de connexion: %s\n", cStringValueOf(a->obj, "Error"));
			}
			freeRequestAnswer(a);
		}
		else
		{
			printf("Echec de connexion au serveur.\n");
		}

	}
	return MAIN_MENU;
}
enum ClientRunnerMode ClientRunner_Logout(Connexion_t connexion)
{
	if(connexion->user != 0)
	{
		//Ajouter la déconnexion (signal au serveur) ici
		RequestAnswer a = Client_Logout(connexion);
		if(a != 0)
		{
			if(a->code == 0)
			{
				printf("Deconnexion réussie.\n");
			}
			else
			{
				printf("Deconnexion forcée: Vous n'êtes pas connectés.\n");
			}
			connexion->user = JSONObject_delete(connexion->user);
			fString(connexion->sid);
			freeRequestAnswer(a);
		}
		else
		{
			printf("Deconnexion impossible: Echec de connexion.\n");
		}
	}
	return MAIN_MENU;
}
enum ClientRunnerMode ClientRunner_Register(Connexion_t connexion)
{
	if(connexion->user == 0)
	{
		AutoString_t login, password, name, firstName;
		login = ReadInputWithMsg(autoString("Login: "));
		password = ReadPasswordWithMsg(autoString("Mot de passe: "));
		firstName = ReadInputWithMsg(AS("Prenom: "));
		name = ReadInputWithMsg(AS("Nom: "));
		Date_t birth = ReadDateWithMsg(AS("Date de naissance:\n"));
		JSONObject_t user = JSONObject_new();
		JSONObject_set(user, AS("Login"), JSONString_new(login));
		JSONObject_set(user, AS("Password"), JSONString_new(password));
		JSONObject_set(user, AS("Birth"), dateToJSON(birth));
		JSONObject_set(user, AS("Name"), JSONString_new(name));
		JSONObject_set(user, AS("FirstName"), JSONString_new(firstName));
		RequestAnswer a = Client_RegisterUser(connexion, user);
		birth = freeDate(birth);
		if(a->code == 0)
		{
			printf("Vous avez bien été enregistré.\n");
		}
		else
		{
			printf("Une erreur est survenue durant l'enregistrement:\n%s\n", cString(JSONObject_stringValueOf(a->obj, AS("Error"))));
		}
		freeRequestAnswer(a);
		ReadInputWithMsg(AS("Appuyez sur enter pour continuer."));
	}
	return MAIN_MENU;
}
