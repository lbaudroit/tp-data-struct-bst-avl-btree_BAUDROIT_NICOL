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

int main() {
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
    .right = &(TreeNode){
      .data = 'G',
      .left = NULL,
      .right = &(TreeNode){
        .data = 'I',
        .left = &(TreeNode){ .data = 'H', .left = NULL, .right = NULL, },
        .right = NULL,
      },
    },
  };
  preorder(&root, print_node);
}
