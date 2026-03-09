#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? a : b)

typedef struct avl_node {
    int key;
    int height;
    void *data; // inutile dans le TP
    struct avl_node *parent;
    struct avl_node *left;
    struct avl_node *right;
} avl_node;

int get_height_or_zero(avl_node *node) {
    return node ? node->height : 0;
}

avl_node *avl_create_node(int value) {
    avl_node *node = malloc(sizeof(avl_node));
    node->key = value;
    node->height = 0;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void avl_recalculate_height_from_valid_children(avl_node *z) {
    if (!z->left && !z->right) {
        z->height = 0;
    } else {
        z->height = MAX(get_height_or_zero(z->left), get_height_or_zero(z->right)) + 1;
    }
}

avl_node *right_rotation(avl_node *z) {
    avl_node *y = z->left;
    avl_node *t3 = y->right;

    y->parent = NULL;

    y->right = z;
    z->parent = y;

    z->left = t3;
    if (t3) t3->parent = z;

    avl_recalculate_height_from_valid_children(z);
    avl_recalculate_height_from_valid_children(y);

    return y;
}

avl_node *left_rotation(avl_node *z) {
    avl_node *y = z->right;

    if (!y) {
        return z;
    }
    avl_node *t3 = y->left;

    y->parent = NULL;

    y->left = z;
    z->parent = y;

    z->right = t3;
    if (t3) t3->parent = z;

    avl_recalculate_height_from_valid_children(z);
    avl_recalculate_height_from_valid_children(y);

    return y;
}

int avl_calculate_balance_factor(avl_node *node) {
    // le -1 permet de différencier les noeuds avec feuilles et sans
    int leftHeight = node->left != NULL ? node->left->height : -1;
    int rightHeight = node->right != NULL ? node->right->height : -1;

    return leftHeight - rightHeight;
}

avl_node *avl_balance(avl_node *x) {
    int balanceFactor = avl_calculate_balance_factor(x);

    if (balanceFactor > -2 && balanceFactor < 2) {
        return x;
    }

    // LEFT
    if (balanceFactor > 0) {
        // LR
        if (x->left->right != NULL) {
            x->left = left_rotation(x->left);
            return right_rotation(x);
        }
        // LL
        return right_rotation(x);
    }

    // RIGHT
    // RR
    if (x->right->left != NULL) {
        x->right = right_rotation(x->right);
        return left_rotation(x);
    }
    // RL
    return left_rotation(x);
}

avl_node *avl_insert(avl_node *root, avl_node *x) {
    if (!root) {
        return x;
    }

    int key = x->key;

    avl_node *current_node = root;
    avl_node *parent_node = NULL;

    // trouver la feuille ou mettre le noeud
    while (current_node) {
        parent_node = current_node;
        if (key < current_node->key) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }

    // ajout à droite ou à gauche
    x->parent = parent_node;
    if (key < parent_node->key) {
        parent_node->left = x;
    } else {
        parent_node->right = x;
    }


    // équilibrage de l'arbre
    avl_node* parent_before_balance = parent_node;
    while (parent_node) {
        avl_node* grand_parent = parent_node->parent;

        avl_recalculate_height_from_valid_children(parent_node);
        parent_node = avl_balance(parent_node);

        // si on a changé de noeud d'attache, on le raccroche au parent
        // ou on le renvoie si on est à la racine
        if (parent_before_balance != parent_node) {
            avl_recalculate_height_from_valid_children(parent_node);
            parent_node->parent = grand_parent;

            if (!grand_parent) {
                return parent_node;
            }
            if (grand_parent -> left == parent_before_balance) {
                grand_parent -> left = parent_node;
            } else {
                grand_parent -> right = parent_node;
            }
        }

        parent_node = parent_node->parent;
        parent_before_balance = parent_node;
    }
    return root;
}


void avl_destroy(avl_node *x) {
    if (x) {
        avl_destroy(x->right);
        avl_destroy(x->left);
        free(x);
    }
}

void avl_print_tree(avl_node *node, int depth) {
    if (node == NULL) return;

    avl_print_tree(node->right, depth + 1);
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%d (h=%d)\n", node->key, node->height);
    avl_print_tree(node->left, depth + 1);
}

avl_node *test_ll() {
    avl_node *z = avl_create_node(30);
    avl_node *y = avl_create_node(20);
    avl_node *x = avl_create_node(10);

    z = avl_insert(z, y);
    z = avl_insert(z, x);

    return z;
}

avl_node *test_rr() {
    avl_node *z = avl_create_node(10);
    avl_node *y = avl_create_node(20);
    avl_node *x = avl_create_node(30);

    z = avl_insert(z, y);
    z = avl_insert(z, x);

    return z;
}

avl_node *test_lr() {
    avl_node *z = avl_create_node(30);
    avl_node *y = avl_create_node(10);
    avl_node *x = avl_create_node(20);

    z = avl_insert(z, y);
    z = avl_insert(z, x);

    return z;
}

avl_node *test_rl() {
    avl_node *z = avl_create_node(10);
    avl_node *y = avl_create_node(30);
    avl_node *x = avl_create_node(20);

    z = avl_insert(z, y);
    z = avl_insert(z, x);

    return z;
}

avl_node *test_balanced() {
    avl_node *a = avl_create_node(40);
    avl_node *b = avl_create_node(30);
    avl_node *c = avl_create_node(20);
    avl_node *d = avl_create_node(25);
    avl_node *e = avl_create_node(10);

    a = avl_insert(a, b);
    a = avl_insert(a, c);
    a = avl_insert(a, d);
    a = avl_insert(a, e);

    return a;
}

void run_test(const char *str, avl_node *tree) {
    printf(str);
    printf("\nAvant :\n");
    avl_print_tree(tree, 0);
    printf("-------------\n");

    avl_destroy(tree);
}

int main() {
    run_test("LL", test_ll());
    run_test("RR", test_rr());
    run_test("LR", test_lr());
    run_test("RL", test_rl());
    run_test("Balanced", test_balanced());

    return 0;
}
