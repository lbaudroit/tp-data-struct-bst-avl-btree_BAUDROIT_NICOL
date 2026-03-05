# Insertion de valeurs
On push successivement 1, 2, 3, 4, 5 dans une structure `s`

## 1. Séquence de valeurs affichées si `s` se comporte comme une pile (LIFO)
Dans le cas d'une pile, les éléments sont ajoutés successivement vers la fin.
On a donc 1, 2, 3, 4, 5
En appelant `pop()` 5 fois, on obtient les derniers éléments ajoutés
On a donc 5, 4, 3, 2, 1

## 2. Séquence de valeurs affichées si `s` se comporte comme une file (FIFO)
Dans le cas d'une pile, les éléments sont ajoutés successivement vers la fin.
On a donc 1, 2, 3, 4, 5
En appelant `pop()` 5 fois, on obtient les premiers éléments ajoutés
On a donc 1, 2, 3, 4, 5

## 3. Inversion des opérations de push
On garde la même logique si on insère dans l'ordre décroissant.
Une pile nous donnera les valeurs dans l'ordre inverse, donc 1, 2, 3, 4, 5
Une file nous restituera les valeurs dans l'ordre, càd 5, 4, 3, 2, 1

# Evaluation d'expression
## 1. Séquence d'opérations sur une pile
On va effectuer 3 pop() pour récupérer les éléments à calculer (les deux opérandes et l'opérateur). 
On effectue le calcul correspondant et on push() le résultat.
On reproduit ces opérations tant que l'on peut effectuer des opérations (3 éléments dans la pile).

## 2. Appliquer à l'expression postfixe [3, 4, +, 2, *]
Dans ce cas, je comprend que la gauche est le "haut" accessible de la pile, et que la droite en est le bas.

pop() => on récupère 3, la pile vaut [4, +, 2, *]
pop() => on récupère 4, la pile vaut [+, 2, *]
pop() => on récupère +, la pile vaut [2, *]

On a assez d'éléments pour effectuer le calcul. 3+4=7
push(7), la pile vaut [7, 2, *]

pop() => on récupère 7, la pile vaut [2, *]
pop() => on récupère 2, la pile vaut [*]
pop() => on récupère *, la pile est vide

On peut à nouveau calculer, on obtient 7*2=14
push(14), la pile vaut [14]

## 4. Vous pouvez vous aidez de l’exo-3 en C token, mais surtout expliquez la différence en complexité spatial vs une solution IA utilisant malloc pour le split des tokens (bonus 4 pts)
Une solution utilisant maloc prend de l'espace inutile supplémentaire (création d'un tableau) augmentant également le temps de traitement, tandis que strtok va simplement remplacer les espace par des \o similaire à l'exercice 3 effectuant dans les cours de C, n'augmentant donc pas dutout l'espace mémoire utilisé.
