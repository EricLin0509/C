#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

int array[10];

for (int i = 0; i < 9; i++)
{
    scanf("%d",&array[i]);
}

for (int i = 8; i >= 4; i--)
{
    array[i+1] = array[i];
}
array[4] = 23;

for (int i = 0; i < 10; i++)
{
    printf("%d ",array[i]);
}
putchar('\n');


int array1[10] = {1,2,3,4,5,6,7,8,9,10};

for (int i = 2; i < 10; i++)
{
    array1[i] = array1[i+1];
}

for (int i = 0; i < 10; i++)
{
    printf("%d ",array1[i]);
}
putchar('\n');


int array2[10] = {1,2,3,4,5,6,7,8,9,10};
int max  = array2[0];
int index = 0;

for (int i = 1; i < 10; i++)
{
    if (max < array2[i])
    {
        max = array2[i];
        index = i;
    }
}
for (int i = 0; i < 10; i++)
{
    if (array2[i] == max)
    {
        printf("%d ",i);
    }
    
}

printf("max=%d index=%d\n",max,index);


int array3[10] = {1,2,3,4,5,6,7,8,9,0};
int sum = 0;
sum = array3[0]+array3[1]+array3[2];
int index2 = 0;

for (int i = 0; i < 8; i++)
{
    if (sum <= array3[i]+array3[i+1]+array3[i+2])
    {
        sum =array3[i]+array3[i+1]+array3[i+2],
        index2 = i;
    }
}

for (int i = index2; i <= index2+2; i++)
{
    printf("%d ",array3[i]);
}
putchar('\n');

return 0;
}