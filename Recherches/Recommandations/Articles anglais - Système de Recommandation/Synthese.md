# Système de notation / Appréciation humaine active
## Notation ordonnée
L'utilisateur donne son avis sur un produit en lui attribuant une note (généralement entre 1 et 5).  
**Avantages** : Plus de nuances possibles, ce qui permet par la suite d'établir des recommandations plus précises  
**Inconvénients** : Coût en calcul plus élevé.

## Notation binaire
L'avis de l'utilisateur sur un produit est simplifié par "J'aime" / "J'aime pas".  
**Avantage** : Coût en calcul plus faible, choix simplifié pour l'utilisateur  
**Inconvénient** : Moins de nuances possible

## Notation Unaire
On a uniquement l'information sur si l'utilisateur a aimé un film  
**Inconvénient** : pas d'information sur les films que l'utilisateur n'a pas aimé  
**Avantages** :  

# Filtrage par le contenu
## Système de Ringo
Utilise le principe de filtrage collaboratif + système de notation manuel
* Un utilisateur est comparé à tous les autres  
Calcul de similarité  (1) p.5 - Etat de l'art Nicolas Bechet 	
* Les utilisateurs ayant obtenu un score supérieur à un certain seuil sont conservés (considérés comme proche de l'utilsatuer cible)
* On fait la moyenne des scores / notations de chaque items de chaque utilsateur
* On ordonne ces résultats, ce qui donne une liste de recommandation pour l'utilsateur

## Assistant personnel Letizia (système filtrage basé sur contenu)

## Système NEWT (pertinence utilisateur)
Mise à jour dynamique des choix utilisateur

## Système conexe (Zhan and Callan 2002)
Construire un profil utilisateur en fonction de ses goûts.  
Utilisé plus dans la recherche de redondance entre documents  
Mesure Cosinus est la plus performante (taux d'erreur : 18,7%)

## Système LIBRA (recommandation livres Amazon) : [Kent and of Pittsburgh
On part d'une thématique (ex : un genre) pour produire des recommandations adépatés

* Extraction information : A partir d'une thématique, une liste de livres est sélectionnée (information du produit extraite à partir du titre, auteur... utilisant des patrons)
* Evaluation utilisateur : Notation par l'utilsateur des produits sélectionnées
* Apprentissage de profils : Choix des utilisateurs sont analysés par un classificateur **Bayesien**
* Recommandation : d'après le profil utilisateur obtenu, de nouveaux livres sont proposés

## Avantage / Inconvénient des systèmes de recommandation basé sur le contenu
### Avantage
Pas besoin de connaître l'utilisateur. On a juste besoin de connaitre les notes données ainsi que les infos sur les produits.
### Inconvénients
Problème de redondance : L'utilisateur ne se verra proposé que des produits en lien direct avec se qu'il connait déjà.
**Solution ?** : Algo de classification permettant des recommandations pseudo-aléatoire (comme algo génétiques)

## Construction du profil utilisateur
Méthode triviale : modèle vectoriel de Salton
