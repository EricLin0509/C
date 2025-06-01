#include <stdio.h>
#include <string.h>

#define MAX_HEAP_SIZE 100

typedef struct Heap {
    int data[MAX_HEAP_SIZE];
    int size;
} Heap;

void sift_up(Heap *heap, int index)
{
    int parent_index = (index - 1) / 2; // 父节点的下标

    while (index > 0 && heap->data[parent_index]) // 节点不是根节点，且节点比父节点大
    {        
        // 交换节点
        int temp = heap->data[index];
        heap->data[index] = heap->data[parent_index];
        heap->data[parent_index] = temp;

        // 更新下标
        index = parent_index;
        parent_index = (index - 1) / 2;
    }
}

void sift_down(Heap *heap, int index)
{
    int left_child_index = index * 2 + 1; // 左子节点的下标
    int right_child_index = index * 2 + 2; // 右子节点的下标

    while (left_child_index < heap->size && 
        heap->data[index] < heap->data[left_child_index] ||
        right_child_index < heap->size) // 节点不是叶子节点，且节点比子节点小
    {
        // 查找最大子节点
        int max_child_index = 0;
        if (right_child_index < heap->size && heap->data[left_child_index] < heap->data[right_child_index]) // 右子节点存在，且右子节点比左子节点大
        {
            max_child_index = right_child_index;
        }
        else max_child_index = left_child_index; // 左子节点存在，且左子节点比右子节点大

        // 交换节点
        int temp = heap->data[index];
        heap->data[index] = heap->data[max_child_index];
        heap->data[max_child_index] = temp;

        // 更新节点的下标
        index = max_child_index;
        left_child_index = index * 2 + 1;
        right_child_index = index * 2 + 2;
    }
}

int remove_max(Heap *heap)
{
    // 将根节点和最后一个节点交换
    int temp = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];

    heap->size--; // 堆的大小减一

    sift_down(heap, 0); // 下沉根节点

    return temp; // 返回根节点的值
}

void build_heap(Heap *heap, int *data, int size)
{
    heap->size = size; // 堆的大小
    memcpy(heap->data, data, size *sizeof(int)); // 复制数组到堆中
    for (int i = size / 2 - 1; i >= 0; i--) // 从最后一个非叶子节点开始，依次上浮节点
    {
        sift_down(heap, i); // 下沉节点
    }
}

void heap_sort(int *data, int size)
{
    Heap heap; // 堆
    build_heap(&heap, data, size); // 构建堆
    for (int i = size - 1; i >= 0; i--) // 从最后一个节点开始，依次取出最大/最小节点
    {
        data[i] = remove_max(&heap); // 取出最大节点
    }
}

int main(int argc, const char *argv[]) {
    int data[] = {3, 5, 7, 2, 4, 6, 8, 1, 9};
    int size = sizeof(data) / sizeof(int);
    heap_sort(data, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    return 0;
}