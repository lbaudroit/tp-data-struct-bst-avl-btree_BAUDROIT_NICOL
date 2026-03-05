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
    struct tree_node *current_node = n;
    struct tree_node *previous_node = NULL; // Previous pour ce souvenir d'où l'on vient à la boucle précédente, évitent alors l'utilisation de la stack
    while (current_node) {
        if (previous_node == current_node->parent) { // Si nous venons de décendre dans l'arbre alors on s'execute d'abord puis on cherche a descendre plus
            process(current_node);
            if (current_node->left) {
                previous_node = current_node;
                current_node = current_node->left;
            } else {
                previous_node = NULL;
            }
        } else if (previous_node == current_node->left) { // Si on vient de dire que la gauche est null, on vérifie la droite ou si on vient de remonter de la branche gauche
            if (current_node->right) {
                previous_node = current_node;
                current_node = current_node->right;
            } else {
                previous_node = current_node;
                current_node = current_node->parent;
            }
        } else { // Si on vient de remonter mais que rien n'est disponible à droite
            previous_node = current_node;
            current_node = current_node->parent;
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
    struct tree_node *current_node = n, *previous_node = NULL;
    while (current_node) {
        if (previous_node == current_node->parent) {
            if (current_node->left) {
                previous_node = current_node;
                current_node = current_node->left;
            } else {
                previous_node = NULL;
            }
        } else if (previous_node == current_node->left) {
            process(current_node);
            if (current_node->right) {
                previous_node = current_node;
                current_node = current_node->right;
            } else {
                previous_node = current_node;
                current_node = current_node->parent;
            }
        } else {
            previous_node = current_node;
            current_node = current_node->parent;
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

    struct tree_node *current_node = *root;
    struct tree_node *parent_node = NULL;

    while (current_node) { // Trouve la feuille la plus adapté à acceuilire le nouveau noeud
        parent_node = current_node;
        if (data < current_node->data) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }

    struct tree_node *new_node = node_new(data); // Crée le noeud puis l'ajoute a gauche ou a droit de la feuille trouvé selon le besoin
    new_node->parent = parent_node;
    if (data < parent_node->data) {
        parent_node->left = new_node;
    } else {
        parent_node->right = new_node;
    }
    return new_node;
}

struct tree_node *tree_delete(struct tree_node **root, int key) {
    struct tree_node *current_node = *root;

    // Trouve le Node qui correpons
    while (current_node != NULL && current_node->data != key) {
        if (key < current_node->data) current_node = current_node->left;
        else current_node = current_node->right;
    }
    if (current_node == NULL) return NULL;

    struct tree_node *node_to_delete; // la node a delete
    struct tree_node *node_to_move; // l'enfant qui irai a ca place

    if (current_node->left == NULL || current_node->right == NULL) {
        node_to_delete = current_node; // Si il a pas d'enfant ou un seul, il faut le supprimer
    } else {
        node_to_delete = current_node->right; // Si il y en as deux il faudrat trouver la feuille qui prendrais le mieux la valeur (la plus a droite puis en bas a gauche uniquement, elle prendrat la place de curr à la fin)
        while (node_to_delete->left)
            node_to_delete = node_to_delete->left;
    }

    if (node_to_delete->left) // Trouve avec quel enfant il faut faire la liaison avec l'ancien parent
        node_to_move = node_to_delete->left;
    else
        node_to_move = node_to_delete->right;
    //  Modifie la reference du parent du fils
    if (node_to_move) node_to_move->parent = node_to_delete->parent;

    if (node_to_delete->parent == NULL) {
        *root = node_to_move;
    } else if (node_to_delete == node_to_delete->parent->left) { // Modifie la reference enfant du parent
        node_to_delete->parent->left = node_to_move;
    } else {
        node_to_delete->parent->right = node_to_move;
    }

    if (node_to_delete != current_node) { // Dans le cas deux enfant, inverse la valeur de to_del et curr, comme ca la valeur to_del est placé dans l'arbre et disparait pas
        current_node->data = node_to_delete->data;
    }

    free(node_to_delete);
    return *root;
}

struct tree_node *tree_delete_predecessor(struct tree_node **root, int key) {
    struct tree_node *current_node = *root;

    while (current_node != NULL && current_node->data != key) {
        if (key < current_node->data) current_node = current_node->left;
        else current_node = current_node->right;
    }
    if (current_node == NULL) return NULL;

    struct tree_node *node_to_delete;
    struct tree_node *node_to_move;

    if (current_node->left == NULL || current_node->right == NULL) {
        node_to_delete = current_node;
    } else {
        // changeemnt de logique : go left , then keep it going right
        node_to_delete = current_node->left;
        while (node_to_delete->right)
            node_to_delete = node_to_delete->right;
    }

    if (node_to_delete->left)
        node_to_move = node_to_delete->left;
    else
        node_to_move = node_to_delete->right;

    if (node_to_move) node_to_move->parent = node_to_delete->parent;

    if (node_to_delete->parent == NULL) {
        *root = node_to_move;
    } else if (node_to_delete == node_to_delete->parent->left) {
        node_to_delete->parent->left = node_to_move;
    } else {
        node_to_delete->parent->right = node_to_move;
    }

    if (node_to_delete != current_node) {
        current_node->data = node_to_delete->data;
    }

    free(node_to_delete);
    return *root;
}

struct tree_node *tree_delete_randomize(struct tree_node **root, int key) {
    if ((*root)->left != NULL && (*root)->right != NULL) {
        if (rand() % 2 == 0) {
            return tree_delete_predecessor(root, key);
        } else {
            return tree_delete(root, key);
        }
    } else
        return tree_delete(root, key);
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

    struct tree_node *d1 = tree_delete_randomize(&root, 24);
    struct tree_node *d2 = tree_delete_randomize(&root, 15);

    printf("After Deletions (Inorder): ");
    preorder(root, print_node);
    printf("\n");

    return 0;
}
