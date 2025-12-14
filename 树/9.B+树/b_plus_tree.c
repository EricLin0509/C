#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_KEY_NUM 4
#define MIN_KEY_NUM (MAX_KEY_NUM / 2)

typedef struct BPlusTreeNode {
    int keys[MAX_KEY_NUM];
    struct BPlusTreeNode *child[MAX_KEY_NUM+1]; // 子节点指针数组应该有 `keys_num+1` 个
    int keys_num;
    bool is_leaf; // 是否是叶子节点，只有叶子节点才可以存数据
    struct BPlusTreeNode *parent;

    /* 存储左右兄弟节点指针 (类似于双向链表)，用于快速遍历兄弟节点 */
    struct BPlusTreeNode *left_sibling; // 左兄弟节点
    struct BPlusTreeNode *right_sibling; // 右兄弟节点
} BPlusTreeNode;

// 创建新节点
BPlusTreeNode* create_node(bool is_leaf)
{
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    node->keys_num = 0;
    node->is_leaf = is_leaf;
    node->parent = NULL;
    node->left_sibling = NULL;
    node->right_sibling = NULL;
    
    for (int i = 0; i <= MAX_KEY_NUM; i++)
    {
        node->child[i] = NULL;
    }
    
    return node;
}

// 在节点中查找键值应插入的位置
int find_insert_position(BPlusTreeNode* node, int key)
{
    int pos = 0;
    for (pos = 0; pos < node->keys_num && key > node->keys[pos]; pos++);
    return pos;
}

// 在叶子节点中插入键值
void insert_into_leaf(BPlusTreeNode* leaf, int key)
{
    int pos = find_insert_position(leaf, key);
    
    // 将键值向后移动，腾出位置
    for (int i = leaf->keys_num; i > pos; i--)
    {
        leaf->keys[i] = leaf->keys[i-1];
    }
    
    // 插入新键值
    leaf->keys[pos] = key;
    leaf->keys_num++;
}

// 分裂叶子节点
BPlusTreeNode* split_leaf_node(BPlusTreeNode* leaf, int* promoted_key)
{
    // 创建新的叶子节点
    BPlusTreeNode* new_leaf = create_node(true);
    
    // 确定分裂点（中间位置）
    int split_point = (leaf->keys_num + 1) / 2;
    
    // 将一半键值移到新节点
    int new_index = 0;
    for (int i = split_point; i < leaf->keys_num; i++)
    {
        new_leaf->keys[new_index++] = leaf->keys[i];
    }
    
    // 更新节点键值数量
    new_leaf->keys_num = leaf->keys_num - split_point;
    leaf->keys_num = split_point;
    
    // 提升的键值是new_leaf的第一个键值
    *promoted_key = new_leaf->keys[0];
    
    // 更新兄弟指针
    new_leaf->right_sibling = leaf->right_sibling;
    new_leaf->left_sibling = leaf;
    
    if (leaf->right_sibling != NULL)
    {
        leaf->right_sibling->left_sibling = new_leaf;
    }
    
    leaf->right_sibling = new_leaf;
    
    // 新节点与父节点相同
    new_leaf->parent = leaf->parent;
    
    return new_leaf;
}

// 分裂内部节点
BPlusTreeNode* split_internal_node(BPlusTreeNode* internal, int* promoted_key)
{
    // 创建新的内部节点
    BPlusTreeNode* new_internal = create_node(false);
    
    // 确定分裂点
    int split_point = internal->keys_num / 2;
    
    // 保存要提升的键值
    *promoted_key = internal->keys[split_point];
    
    // 复制一半键值到新节点
    int new_index = 0;
    for (int i = split_point + 1; i < internal->keys_num; i++)
    {
        new_internal->keys[new_index++] = internal->keys[i];
    }
    
    // 复制子指针到新节点
    int child_index = 0;
    for (int i = split_point + 1; i <= internal->keys_num; i++)
    {
        new_internal->child[child_index++] = internal->child[i];
        if (internal->child[i] != NULL)
        {
            internal->child[i]->parent = new_internal;
        }
    }
    
    // 更新节点键值数量
    new_internal->keys_num = internal->keys_num - split_point - 1;
    internal->keys_num = split_point;
    
    // 新节点与父节点相同
    new_internal->parent = internal->parent;
    
    return new_internal;
}

// 在内部节点中插入键值和子指针
void insert_into_internal(BPlusTreeNode* node, int key, BPlusTreeNode* right_child)
{
    int pos = find_insert_position(node, key);
    
    // 移动键值为新键值腾出空间
    for (int i = node->keys_num; i > pos; i--)
    {
        node->keys[i] = node->keys[i-1];
    }
    
    // 移动子指针
    for (int i = node->keys_num + 1; i > pos + 1; i--)
    {
        node->child[i] = node->child[i-1];
    }
    
    // 插入新键值和子指针
    node->keys[pos] = key;
    node->child[pos + 1] = right_child;
    node->keys_num++;
    
    if (right_child != NULL)
    {
        right_child->parent = node;
    }
}

// 找到键值应该插入的叶子节点
BPlusTreeNode* find_leaf_node(BPlusTreeNode* root, int key)
{
    BPlusTreeNode* current = root;
    
    while (!current->is_leaf)
    {
        int i = 0;
        while (i < current->keys_num && key >= current->keys[i])
        {
            if (key < current->keys[i])
            {
                break;
            }
            i++;
        }
        current = current->child[i];
    }
    
    return current;
}

// 插入操作的入口函数
BPlusTreeNode* bplus_tree_insert(BPlusTreeNode* root, int key)
{
    // 如果树为空，创建根节点（叶子节点）
    if (root == NULL)
    {
        root = create_node(true);
        insert_into_leaf(root, key);
        return root;
    }
    
    // 找到应该插入的叶子节点
    BPlusTreeNode* leaf = find_leaf_node(root, key);
    
    // 检查键值是否已存在
    for (int i = 0; i < leaf->keys_num; i++)
    {
        if (leaf->keys[i] == key)
        {
            printf("Key %d already exists in the tree.\n", key);
            return root;
        }
    }
    
    // 插入到叶子节点
    insert_into_leaf(leaf, key);
    
    // 如果叶子节点没有溢出，直接返回
    if (leaf->keys_num <= MAX_KEY_NUM)
    {
        return root;
    }
    
    // 叶子节点溢出，需要分裂
    BPlusTreeNode* current = leaf;
    int promoted_key;
    BPlusTreeNode* new_child = NULL;
    
    while (current->keys_num > MAX_KEY_NUM)
    {
        if (current->is_leaf)
        {
            new_child = split_leaf_node(current, &promoted_key);
        }
        else
        {
            new_child = split_internal_node(current, &promoted_key);
        }
        
        // 如果当前节点是根节点，创建新的根节点
        if (current->parent == NULL)
        {
            BPlusTreeNode* new_root = create_node(false);
            new_root->keys[0] = promoted_key;
            new_root->keys_num = 1;
            new_root->child[0] = current;
            new_root->child[1] = new_child;
            
            current->parent = new_root;
            new_child->parent = new_root;
            
            root = new_root;
            break;
        }
        else
        {
            // 否则，将提升的键值插入到父节点
            insert_into_internal(current->parent, promoted_key, new_child);
            current = current->parent;
        }
    }
    
    return root;
}

// 辅助函数：打印B+树
void print_bplus_tree(BPlusTreeNode* node, int level)
{
    if (node == NULL) return;
    
    printf("Level %d: ", level);
    if (node->is_leaf)
    {
        printf("Leaf [");
        for (int i = 0; i < node->keys_num; i++)
        {
            printf("%d", node->keys[i]);
            if (i < node->keys_num - 1) printf(", ");
        }
        printf("]\n");
    }
    else
    {
        printf("Internal [");
        for (int i = 0; i < node->keys_num; i++)
        {
            printf("%d", node->keys[i]);
            if (i < node->keys_num - 1) printf(", ");
        }
        printf("]\n");
        
        for (int i = 0; i <= node->keys_num; i++)
        {
            print_bplus_tree(node->child[i], level + 1);
        }
    }
}

BPlusTreeNode *find_leftmost_leaf(BPlusTreeNode *root) // 找到最左边的叶子节点
{
    BPlusTreeNode *current = root;

    while (!current->is_leaf)
    {
        current = current->child[0];
    }

    return current;
}

void range_query(BPlusTreeNode* leaf, int min_key, int max_key) // 范围查询
{
    BPlusTreeNode* current = leaf;

    while (current != NULL)
    {
        for (int i = 0; i < current->keys_num; i++)
        {
            if (current->keys[i] >= min_key && current->keys[i] <= max_key) printf("%d ", current->keys[i]);
            else continue;
        }
        current = current->right_sibling;
    }
}

// 测试函数
int main(void) {
    BPlusTreeNode* root = NULL;
    
    printf("Inserting keys into B+ tree...\n");
    
    // 插入一些测试数据
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17, 3, 25, 15, 8, 22};
    int num_keys = sizeof(keys) / sizeof(keys[0]);
    
    for (int i = 0; i < num_keys; i++) {
        printf("Inserting %d...\n", keys[i]);
        root = bplus_tree_insert(root, keys[i]);
        print_bplus_tree(root, 0);
        printf("\n");
    }
    
    BPlusTreeNode *leftmost_leaf = find_leftmost_leaf(root);
    printf("Leftmost leaf: ");

    range_query(leftmost_leaf, 10, 30);
    printf("\n");

    return 0;
}