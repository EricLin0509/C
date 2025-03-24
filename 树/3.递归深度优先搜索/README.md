# 递归深度优先搜索

## 代码实现

由于递归的特性，我们可以传入任意一个节点，然后递归调用它的子节点

```c
void print_depth_first_search_recursive(TreeNode *node)
```

### 打印节点

```c
void print_depth_first_search_recursive(TreeNode *node)
{
    printf("%d ", node->val);
}
```

### 递归调用子节点

**需要判断子节点是否为 `NULL`**

```c
void print_depth_first_search_recursive(TreeNode *node)
{
    printf("%d ", node->val);

    if (node->left != NULL)
    {
        print_depth_first_search_recursive(node->left); // 递归调用左子节点
    }

    if (node->right != NULL)
    {
        print_depth_first_search_recursive(node->right); // 递归调用右子节点
    }
}
```

### 测试

```c
TreeNode *root = new_node(0);
root->left = new_node(1);
root->right = new_node(2);
root->left->left = new_node(3);
root->left->right = new_node(4);
root->right->left = new_node(5);
root->right->right = new_node(6);
```

```bash
gcc -o dfs dfs.c
./dfs
0 1 3 4 2 5 6
```

## 流程

假设以根节点 (`root`) 开始，一共3层

1. 访问 `root` 节点
2. 访问 `root->left` 节点
3. 访问 `root->left->left` 节点
4. **由于 `root->left->left` 没有子节点，返回上一层**
5. 访问 `root->left->right` 节点
6. **由于 `root->left->right` 没有子节点，返回上一层**
7. 访问 `root->right` 节点
8. 访问 `root->right->left` 节点
9. **由于 `root->right->left` 没有子节点，返回上一层**
10. 访问 `root->right->right` 节点
11. **由于 `root->right->right` 没有子节点，结束**

## 查找节点

```c
void print_depth_first_search_recursive(TreeNode *node)
{
    if (node->val == 5) // 找到节点
    {
        printf("%d (Found 5) ", node->val);
        return;
    }
    else
    {
        printf("%d ", node->val);
    }

    if (node->left != NULL)
    {
        print_depth_first_search_recursive(node->left); // 递归调用左子节点
    }

    if (node->right != NULL)
    {
        print_depth_first_search_recursive(node->right); // 递归调用右子节点
    }
}
```

### 测试
```bash
./dfs
0 1 3 4 2 5 (Found 5) 6
```

可以看到，程序找到节点后，依旧会继续遍历

这是因为在找到节点后，**只是返回那个节点的函数调用，而其他的函数调用并没有被取消**

所以，我们需要在找到节点后，取消其他的函数调用

### 取消其他函数调用

```c
bool found = false; // 全局变量，表示是否找到节点

void print_depth_first_search_recursive(TreeNode *node)
{
    if (node->val == 5) // 找到节点
    {
        printf("%d (Found 5) ", node->val);
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
```

### 再次测试

```bash
./dfs
0 1 3 4 2 5 (Found 5)
```

可以看到，程序找到了节点后，就不再继续遍历了