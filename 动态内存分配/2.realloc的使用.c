#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {

int *a = malloc(sizeof(int) * 5);

for (int i = 0; i < 5; i++)
{
    a[i] = i;
}

for (int i = 0; i < 5; i++)
{
    printf("a[%d]=%d\n", i, a[i]);
}
puts("\n");

printf("a_old: %zu\n",a);

a = realloc(a, sizeof(int) * 10); // 重新分配内存，不会清除原来的内存

printf("a_new: %zu\n",a); // 可能会输出原来的内存地址，也可能会输出新的内存地址


//
// a1
// 0    1   2   3   4   5   _   _   _   _   _   // 内存后面有足够的空间的情况
//
// a2                      a3
// 0    1   2   3   4   8   7   0   5   9 // 内存后面没有足够的空间的情况
//

/*
realloc() 的原理
realloc() 先引入原来的指针，然后返回一个新的指针
realloc() 会先判断原来分配的内存后面是否有足够的空间，如果有，就直接返回原来的指针
如果没有，就会重新分配一块新的内存，然后将原来的内存中的数据复制到新的内存中，最后返回新的指针
*/

for (int i = 5; i < 10; i++)
{
    a[i] = i;
}

for (int i = 0; i < 10; i++)
{
    printf("a[%d]=%d\n", i, a[i]); // 输出 0 到 9
}

free(a);


// 安全风险
int *a1 = malloc(sizeof(int) * 5);
printf("a1_old: %zu\n",a1);

for (int i = 0; i < 5; i++)
{
    a1[i] = i;
}

int *save = a1; // 保存原来的指针

a1 = realloc(a1, sizeof(int) * 20);
printf("a1_new: %zu\n",a1);

for (int i = 0; i < 5; i++)
{
    printf("save[%d]=%d\n", i, save[i]); // realloc() 不会清除原来的内存里面的内容，会有安全风险
}

free(a1);

return 0;
}