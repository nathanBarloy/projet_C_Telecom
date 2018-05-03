# Protocole de transfert de données
## Requête au serveur
Toutes les requêtes doivent suivre le format suivant:
```
{
	"Sid" : "",
	"Type" : "",
	"Query" : {queryObject}
}
```
- Sid peut être vide si l'utilisateur n'est pas connecté, correspond a l'id de session
- Type correspond au type de requête
- Query contient l'objet json des données de la requête
## Réponse
```
{
	"Type" : "",
	"Time" : 0,
	"Status" : 0,
	"Error" : "",
	"Answer" : {answerObject}
}
```
- Id correspond l'id de la reponse
- Type correspond au type de réponse
- Time correspond a la date de génération de la reponse (timestamp)
- Status correspond au code de status de la requête, permet de voir si une erreur a eu lieu ou non
- Error correspond au message d'erreur lié a la requête en cas d'erreur
- Answer contient l'objet json contenant les données de la réponse, peut être vide en cas d'erreur.

# Requêtes
Tous ces objets représente un queryObject
## Demande de connexion à un compte utilisateur
Type: "connect"
```
{
	"Login" : "",
	"Password" : ""
}
```
Reponse: "connectAnswer"

## Demande de déconnexion d'un utilisateur
Type: "disconnect"
```
{

}
```
- Utilise le SID de la requête
Reponse: "disconnectAnswer"

## Enregistrement d'un utilisateur

Type: "registerUser"
```
{User}
```
Transmet un utilisateur comme objet de requête.
Les champs requis sont: Name, FirstName, Login, Password, Birth.
Les autres champs seront ignorés par le serveur et ne sont donc pas indispensables.



# Réponses
## Réponse de connexion d'utilisateur
Type: "connectAnswer"
```
{
	"Login" : "",
	"Sid": "",
}
```
## Réponse de déconnexion d'un utilisateur
Type: "disconnectAnswer"
```
{

}
```

## Réponse d'enregistrement d'un utilisateur

Type: "registerUserAnswer"
```
{
	"Registered" : bool,
	"Cause" : ""
}
```
Renvoie true dans "Registered" si l'utilisateur a bien été enregistré. False en cas d'erreur.
Si false, cause contiendra un mot clé permettant de comprendre l'erreur:
- Login: Le login est déjà utilisé.
- Password: Le mot de passe est invalide, ou trop court (mini 4 caractères)
