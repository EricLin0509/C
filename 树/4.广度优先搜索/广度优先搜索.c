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

void print_breadth_first_search(TreeNode *root)
{
    TreeNode *queue[100];
    size_t queue_num = 0;

    queue[queue_num++] = root; // 将根节点入队

    while (queue_num > 0)
    {
        TreeNode *curr = queue[0];

        for (int i = 0; i < queue_num - 1; i++) // 向前移动队列
        {
            queue[i] = queue[i + 1];
        }
        
        queue_num--; // 队列长度减一
        
        printf("%d ", curr->val);

        if (curr->left != NULL)
        {
            queue[queue_num++] = curr->left; // 将左子节点入队
        }
        if (curr->right != NULL)
        {
            queue[queue_num++] = curr->right; // 将右子节点入队
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

    // 广度优先搜索
    print_breadth_first_search(root);

    return 0;
}