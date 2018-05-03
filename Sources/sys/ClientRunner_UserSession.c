#include "ClientRunner_UserSession.h"
#include "../utils/ReadInput.h"
enum ClientRunnerMode ClientRunner_Login(Connexion_t connexion)
{

	if(connexion->user == 0)
	{
		AutoString_t login, password;
		printf("Connexion à un compte utilisateur:\n");
		login = ReadInputWithMsg(autoString("Login: "));
		password = ReadInputWithMsg(autoString("Mot de passe: "));

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


	}
	return MAIN_MENU;
}
