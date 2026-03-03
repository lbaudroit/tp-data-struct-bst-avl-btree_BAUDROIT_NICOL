#include <stddef.h>

struct tree_node {
  int data; // ou int key + void* data;
  struct tree_node *parent;
  struct tree_node *left;
  struct tree_node *right;
};

typedef struct tree_node TreeNode;

typedef void (*process_fn)(struct tree_node *);
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
}
