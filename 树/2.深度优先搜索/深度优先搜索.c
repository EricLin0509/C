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

void print_depth_first_search(TreeNode *root)
{
    TreeNode *stack[100]; // 创建栈
    size_t stack_num = 0; // 栈的大小

    stack[stack_num++] = root; // 将根节点入栈

    while (stack_num > 0)
    {
        TreeNode *curr = stack[--stack_num]; // 前面的节点先出栈

        printf("%d ", curr->val); // 访问节点

        if (curr->right != NULL)
        {
            stack[stack_num++] = curr->right; // 将右子节点入栈
        }
        if (curr->left != NULL)
        {
            stack[stack_num++] = curr->left; // 将左子节点入栈
        }
    }
    printf("\n");
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
    print_depth_first_search(root);

    return 0;
}