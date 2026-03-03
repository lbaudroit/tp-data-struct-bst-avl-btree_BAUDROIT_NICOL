#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_node {
  int data; // ou int key + void* data;
  struct tree_node *parent;
  struct tree_node *left;
  struct tree_node *right;
};

typedef struct tree_node TreeNode;
typedef void (*process_fn)(struct tree_node *);

void preorder(struct tree_node *n, process_fn process) {
    if (!n) return;
    process(n);
    preorder(n->left, process);
    preorder(n->right, process);
}

void iterative_preorder(struct tree_node *n, process_fn process) {
    struct tree_node *curr = n, *prev = NULL;
    while (curr) {
        if (prev == curr->parent) {
            process(curr);
            if (curr->left) {
                prev = curr;
                curr = curr->left;
                continue;
            }
            prev = NULL;
        }
        if (prev == curr->left) {
            if (curr->right) {
                prev = curr;
                curr = curr->right;
                continue;
            }
        }
        prev = curr;
        curr = curr->parent;
    }
}

void inorder(struct tree_node *n, process_fn process) {
    if (!n) return;
    inorder(n->left, process);
    process(n);
    inorder(n->right, process);
}

void iterative_inorder(struct tree_node *n, process_fn process) {
    struct tree_node *curr = n, *prev = NULL;
    while (curr) {
        if (prev == curr->parent) {
            if (curr->left) { prev = curr; curr = curr->left; continue; }
            prev = NULL;
        }
        if (prev == curr->left) {
            process(curr);
            if (curr->right) { prev = curr; curr = curr->right; continue; }
        }
        prev = curr;
        curr = curr->parent;
    }
}

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
    if (!*root) {
        *root = node_new(data);
        return *root;
    }

    struct tree_node *current = *root;
    struct tree_node *parent = NULL;

    while (current) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    struct tree_node *new_node = node_new(data);
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
