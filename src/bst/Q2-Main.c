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
    printf("%c ", n->data);
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

int main() {
    TreeNode *root = node_new('F');
    bst_insert(&root, 'B');
    bst_insert(&root, 'A');
    bst_insert(&root, 'D');
    bst_insert(&root, 'C');
    bst_insert(&root, 'E');
    bst_insert(&root, 'G');
    bst_insert(&root, 'I');
    bst_insert(&root, 'H');
    preorder(root, print_node);
    printf("\n");
    iterative_preorder(root, print_node);
    printf("\n");
    inorder(root, print_node);
    printf("\n");
    iterative_inorder(root, print_node);
    return 0;
}
