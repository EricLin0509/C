#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *new_node(int val)
{
    TreeNode *node = malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bool found = false;

void print_depth_first_search_recursive(TreeNode *node)
{
    if (node->val == 3) // 找到节点
    {
        printf("%d (Found 3) ", node->val);
        found = true;
        return;
    }
    else
    {
        printf("%d ", node->val);
    }

    if (node->left != NULL && !found)
    {
        print_depth_first_search_recursive(node->left); // 递归调用左子节点
    }

    if (node->right != NULL &&!found)
    {
        print_depth_first_search_recursive(node->right); // 递归调用右子节点
    }
}

int main(int argc, const char *argv[]) {
    // 创建根节点
    TreeNode *root = new_node(0);
    root->left = new_node(1);
    root->right = new_node(2);
    root->left->left = new_node(3);
    root->left->right = new_node(4);
    root->right->left = new_node(5);
    root->right->right = new_node(6);

    // 深度优先搜索
    print_depth_first_search_recursive(root);
    printf("\n");

    return 0;
}