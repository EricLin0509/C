#include <gtk/gtk.h>

static void clicked_button1(GtkButton *button)
{
    const char *s;
    s = gtk_button_get_label(button);
    
    if (strcmp(s, "Hello") == 0)
    {
        gtk_button_set_label(button, "Goodbye");
    }
    else
    {
        gtk_button_set_label(button, "Hello");
    }
}

static void clicked_button2(GtkButton *button, GtkWindow *window)
{
    gtk_window_destroy(GTK_WINDOW(window)); // 关闭窗口
}

static void activate(GtkApplication* app, gpointer user_data) // 信号回调函数
{
    GtkWidget *window; // 窗口对象
    window = gtk_application_window_new(GTK_APPLICATION(app)); // 创建窗口对象

    gtk_window_set_title(GTK_WINDOW(window), "Hello World"); // 设置标题
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); // 设置默认尺寸

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // 创建垂直方向的 GtkBox
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE); // 设置 GtkBox 控件的子控件是否等宽

    gtk_window_set_child(GTK_WINDOW(window), box); // 将box控件合并到窗口中

    GtkWidget *button1 = gtk_button_new_with_label("Hello");
    GtkWidget *button2 = gtk_button_new_with_label("Close");

    g_signal_connect(button1, "clicked", G_CALLBACK(clicked_button1), NULL); // 连接信号
    g_signal_connect(button2, "clicked", G_CALLBACK(clicked_button2), window); // 连接信号

    gtk_box_append(GTK_BOX(box), button1); // 将button1添加到box中
    gtk_box_append(GTK_BOX(box), button2); // 将button2添加到box中

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