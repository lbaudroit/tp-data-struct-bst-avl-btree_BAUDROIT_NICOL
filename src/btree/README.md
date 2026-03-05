# B-tree de degré 3 avec l'insertion de "A L G O R I T H M E"
Lettres à ajouter : A L G O R I T H M S
Dans l'ordre ASCII : A G H I L M O R S T

t = 3 donc
- les nœuds contiennent entre 0 et 2 clés
(3/2)-1= 0 (impossible donc 1) et (3-1)=2 

- les nœuds non-racine sont entre 1 et 3 fils
3/2 = 1

## Construction de l'arbre par étapes

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
   [ G | I | O ] // violation, > 2 clés
[ A ][ H ][ L ][ R | T ]

Éclatement et remontée de la valeur médiane (I) :
              [ I ]
      [ G ]          [ O ]
[ A ]     [ H ]   [ L ]   [ R | T ]

Insertion de M :
              [ I ]
      [ G ]          [ O ]
[ A ]     [ H ]   [ L | M ]   [ R | T ]

Insertion de S :
              [ I ]
      [ G ]          [ O ]
[ A ]     [ H ]   [ L | M ]   [ R | S | T ] // violation, > 2 clés

Éclatement et remontée de la valeur médiane (S) :
                    [ I ]
            [ G ]            [ O | S]
[ A ]     [ H ]   [ L | M ]    [ R ][ T ]

Vérifié avec https://www.cs.usfca.edu/~galles/visualization/BTree.html

