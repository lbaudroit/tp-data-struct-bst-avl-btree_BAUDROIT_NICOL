# B-tree de degré 3 avec l'insertion de "A L G O R I T H M E"
Lettres à ajouter : A L G O R I T H M S
Dans l'ordre ASCII : A G H I L M O R S T

t = 3 donc
- les nœuds contiennent entre 0 et 2 clés
(3/2)-1= 0 (impossible donc 1) et (3-1)=2 

- les nœuds non-racine sont entre 1 et 3 fils
3/2 = 1

## Construction de l'arbre par étapes
Visiblement, il fallait utiliser le degré minimum et non pas l'ordre.
https://stackoverflow.com/a/45826413

Insertion de A :
[ A ]

Insertion de L :
[ A | L ]

Insertion de G :
[ A | G | L ] // violation, > 2 clés

Éclatement et remontée de la valeur médiane (G) :
    [ G ]
 [ A ] [ L ]

Insertion de O :
   [ G ]
[ A ] [ L | O ]

Insertion de R :
   [ G ]
[ A ] [ L | O | R ] // violation, > 2 clés

Eclatement et remontée de la valeur médiane (O) :
    [ G | O ]
[ A ] [ L ] [ R ]

Insertion de I :
      [ G | O ]
[ A ] [ I |  L ] [ R ]

Insertion de T :
      [ G | O ]
[ A ] [ I |  L ] [ R | T ]

Insertion de H :
         [ G | O ]
[ A ] [ H  | I |  L ] [ R | T ] // violation, > 2 clés

Éclatement et remontée de la valeur médiane (I) :
   [ G | I | O ]     // violation, > 2 clés
[ A ][ H ][ L ] [ R | T ]

Éclatement et remontée de la valeur médiane (I) :
              [ I ]
      [ G ]           [ O ]
[ A ]     [ H ]   [ L ]   [ R | T ]

Insertion de M :
              [ I ]
      [ G ]               [ O ]
[ A ]     [ H ]   [ L | M ]   [ R | T ]

Insertion de S :
              [ I ]
      [ G ]            [ O ]
[ A ]     [ H ][ L | M ]   [ R | S | T ] // violation, > 2 clés

Éclatement et remontée de la valeur médiane (S) :
                    [ I ]
            [ G ]        [ O | S ]
[ A ]     [ H ]   [ L | M ][ R ][ T ]

Vérifié avec https://www.cs.usfca.edu/~galles/visualization/BTree.html

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
