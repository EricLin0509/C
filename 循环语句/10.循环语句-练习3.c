#include  <stdio.h> 
#include <unistd.h>
int main(int argc, const char * argv[] ) {

/*
int max =0;
for (int  i = 0; i < 6; i++)
{
  int num = 0;
  scanf("%d",&num);
  if (i == 0)
  {
    max = num;
  }
  else if (max < num)
  {
    max = num;
  }
  
}
printf("max = %d\n",max);
*/

for (int i = 0; i <3; i++)
{
  for (int k = 0; k < 3-i-1; k++)
  {
    printf("  ");
  }
  
  for (int j = 0; j < 2*i+1; j++)
  {
    printf("* ");
  }
  printf("\n");
}

return 0;
}