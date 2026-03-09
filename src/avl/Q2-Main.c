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

avl_node *avl_create_node(int value, int height) {
    avl_node *node = malloc(sizeof(avl_node));
    node->key = value;
    node->height = height;
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
    avl_node *z = avl_create_node(30, 2);
    avl_node *y = avl_create_node(20, 1);
    avl_node *x = avl_create_node(10, 0);

    z->left = y;
    y->parent = z;

    y->left = x;
    x->parent = y;

    return z;
}

avl_node *test_rr() {
    avl_node *z = avl_create_node(10, 2);
    avl_node *y = avl_create_node(20, 1);
    avl_node *x = avl_create_node(30, 0);

    z->right = y;
    y->parent = z;

    y->right = x;
    x->parent = y;

    return z;
}

avl_node *test_lr() {
    avl_node *z = avl_create_node(30, 2);
    avl_node *y = avl_create_node(10, 1);
    avl_node *x = avl_create_node(20, 0);

    z->left = y;
    y->parent = z;

    y->right = x;
    x->parent = y;

    return z;
}

avl_node *test_rl() {
    avl_node *z = avl_create_node(10, 2);
    avl_node *y = avl_create_node(30, 1);
    avl_node *x = avl_create_node(20, 0);

    z->right = y;
    y->parent = z;

    y->left = x;
    x->parent = y;

    return z;
}

avl_node *test_balanced() {
    avl_node *root = avl_create_node(30, 2);
    avl_node *rootleft = avl_create_node(20, 1);
    avl_node *rootright = avl_create_node(40, 0);
    avl_node *rootleftleft = avl_create_node(10, 0);
    avl_node *rootleftright = avl_create_node(25, 0);

    root->left = rootleft;
    rootleft->parent = root;

    root->right = rootright;
    rootright->parent = root;

    root->left->left = rootleftleft;
    rootleftleft->parent = rootleft;

    root->left->right = rootleftright;
    rootleftright->parent = rootleft;

    return root;
}

void run_test(const char *str, avl_node *start_tree) {
    printf(str);
    printf("\nAvant :\n");
    avl_print_tree(start_tree, 0);
    printf("---\n");

    avl_node *end_tree = avl_balance(start_tree);

    printf("Après :\n");
    avl_print_tree(end_tree, 0);

    printf("-------------\n");

    avl_destroy(end_tree);
}

int main() {
    run_test("LL", test_ll());
    run_test("RR", test_rr());
    run_test("LR", test_lr());
    run_test("RL", test_rl());
    run_test("Balanced", test_balanced());

    return 0;
}
