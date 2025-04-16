# 遍历二叉树

一共有三种遍历方式：

- 前序遍历
- 中序遍历
- 后序遍历

![tree](imgs/tree.png)

## 前序遍历

前序遍历的顺序为：根节点 -> 左子树 -> 右子树

其输出顺序为：0 1 3 4 2 5 6

### 循环实现

```c
void preorderTraversal(struct TreeNode* root)
{
    TreeNode* stack[100];
    size_t stack_num = 0;

    stack[stack_num++] = root;
    while (stack_num > 0)
    {
        TreeNode* curr = stack[--stack_num];
        printf("%d ", curr->val);

        if (curr->right != NULL)
        {
            stack[stack_num++] = curr->right;
        }
        if (curr->left!= NULL)
        {
            stack[stack_num++] = curr->left;
        }
    }
}
```

### 递归实现
```c
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
```

## 中序遍历

中序遍历的顺序为：左子树 -> 根节点 -> 右子树

其输出顺序为：3 1 4 0 2 5 6

```c
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
```

## 后序遍历

后序遍历的顺序为：左子树 -> 右子树 -> 根节点

其输出顺序为：3 4 1 5 6 2 0

```c
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
```