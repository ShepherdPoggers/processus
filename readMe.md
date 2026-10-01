# Familiarisation avec Linux et gestion des processus

## Auteurs
- SHEE15060600, Shepherd, Elliot
- DESA07010400, Desbiens, Anthony

## Compilation du code

Pour lancer le shell, il suffit d'exécuter :
```bash
g++ src/*.cpp -o shell
./shell
```

## Utilisation de random

Tous les fichiers d'historique sont enregistrés dans le dossier `historique/`.
Les commandes de l'exécution aléatoire sont toutes enregistrées dans `historique/historiqueX_Complet`.
Les 5 dernières commandes sont aussi enregistrées à une fréquence f dans `historique/historiqueX_Y`.

La fonction random s'utilise comme suit :
```bash
random <nombreCommandes> <frequenceSauvegarde>
```
Où :
- `<nombreCommandes>` représente le nombre de commandes aléatoires qui seront exécutées ;
- `<frequenceSauvegarde>` représente la fréquence à laquelle on écrit un fichier d'historique.
