# LearningMan

## Description
LearningMan est un jeu de plateforme avec une IA entrainable mise à disposition. 
Le jeu se décompose en deux parties : 

Une partie jouable par l’utilisateur, qui doit battre le boss d’un niveau et obtenir le meilleur score possible (grâce au temps de réalisation du niveau et au nombre d’ennemis tués). 

L’autre partie consiste à faire entraîner et jouer des modèles d’intelligence artificielle afin que ceux-ci finissent le niveau et obtiennent les meilleurs scores possibles. Les modèles peuvent être sauvegardés et chargés par la suite pour pouvoir continuer un apprentissage plus tard.

Le jeu est lié à un site, qui dispose d’un tableau des meilleurs scores avec la possibilité de télécharger les modèles d’IA. Une partie statistique permet aussi de voir des données sur l’ensemble des joueurs ayant joué au jeu
(Le site n'est aujourd'hui plus actif en raison du coût pour le maintenir allumé).

## Jeu
Les actions disponibles par le joueur et l'IA sont le tir, le saut et le déplacement horizontal
Ci-dessous des images du jeu (avec les carrés rouges qui ne peuvent être affichés que durement l'entraînement du modèle)
![image](https://user-images.githubusercontent.com/37442009/189716704-26c68e01-8dad-41fe-9763-c86b12789b49.png)

## Site 
Le scoreboard où l’on peut voir les meilleurs score des joueurs et IA ayant joué
![image](https://user-images.githubusercontent.com/37442009/189717513-e7d7c3a3-5743-408a-91c4-8fd5ef64a371.png)

Page constituée de différentes statistiques concernant les données des parties jouées
![image](https://user-images.githubusercontent.com/37442009/189717660-2e7b59cc-10ca-4b24-8251-155665313182.png)

## Résultats
En utilisant du Q-Learning on a réussi à obtenir de bons résultats permettant au modèle de finir le niveau et assez rapidement. 
Plus rapidement qu'un joueur peu expérimenté mais moins que quelqu'un qui rush et connaît bien le jeu. 
