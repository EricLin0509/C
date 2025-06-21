#include <gtk/gtk.h>

static void
activate (GApplication *app, gpointer *user_data)
{
    g_print ("GtkApplication is activated.\n");
}

int main(int argc, char **argv) {
    GtkApplication *app; // 声明 GtkApplication 对象
    app = gtk_application_new("org.example.myapp", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app); // 释放 GtkApplication 对象
    return status; // 返回应用程序的退出状态
}