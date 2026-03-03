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