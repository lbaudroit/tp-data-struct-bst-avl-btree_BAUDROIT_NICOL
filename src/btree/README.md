# B-tree de degré 3 avec l'insertion de "A L G O R I T H M E"
Lettres à ajouter : A L G O R I T H M S
Dans l'ordre ASCII : A G H I L M O R S T

t = 3 donc les noeuds ont entre 2 et 5 clés, donc entre 3 et 6 enfants.

## Construction de l'arbre par étapes
En faisant l'exercice, j'ai appris la différence entre degré et ordre... et aussi à lire les consignes
https://stackoverflow.com/a/45826413
Voici la version corrigée :

Insertion de A :
```text
[ A ]
```

Insertion de L :
```text
[ A | L ]
```

Insertion de G :
```text
[ A | G | L ] 
```

Insertion de O :
```text
[ A | G | L | O ]
```

Insertion de R :
```text
[ A | G | L | O | R ]
```

Insertion de I :
```text
[ A | G | I | L | O | R ] // > 5 clés, 
```

Éclatement et remontée de la valeur médiane basse (I) :
```text
       [ I ]
[ A | G ] [ L | O | R ]
```

Insertion de T :
```text
       [ I ]
[ A | G ] [ L | O | R | T ]
```

Insertion de H :
```text
            [ I ]
[ A | G | H ] [ L | O | R | T ]
```

Insertion de M :
```text
            [ I ]
[ A | G | H ] [ L | M | O | R | T ]
```

Insertion de S :
```text
            [ I ]
[ A | G | H ] [ L | M | O | R | S | T ]
```

Éclatement et remontée de la valeur médiane (O) :
```text
                [ I | O ]
[ A | G | H ]   [ L | M ]   [ R | S | T ]
```

Vérifié avec https://www.cs.usfca.edu/~galles/visualization/BTree.html
(cette fois-ci en mettant le degré à 6)

## Nombre de clés et hauteur
Dans le cas où le B-tree est entièrement rempli.
On aura le maximum d'enfants, donc m, enfants pour chaque nœud, donc un total de m^h
(m nœuds pour chaque nœud du niveau précédent).
Chaque nœud rempli au maximum aura m-1 clés, donc un total de (m-1)(m ^ h) clés au total.

Un B-tree gagne en hauteur lorsqu'on effectue des éclatements.

## Recherche et complexité
On considère la complexité d'une recherche dichotomique de clé dans un nœud O(log(n))
Dans le pire cas, on devra descendre jusqu'aux feuilles (donc parcourir la hauteur), dans le meilleur on s'arrête au premier nœud.
Ainsi, on sera toujours en log(c * n)) (avec c entre h et 1) donc O(log(n))
On peut considérer que h est de l'ordre de log n, auquel cas on est en O(log(n)^2)

## Minimum, prédécesseur, suppression
Pour trouver la clé de valeur minimum, on doit naviguer à gauche jusqu'à la feuille et prendre la valeur la plus à gauche.

Pour trouver le prédécesseur d'une clé :
- s'il existe une clé précédente dans le nœud courant, on la prend
- si la clé possède un sous-arbre gauche, il nous faut prendre la plus grande clé de ce sous-arbre (similairement à la recherche du minimum de la question précédente)
- s'il n'y a ni clé précédente ni sous-arbre gauche, il nous faut remonter l'arbre jusqu'à la première clé dont le nœud actuel constitue le sous-arbre droit
