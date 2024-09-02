#include  <stdio.h> 

int main(int argc, const char * argv[] ) {

int array[10];
int temp = 0;

for (int i = 0; i < 10; i++)
{
    scanf("%d",&array[i]);
}

for (int i = 1; i <= 9; i++)
{
    int flag = 0;

    for (int j = 0; j < 10-i; j++)
    {
        if (array[j] > array[j+1])
        {
            temp = array[j];
            array[j] = array[j+1];
            array[j+1] = temp;
            flag = 1;
        }
    }

    if (flag == 0)
    {
        break;
    }
    

    printf("第%d次: ",i);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ",array[i]);
    }
    putchar('\n');

}
for (int i = 0; i < 10; i++)
{
    printf("%d ",array[i]);
}
putchar('\n');

return 0;
}