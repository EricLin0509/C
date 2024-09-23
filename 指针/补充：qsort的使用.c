#include <stdio.h>
#include <stdlib.h>

int compare(const void *num1, const void *num2)
{
    return *(int *)num1 - *(int *)num2; // 此处将 'void *' 强制转换成 'int *'，然后再解引用
}

int main(int argc, const char * argv[]) {
int arr[] = {0,1,9,2,8,3,7,4,6,5};

int size = sizeof(arr) / sizeof(arr[0]);

qsort(arr, size, sizeof(arr[0]), compare);

for (int i = 0; i < size; i++)
{
    printf("%d ",arr[i]);
}
printf("\n");

}