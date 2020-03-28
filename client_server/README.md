# Description
L'archive td8-contents.tar contient les fichiers suivants :
- le fichier README.md, que vous êtes en train de lire ;
- le fichier lottery.cfg, fichier de configuration exemple que vous pouvez
  donner au serveur pour lancer une lotterie, sa description est donnée
  plus bas ;
  
- Le programme utilise un bibliothéque data_lottory.h, cette dernière contient 
  les fonctions qui permert de récupérer le numéro du lottory, le nombre de chiffre
  correspondant ainsi que le gain associé et des fonctions de vérifications si le 
  client a gagné ou pas.

-Le programme utilise deux tubes nommés, celui du client pour envoyer au serveur des messages
   et celui du serveur pour envoyer au client des message.

- le fichier scenario-test.sh (exécutable), script de test effectuant des
  scénario.

# Utilisation
Pour utiliser directement le script de test, veuillez le lancer dans le même
répertoire que votre application, appelée 'million' :
```
$ ./scenario-test.sh
```

Sinon, vous pouvez changer la valeur de la variable EXEC, pour cibler votre
exécutable. **ATTENTION, les scénarii cibleront un exécutable nommé 'million'.**

# Configuration
Le fichier de configuration est détaillé ici :
```
4                   # nombre de numéros
6 25 18 39          # numéros gagnants
4 9865              # gain pour 4 chiffres
3 345               # gain pour 3 chiffres
2 19                # gain pour 2 chiffres
1 2                 # gain pour 1 chiffre
```
