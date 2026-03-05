#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_node {
  int data; // ou int key + vod* data;
  struct tree_node *parent;
  struct tree_node *left;
  struct tree_node *right;
};

typedef struct tree_node TreeNode;
typedef void (*process_fn)(struct tree_node *);

 // Preorder = d'abord la function et ensuite left puis right
void preorder(struct tree_node *n, process_fn process) {
    if (!n) return;
    process(n);
    preorder(n->left, process);
    preorder(n->right, process);
}

// Iterative version  = n'utilise pas la récurtion
void iterative_preorder(struct tree_node *n, process_fn process) {
    struct tree_node *curr = n;
    struct tree_node *prev = NULL; // Previous pour ce souvenir d'où l'on vient à la boucle précédente, évitent alors l'utilisation de la stack
    while (curr) {
        if (prev == curr->parent) { // Si nous venons de décendre dans l'arbre alors on s'execute d'abord puis on cherche a descendre plus
            process(curr);
            if (curr->left) {
                prev = curr;
                curr = curr->left;
            } else {
                prev = NULL;
            }
        } else if (prev == curr->left) { // Si on vient de dire que la gauche est null, on vérifie la droite ou si on vient de remonter de la branche gauche
            if (curr->right) {
                prev = curr;
                curr = curr->right;
            } else {
                prev = curr;
                curr = curr->parent;
            }
        } else { // Si on vient de remonter mais que rien n'est disponible à droite
            prev = curr;
            curr = curr->parent;
        }
    }
}
// Inorder execute toujours d'abord la gauche, puis sois même, puis la droite
void inorder(struct tree_node *n, process_fn process) {
    if (!n) return;
    inorder(n->left, process);
    process(n);
    inorder(n->right, process);
}

// Même logique que pour l'proder iteratif en haut, mais en metant le process pas au même endroit, après être "remonté" d'à gauche, (ou avoir vérifier que la gauche est null)
void iterative_inorder(struct tree_node *n, process_fn process) {
    struct tree_node *curr = n, *prev = NULL;
    while (curr) {
        if (prev == curr->parent) {
            if (curr->left) {
                prev = curr;
                curr = curr->left;
            } else {
                prev = NULL;
            }
        } else if (prev == curr->left) {
            process(curr);
            if (curr->right) {
                prev = curr;
                curr = curr->right;
            } else {
                prev = curr;
                curr = curr->parent;
            }
        } else {
            prev = curr;
            curr = curr->parent;
        }
    }
}

// Postorder execute toujours d'abord la gauche, puis la droite et einf self
void postorder(struct tree_node *n, process_fn process) {
    if (!n) return;
    postorder(n->left, process);
    postorder(n->right, process);
    process(n);
}

void print_node(struct tree_node *n) {
    printf("%d ", n->data);
}

void tree_free(struct tree_node *subroot) {
    if (!subroot) return;
    postorder(subroot->left, (process_fn)(void (*)(struct tree_node *))free);
    postorder(subroot->right, (process_fn)(void (*)(struct tree_node *))free);
    subroot->left = NULL;
    subroot->right = NULL;
}

struct tree_node *node_new(int data) {
    struct tree_node *n = malloc(sizeof(struct tree_node));
    n->data = data;
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    return n;
}

struct tree_node *bst_insert(struct tree_node **root, int data) {
    if (!*root) { // S'asure que root est pas null, sinon on initialise
        *root = node_new(data);
        return *root;
    }

    struct tree_node *current = *root;
    struct tree_node *parent = NULL;

    while (current) { // Trouve la feuille la plus adapté à acceuilire le nouveau noeud
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    struct tree_node *new_node = node_new(data); // Crée le noeud puis l'ajoute a gauche ou a droit de la feuille trouvé selon le besoin
    new_node->parent = parent;
    if (data < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    return new_node;
}

struct tree_node *tree_delete(struct tree_node **root, int key) {
    struct tree_node *curr = *root;

    // Trouve le Node qui correpons
    while (curr != NULL && curr->data != key) {
        if (key < curr->data) curr = curr->left;
        else curr = curr->right;
    }
    if (curr == NULL) return NULL;

    struct tree_node *to_del; // la node a delete
    struct tree_node *to_move; // l'enfant qui irai a ca place

    if (curr->left == NULL || curr->right == NULL) {
        to_del = curr; // Si il a pas d'enfant ou un seul, il faut le supprimer
    } else {
        to_del = curr->right; // Si il y en as deux il faudrat trouver la feuille qui prendrais le mieux la valeur (la plus a droite puis en bas a gauche uniquement, elle prendrat la place de curr à la fin)
        while (to_del->left)
            to_del = to_del->left;
    }

    if (to_del->left) // Trouve avec quel enfant il faut faire la liaison avec l'ancien parent
        to_move = to_del->left;
    else
        to_move = to_del->right;
    //  Modifie la reference du parent du fils
    if (to_move) to_move->parent = to_del->parent;

    if (to_del->parent == NULL) {
        *root = to_move;
    } else if (to_del == to_del->parent->left) { // Modifie la reference enfant du parent
        to_del->parent->left = to_move;
    } else {
        to_del->parent->right = to_move;
    }

    if (to_del != curr) { // Dans le cas deux enfant, inverse la valeur de to_del et curr, comme ca la valeur to_del est placé dans l'arbre et disparait pas
        curr->data = to_del->data;
    }

    free(to_del);
    return *root;
}

int main() {
    TreeNode *root = node_new(10);
    bst_insert(&root, 2);
    bst_insert(&root, 25);
    bst_insert(&root, 15);
    bst_insert(&root, 30);
    bst_insert(&root, 12);;
    bst_insert(&root, 20);
    bst_insert(&root, 16);
    bst_insert(&root, 24);
    bst_insert(&root, 17);
    bst_insert(&root, 22);
    preorder(root, print_node);
    printf("\n");
    iterative_preorder(root, print_node);
    printf("\n");
    inorder(root, print_node);
    printf("\n");
    iterative_inorder(root, print_node);
    printf("\n");
    //tree_free(root->left);
    preorder(root, print_node);
    printf("\n");

    printf("Original Inorder: ");
    preorder(root, print_node);
    printf("\n");

    struct tree_node *d1 = tree_delete(&root, 24);
    struct tree_node *d2 = tree_delete(&root, 15);
    //struct tree_node *d3 = tree_delete(&root, 10);

    printf("After Deletions (Inorder): ");
    preorder(root, print_node);
    printf("\n");

    return 0;
}
