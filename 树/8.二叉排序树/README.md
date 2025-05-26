# 二叉排序树

## 定义

二叉排序树 (Binary Sort Tree / Binary Search Tree)，又称为二叉查找树。用于快速查找、插入和删除数据的一种数据结构

## 特点

- 左子树的所有节点的值均小于或等于它的根节点的值
- 右子树的所有节点的值均大于或等于它的根节点的值
- 左右子树也分别为二叉排序树

## 实现

```c
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node; // 二叉树节点

void insertNode(Node **root, int data); // 插入节点
void deleteNode(Node **root, int data); // 删除节点
Node* findNode(Node *root, int data); // 查找节点
```

### 插入节点

#### 如果二叉树为空，则直接插入节点

```c
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
}
```

#### 判断节点的值与父节点的值的大小关系

- 如果节点的值**小于父节点的值**，去往**左子树**
- 如果节点的值**大于父节点的值**，去往**右子树**

```c
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
```

### 查找节点

#### 如果二叉树为空，则返回 NULL

```c
Node* findNode(Node *root, int data)
{
    if (root == NULL) return NULL;
}
```

#### 判断节点的值与父节点的值的大小关系

跟上面的[插入节点](#判断节点的值与父节点的值的大小关系)的思路大致相同，这里只需要返回找到的节点即可

```c
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
```

### 删除节点

#### 如果二叉树为空或者要删除的节点不存在，则直接退出

```c
void deleteNode(Node **root, int data)
{
    if (*root == NULL) return;
}
```

#### 查找要删除的节点

```c
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
}
```

#### 如果要删除的节点存在，则删除节点

**由于二叉排序树的特性，如果直接删除节点，可能会导致二叉排序树的结构被破坏**，因此需要进行一些操作来保证二叉排序树的结构不变

- 如果要删除的节点是叶子节点，则直接删除

```c
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
    }
}
```

- 如果要删除的节点只有左子树或右子树，则将左子树或右子树替换到要删除的节点的位置

```c
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
    }
}
```

- 如果要删除的节点有左右子树，则需要找到一个节点来替换要删除的节点

这里有两种选择

- **从根节点开始向左子树中查找<mark>最大</mark>的节点**，将其值替换到要删除的节点的位置
- **从根节点开始向右子树中查找<mark>最小</mark>的节点**，将其值替换到要删除的节点的位置

```c
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
```

```c
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
```

或者

```c
Node *temp = findRightMinNode(*root); // 从右子树中查找最小的节点
(*root)->data = temp->data; // 将最小的节点的值赋值给要删除的节点
deleteNode(&((*root)->right), temp->data); // 删除最小的节点
```