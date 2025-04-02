# 广度优先搜索

## 定义

广度优先搜索（Breadth-First Search，BFS）是一种图形搜索算法，用于在图形或树结构中查找特定节点或路径。它从起始节点开始，逐层向外扩展，直到找到目标节点或遍历完整个图

## 图解

**图中节点的数字代表访问的顺序**

![BFS](./imgs/BFS.png)

可以看到，BFS 是从根节点开始，沿着树的宽度遍历树的节点。如果所有节点均被访问，则算法中止

## 代码实现

```c
void print_breadth_first_search(TreeNode *root);
```

- root: 根节点

### 创建队列

我们可以把广度优先搜索想象成一组元素排队，然后移除这些元素

可以发现，当第一个元素排队时，它是第一个被移除的，这与队列的性质相吻合

```c
void print_breadth_first_search(TreeNode *root)
{
    TreeNode *queue[100];
    size_t queue_num = 0;
}
```

### 将队列的初始值设置为根节点

```c
void print_breadth_first_search(TreeNode *root)
{
    TreeNode *queue[100];
    size_t queue_num = 0;

    queue[queue_num++] = root; // 将根节点入队
}
```

### 循环遍历节点

```c
void print_breadth_first_search(TreeNode *root)
{
    TreeNode *queue[100];
    size_t queue_num = 0;

    queue[queue_num++] = root; // 将根节点入队

    while (queue_num > 0)
    {
        TreeNode *curr = queue[0];
        queue_num--; // 队列长度减一

        printf("%d ", curr->val);
    }
    printf("\n");
}
```

### 向队列中添加子节点

通过判断子节点是否为 `NULL` 来判断是否有子节点

```c
void print_breadth_first_search(TreeNode *root)
{
    TreeNode *queue[100];
    size_t queue_num = 0;

    queue[queue_num++] = root; // 将根节点入队

    while (queue_num > 0)
    {
        TreeNode *curr = queue[0];
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
gcc -o bfs bfs.c
./bfs
段错误 (核心已转储)
```

可以看到，程序崩溃了

**这是因为，我们在对元素进行出列时，并没有将队头完全删除，而是覆盖了第二位及之后的元素**

### 修复

要保证元素进行出列时将队头完全删除，**需要将队列中的元素向前移动**

```c
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
```

遍历到 `queue_num - 1` 是因为最后一个元素不需要移动

[源代码](广度优先搜索.c)

### 再次测试

```bash
gcc -o bfs bfs.c
./bfs
0 1 2 3 4 5 6
```

可以看到，输出顺序正确