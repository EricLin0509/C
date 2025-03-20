#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, const char *argv[]) {
    // 创建根节点
    TreeNode *root = new_node(1);
    root->val = 1;
    root->left = new_node(2); // 左子节点
    root->right = new_node(3); // 右子节点

    // 访问节点
    printf("根节点的值：%d\n", root->val);
    printf("左子节点的值：%d\n", root->left->val);
    printf("右子节点的值：%d\n", root->right->val);
    return 0;
}