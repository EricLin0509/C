#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    char *s = g_new(char, 14);
    strcpy(s, "Hello, world!");
    g_print("%s\n", s);
    g_free(s);
    return 0;
}