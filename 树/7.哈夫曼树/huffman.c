#include <stdio.h>
#include <stdlib.h>

typedef struct HuffmanNode {
    char data;
    int weight;
    struct HuffmanNode *left, *right, *parent;
} HuffmanNode;

typedef struct {
    HuffmanNode **nodes;
    int size;
} HuffmanTree;

// 初始化哈夫曼树
HuffmanTree* initTree(int capacity)
{
    HuffmanTree *tree = malloc(sizeof(HuffmanTree));
    tree->nodes = malloc(sizeof(HuffmanNode*) * capacity);
    tree->size = 0;
    return tree;
}

// 插入节点到堆中（保持最小堆）
void insertNode(HuffmanTree *tree, HuffmanNode *node)
{
    int i = tree->size++;
    while(i > 0)
    {
        int parent = (i - 1) / 2;
        if(tree->nodes[parent]->weight <= node->weight) break;
        tree->nodes[i] = tree->nodes[parent];
        i = parent;
    }
    tree->nodes[i] = node;
}

// 从堆中提取最小节点
HuffmanNode* extractMin(HuffmanTree *tree)
{
    HuffmanNode *min = tree->nodes[0];
    HuffmanNode *last = tree->nodes[--tree->size];
    
    int i = 0, child;
    while((child = 2*i + 1) < tree->size)
    {
        if(child + 1 < tree->size && tree->nodes[child+1]->weight < tree->nodes[child]->weight) child++;
        if(last->weight <= tree->nodes[child]->weight) break;
        tree->nodes[i] = tree->nodes[child];
        i = child;
    }
    tree->nodes[i] = last;
    return min;
}

// 构建哈夫曼树
void buildHuffmanTree(HuffmanTree *tree)
{
    while(tree->size > 1) {
        HuffmanNode *left = extractMin(tree);
        HuffmanNode *right = extractMin(tree);
        
        HuffmanNode *parent = malloc(sizeof(HuffmanNode));
        parent->weight = left->weight + right->weight;
        parent->left = left;
        parent->right = right;
        left->parent = right->parent = parent;
        
        insertNode(tree, parent);
    }
}

// 生成哈夫曼编码（递归实现）
void generateCodes(HuffmanNode *node, char *code, int depth)
{
    if(!node->left && !node->right)
    {
        code[depth] = '\0';
        printf("字符 %c 的编码: %s\n", node->data, code);
        return;
    }
    
    if(node->left)
    {
        code[depth] = '0';
        generateCodes(node->left, code, depth + 1);
    }
    if(node->right)
    {
        code[depth] = '1';
        generateCodes(node->right, code, depth + 1);
    }
}

int main(int argc, const char * argv[]) {
    // 示例数据（可修改）
    char chars[] = {'A', 'B', 'C', 'D'};
    int weights[] = {5, 2, 1, 1};  // 权重示例
    
    HuffmanTree *tree = initTree(7);  // 总节点数 = 2n-1
    
    // 创建叶子节点
    for(int i = 0; i < 4; i++)
    {
        HuffmanNode *node = malloc(sizeof(HuffmanNode));
        node->data = chars[i];
        node->weight = weights[i];
        node->left = node->right = node->parent = NULL;
        insertNode(tree, node);
    }
    
    buildHuffmanTree(tree);
    
    char code[32];
    generateCodes(tree->nodes[0], code, 0);
    
    // 释放内存（略）
    return 0;
}