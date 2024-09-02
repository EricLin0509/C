#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

int a[5] = {1,2,3,4,5};
for (int i = 0; i < 5; i++)
{
    printf("%d",a[i]);
    if (i != 4)
    {
        printf(",");
    }
    
}
putchar('\n');

int array1[10]={0};
int sum = 0;
for (int i = 0; i < 10; i++)
{
    scanf("%d",&array1[i]);
    sum += array1[i];
}
printf("sum = %d\n",sum);
putchar('\n');

for (int i = 0; i < 10; i++)
{
    if (array1[i]%2 == 0)
    {
        printf("%d",array1[i]);
    }
    
}
putchar('\n');

return 0;
}