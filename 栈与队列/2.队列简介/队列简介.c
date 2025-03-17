#include <stdio.h>

int queue[256];
int size = 0;

void insert(int element)
{
    if (size == 256)
    {
        perror("queue is full");
        return;
    }

    queue[size] = element;
    size++;
}

int main(int argc, const char *argv[]) {

    insert(1);
    insert(2);
    insert(3);
    insert(4);

    for (int i = 0; i < size; i++)
    {
        printf("%d\n", queue[i]);
    }
    

}