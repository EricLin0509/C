#include "myobject.h"

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *obj;

    obj = my_object_new();
    // 使用 obj
}

#include "myobject.h"

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.example.myapp", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}