## Expliquer en quoi cette construction « sur la pile » est limitée dès qu’on souhaite insérer ou supprimer des nœuds à l’exécution. Et si cette construction est compatible avec malloc et free (1 pt)
  1. Etant alloué dans la pile, ils restent uniquement accessible dans le bloc de code où ils sont allouée
  2. La pile ne supporte pas la création dynamique, elle n'est donc pas modifiable ( on ne peux pas ajouter de nouveau noeud) pour faire cela il faudrat recréer tout l'objet complet, supprimer quant a lui ne permet pas de libérer, seul mettre l'adresse à null à la limite mais le sdonnées sont toujours là, donc le nombre de noeud est fixe
  3. quant à la comptabilité mallo et free, oui elle peut etre compatible mais il faut changer la manière de faire, allouer un nouveau noeud avec malloc, remplire ces donner uis effectuer les connections, pour supprimer d'abord detacher des autres noeud, et free pour liberer la memoire on maitrise donc encore mieux le cycle de vie des objets
## Ecrire un main de base qui déclare cette variable root pour la suite (0.5 pt)
  
## Est-ce un BST en suposant l’ordre alphabétique ? (1 pt)
