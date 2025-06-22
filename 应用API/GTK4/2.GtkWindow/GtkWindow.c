#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data) // 信号回调函数
{
    GtkWidget *window; // 窗口对象
    window = gtk_application_window_new(GTK_APPLICATION(app)); // 创建窗口对象

    gtk_window_set_title(GTK_WINDOW(window), "Hello World"); // 设置标题
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); // 设置默认尺寸

    gtk_window_present(GTK_WINDOW(window)); // 显示窗口
}

int main(int argc, char **argv) {
    GtkApplication *app; // GtkApplication 对象
    
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS); // 创建 GtkApplication 对象

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL); // 连接信号

    int status = g_application_run(G_APPLICATION(app), argc, argv); // 运行 GtkApplication 对象

    g_object_unref(app); // 释放 GtkApplication 对象
    return status;
}