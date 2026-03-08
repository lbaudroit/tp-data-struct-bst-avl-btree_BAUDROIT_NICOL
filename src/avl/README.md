# Questions
## Equilibre
L'arbre statique comportant des lettres est déséquilibré : root.right a une hauteur de 0 à gauche et 2 à droite (donc une différence excédant 1)
L'arbre d'entiers est également déséquilibré : à gauche de la racine, on a une hauteur de 1, à droite (donc une différence plus grande que 1)

Arbre de lettres corrigé
```c
TreeNode root = {
  .data = 'F',
  .left = &(TreeNode){
    .data = 'B',
    .left = &(TreeNode){ .data = 'A', .left = NULL, .right = NULL, },
    .right = &(TreeNode){
      .data = 'D',
      .left = &(TreeNode){ .data = 'C', .left = NULL, .right = NULL, },
      .right = &(TreeNode){ .data = 'E', .left = NULL, .right = NULL, },
    },
  },
  .right = &(Node){
    .data = 'H',
    .left = &(TreeNode){ .data = 'G', .left = NULL, .right = NULL, },
    .right = &(TreeNode){ .data = 'I', .left = NULL, .right = NULL, },
  },
};
```

Arbre d'entiers corrigé : cf image Q1-Arbre.jpeg

## Hauteur et complexité
Dans un arbre de hauteur 1, on a (au max) 2 feuilles, et 3 valeurs.
Dans un arbre de hauteur 2, on a (au max) 2 feuilles pour chaque noeud intermédiaire, ainsi qu'une valeur pour chaque noeud, soit 5 valeurs.

On peut donc dire qu'un AVL a un nombre de feuilles de l'ordre 2^h,
un nombre de nœuds égal à la somme des 2^n avec n=h, n-- jusqu'à n=1
donc un nombre de valeurs similaire. Ainsi, le rapport entre hauteur et nombre de noeuds est d'ordre O(log_2(n))
Cependant, la base du logarithme importe peu, car on peut convertir facilement entre deux bases à partir d'une constante
Par exemple : log_10(a) = log_2(a) / log_2(10)

Un arbre est équilibré si on n'a pas plus d'un niveau de différence entre les hauteurs droites et gauches.
Lors de l'insertion, on peut descendre jusqu'à h niveaux pour insérer la valeur, et dans le cas d'un arbre équilibré, on a h = log_2(n)
On doit ensuite effectuer des rotations si l'arbre devient déséquilibré à la suite de cette insertion.
Cependant, dans le chemin de l'arborescence, il n'y aura qu'un nœud réellement affecté et déséquilibré par l'insertion.
Il suffit donc d'une seule rotation pour corriger le déséquilibre entraîné.

## Rotations
LL : lorsqu'on ajoute un nœud NEW seul à gauche d'un élément MID vide déjà seul à gauche de son parent PARENT
PARENT a donc un facteur de +/- 2
Dans ce cas, MID devient racine du sous-arbre, avec NEW à sa gauche et PARENT à sa droite.

RR : même chose mais avec NEW à droite de MID, lui-même à droite de PARENT.

LR : on ajoute NEW seul à droite d'un noeud MID seul à gauche de PARENT
On effectue une rotation LL puis RR

RL : même chose mais avec NEW à gauche de MID, lui-même à droite de PARENT
On effectue RR puis LL

On a au maximum une rotation (si on compte LR et RL comme 1 seule rotation), car seul un nœud est impacté 






