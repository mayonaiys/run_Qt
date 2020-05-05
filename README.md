# Run
Run est un jeu de parcours développé en C++/Qt dans le cadre d'un projet noté.
Les consignes étaient les suivantes : créer un jeu d'un objet qui saute des obtacles/trous en utilisant les flèches du clavier,
mémoriser le meilleur temps, avoir au moins une vue centrée sur le joueur, partie esthétique libre, pouvoir recommencer une partie à la fin ou quitter le jeu, proposer des améliorations.

## Description
Run est un jeu de parcours dont le but est de finir chaque niveau le plus rapidement possbile.
Les niveaux sont composés de plateformes (parfois mouvantes), d'obstacles (parfois mouvants) et de ravins.
Il est possible de jouer en solo ou en multijoueur (sur un même clavier). 
Les touches des joueurs sont personnalisables dans un menu prévu à cet effet.
Il suffit de finir un niveau en solo pour débloquer le niveau suivant.
Un classement est disponible pour chaque niveau afin de voir qui l'a fini le plus vite.

## Jouer
Pour jouer au jeu il suffit d'ouvrir le projet sur [Clion](https://www.jetbrains.com/fr-fr/clion/) et de lancer [Xming](https://sourceforge.net/projects/xming/).
Dans Clion il faudra aller dans Run>EditConfigurations et écrire : DISPLAY=:0.0 dans Environnement variables.
Suite à cela, plus qu'a lancer le jeu!

Les touches de bases pour le premier joueur sont : flèche du haut (saut), flèche de gauche (courir à gauche), flèche de droite (courir à droite)

Celles pour le second joueur (dans le cas d'une partie multijoueur) sont : Z (saut), Q (courir à gauche), D (courir à droite)

En jeu il suffit d'appuyer sur la touche echap pour ouvrir le menu de pause (de même pour quitter). 

(En pause, si l'on clique sur le bouton résume pour reprendre le jeu, il faut cliquer sur la fenêtre car Windows enlève le focus sur la scène).


## Contributions
Toute contribution est la bienvenue. 
Chacun est libre de récupérer le code source et l'améliorer ou de tout simplement proposer des idées d'améliorations possibles.

## License
[MIT](https://choosealicense.com/licenses/mit/)