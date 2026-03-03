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

void inorder(struct tree_node *n, process_fn process) {
    if (!n) return;
    inorder(n->left, process);
    process(n);
    inorder(n->right, process);
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
    root->left = node_new('B');
    root->left->left = node_new('A');
    root->left->right = node_new('D');
    root->left->right->left = node_new('C');
    root->left->right->right = node_new('E');
    root->right = node_new('G');
    root->right->right = node_new('I');
    root->right->right->left = node_new('H');
    TreeNode *root2 = node_new('F');
    bst_insert(&root2, 'B');
    bst_insert(&root2, 'A');
    bst_insert(&root2, 'D');
    bst_insert(&root2, 'C');
    bst_insert(&root2, 'E');
    bst_insert(&root2, 'G');
    bst_insert(&root2, 'I');
    bst_insert(&root2, 'H');
    preorder(root, print_node);
    printf("\n");
    preorder(root2, print_node);
}
