# Structures des pages web en JSON
```
{
	"title" : "Initialization...",
	"url" : "exec://init.json",
	"body" : [{"file" : {"name" : "init.html"}}],
	"head" : [
		{"tag": {
			"name" : "meta",
			"attributes" : [{"name" : "http-equiv", "value" : "refresh"}, {"name" : "content", "value" : "1;url=exec://boot.json"}],
			"ifconnected" : false
			}
		},
		{
			"tag" :
			{
				"name" : "meta",
				"attributes" : [{"name" : "http-equiv", "value" : "refresh"}, {"name" : "content", "value" : "1;url=exec://menu.json"}],
				"ifconnected" : true,
			}
		}
		]
}
```
Exemple sur le fichier d'initialisation:
- "title" : correspond au titre affiché dans la fenêtre
- "url" : correspond a l'url de la page actuelle
- "body" : section contenant des information sur le contenu de la page (array)
- "head" : section contennant des informations sur le head de la page (array)
- "scripts" : section contenant des informations sur les scripts de la page (array de string = nom des fichiers)
- "styles" : section contenant des informations sur le css de la page (array de string = nom des fichiers)

Les sections body et head contiennent un tableau de conteneur (voir définition plus bas).

## Conteneur
Le conteneur peut permettre l'insertion de contenus, fichiers et code généré.

```
[
	{
		"file" :
		{
			"name" : "fichier",
			//+params
		}
	}
]
```
Ou

```
[
	{
		"tag" :
		{
			"name" : "type d'element html",
			"attributes": [attribute ...],
			"value" : "Contenu text, entre les 2 balises html. Monobalise si innexistant."
			"childs" : [container],
			//+params
		}
	}
}
```

Ou:

```
[
	{
		"function" : "fctName"
		//+params
	}
]
```
- "childs" : est facultatif, il contient un array permettant d'inclure des conteneurs dans celui ci.

Params:
- "ifconnected" : Si présent, permet d'afficher un élément uniquement si il répond a la condition. "true" = requiert d'être connecté a un serveur, "false" : "requiert de ne pas être connecté a un serveur"
- "iflogged" : Si présent, permet d'afficher un élément uniquement si il répond à la condition. "true" : Requiert que l'utilisateur soit authentifié. "false" : "requiert que l'utilisateur ne soit pas authentifié."
