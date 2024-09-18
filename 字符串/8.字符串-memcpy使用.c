#include <stdio.h>
#include <string.h>

int main() {

char s[] ="abcdefghijklmnopqrstuvwxyz";
char d[27];

memcpy(d,s,sizeof(s));
printf("%d\n",sizeof(s));
printf("%d\n",sizeof(char) * 27);
printf("%s\n",d);

char e[10];
memcpy(e,s+8,sizeof(char) * 9);
e[9] = '\0';
printf("%s\n",e);

return 0;
}