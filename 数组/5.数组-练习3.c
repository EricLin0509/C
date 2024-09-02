#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

/*
int min = 0;

int array[10];
for (int i = 0; i < 10; i++)
{
    if (i == 0)
    {
        min = array[0];
    }
    if (min > array[i])
    {
        min = array[i];
    }
}

for (int i = min; i >= 1; i--)
{
    int flag = 0;
    for (int j = 0; j < 10; j++)
    {
        if (array[j]%i != 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("最大公约数是%d\n",i);
    }
    
}
*/

int array[10];
for (int  i = 0; i < 10; i++)
{
    scanf("%d",&array[i]);
}

// 先把最后一个元素存起来
int temp = array[9];

for (int i = 9; i > 0; i--)
{
    array[i] = array[i-1];
}
array[0] = temp;

for (int i = 0; i < 10; i++)
{
    printf("%d ",array[i]);
}
putchar('\n');

return 0;
}