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

void preorderTraversal(struct TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(struct TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->val);
    inorderTraversal(root->right);
}

void postorderTraversal(struct TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->val);
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

    printf("先序遍历：");
    preorderTraversal(root);
    printf("\n");
    printf("中序遍历：");
    inorderTraversal(root);
    printf("\n");
    printf("后序遍历：");
    postorderTraversal(root);
    printf("\n");

    return 0;
}