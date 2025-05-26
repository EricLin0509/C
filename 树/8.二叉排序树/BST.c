#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node; // 二叉树节点

void insertNode(Node **root, int data)
{
    if (*root == NULL)
    {
        *root = malloc(sizeof(Node));
        (*root)->data = data;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }

    if (data < (*root)->data) // 如果节点的值小于父节点的值
    {
        insertNode(&((*root)->left), data);
    }
    else if (data > (*root)->data) // 如果节点的值大于父节点的值
    {
        insertNode(&((*root)->right), data);
    }
}

Node* findNode(Node *root, int data)
{
    if (root == NULL) return NULL;

    if (data < root->data) // 如果节点的值小于父节点的值
    {
        return findNode(root->left, data);
    }
    else if (data > root->data) // 如果节点的值大于父节点的值
    {
        return findNode(root->right, data);
    }

    if (data == root->data) // 如果节点的值等于父节点的值
    {
        return root;
    }
}

static Node* findLeftMaxNode(Node *root) // 从根节点开始向左子树中查找最大的节点
{
    root = root->left; // 从左子树开始查找
    while (root->right != NULL) // 一直往右子树查找
    {
        root = root->right;
    }
    return root;
}

static Node* findRightMinNode(Node *root) // 从根节点开始向右子树中查找最小的节点
{
    root = root->right; // 从右子树开始查找
    while (root->left!= NULL) // 一直往左子树查找
    {
        root = root->left;
    }
    return root;
}

void deleteNode(Node **root, int data)
{
    if (*root == NULL) return;

    if (data < (*root)->data) // 如果节点的值小于父节点的值
    {
        deleteNode(&((*root)->left), data);
    }
    else if (data > (*root)->data) // 如果节点的值大于父节点的值
    {
        deleteNode(&((*root)->right), data);
    }

    if (data == (*root)->data) // 如果节点的值等于父节点的值
    {
        if ((*root)->left == NULL && (*root)->right == NULL) // 如果要删除的节点是叶子节点
        {
            free(*root);
            *root = NULL;
            return;
        }
        else if ((*root)->left == NULL) // 如果要删除的节点只有右子树
        {
            Node *temp = *root;
            *root = (*root)->right;
            free(temp);
        }
        else if ((*root)->right == NULL) // 如果要删除的节点只有左子树
        {
            Node *temp = *root;
            *root = (*root)->left;
            free(temp);
        }
        else // 如果要删除的节点有左右子树
        {
            Node *temp = findLeftMaxNode(*root); // 从左子树中查找最大的节点
            (*root)->data = temp->data; // 将最大的节点的值赋值给要删除的节点
            deleteNode(&((*root)->left), temp->data); // 删除最大的节点
        }
    }
}

void printTree(Node *root)
{
    Node *stack[100];
    int count = 0;
    stack[count++] = root;
    while (count > 0)
    {
        Node *node = stack[--count];
        printf("%d ", node->data);
        if (node->right != NULL)
        {
            stack[count++] = node->right;
        }
        if (node->left != NULL)
        {
            stack[count++] = node->left;
        }
    }
    printf("\n");
}

int main(int argc, const char *argv[]) {
    Node *root = NULL;
    insertNode(&root, 10);
    insertNode(&root, 5);
    insertNode(&root, 15);
    insertNode(&root, 3);
    insertNode(&root, 7);
    insertNode(&root, 12);
    insertNode(&root, 17);
    insertNode(&root, 2);
    insertNode(&root, 4);

    printf("%s\n", findNode(root, 10) != NULL ? "found 10" : "10 not found");
    printf("%s\n", findNode(root, 0)!= NULL? "found 0" : "0 not found");

    printTree(root);

    deleteNode(&root, 5);
    printTree(root);
    deleteNode(&root, 15);
    printTree(root);
}