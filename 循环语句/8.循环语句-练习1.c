#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

int m = 8;
int n = 3;
int sum = 1;

for (int i=0; i<n; i++)
{
    sum *= m;
    if (m == 0)
    {
        sum = 0;
    }
    
}

printf("m^3 = %d\n",sum);
 

int a = 1;
while (1)
{
    if (a%3==2 && a%5==3 && a%7==4)
    {
        break;
    }
    a++;
}
printf("士兵人数%d\n",a);

char temp = '0';
while (temp != '\n')
{
    temp = getchar();
    putchar(temp);
}


return 0;
}