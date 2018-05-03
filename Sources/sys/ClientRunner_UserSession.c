#include "ClientRunner_UserSession.h"
#include "../utils/ReadInput.h"
#include "RequestTypes.h"
enum ClientRunnerMode ClientRunner_Login(Connexion_t connexion)
{

	if(connexion->user == 0)
	{
		AutoString_t login, password;
		printf("Connexion à un compte utilisateur:\n");
		login = ReadInputWithMsg(autoString("Login: "));
		password = ReadPasswordWithMsg(autoString("Mot de passe: "));

	}
	return MAIN_MENU;
}
enum ClientRunnerMode ClientRunner_Logout(Connexion_t connexion)
{
	if(connexion->user != 0)
	{
		//Ajouter la déconnexion (signal au serveur) ici
		connexion->user = JSONObject_delete(connexion->user);
		connexion->sid = JSONObject_delete(connexion->sid);
		printf("Deconnexion réussie.\n");
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
		Date_t birth = ReadDateWithMsg(AS("Date de naissance:"));
		JSONObject_t user = JSONObject_new();
		JSONObject_set(user, AS("Login"), JSONString_new(login));
		JSONObject_set(user, AS("Password"), JSONString_new(password));
		JSONObject_set(user, AS("Birth"), dateToJSON(birth));
		JSONObject_set(user, AS("Name"), JSONString_new(name));
		JSONObject_set(user, AS("FirstName"), JSONString_new(firstName));
		RequestAnswer a = Client_RegisterUser(connexion, user);
		birth = freeDate(birth);

	}
	return MAIN_MENU;
}
