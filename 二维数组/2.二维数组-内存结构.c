#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

// 验证二维数组内存是连续的

int arr[3][5] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15}};
for (int i = 0; i < 3; i++)
{
    for (int j = 0; j < 4; j++)
    {
        printf("%p ", &arr[i][j]);
    }
}
printf("\n");

/*
输出：0x753b32380400 0x753b32380404 0x753b32380408 0x753b3238040c 0x753b32380414 0x753b32380418 0x753b3238041c 0x753b32380420 0x753b32380428 0x753b3238042c 0x753b32380430 0x753b32380434
注意：一个整形变量为4个字节
*/

int arr1[2][3] = {1,2,3,4,5,6};
int arr2[2][3] = {10,20,30,40,50,60};

for (int i = 0; i < 2; i++)
{
    for (int j = 0; j < 3; j++)
    {
        printf("%d+%d=%d\n",arr1[i][j],arr2[i][j],arr1[i][j]+arr2[i][j]);
    }
    
}


return 0;
}