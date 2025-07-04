#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data) // 信号回调函数
{
    GtkWidget *window; // 窗口对象
    window = gtk_application_window_new(GTK_APPLICATION(app)); // 创建窗口对象

    gtk_window_set_title(GTK_WINDOW(window), "Hello World"); // 设置标题
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); // 设置默认尺寸

    GtkWidget *scrolled_window = gtk_scrolled_window_new(); // 创建 GtkScrolledWindow 实例
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window); // 设置窗口的子控件

    GtkWidget *text_view = gtk_text_view_new();
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    gchar *text = "C is a general-purpose programming language. It was created in the 1970s by Dennis Ritchie and remains very widely used and influential. By design, C's features cleanly reflect the capabilities of the targeted CPUs. It has found lasting use in operating systems code (especially in kernels[10]), device drivers, and protocol stacks, but its use in application software has been decreasing C is commonly used on computer architectures that range from the largest supercomputers to the smallest microcontrollers and embedded systems. ";

    gtk_text_buffer_set_text(buffer, text, -1); // 设置文本内容
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD); // 设置换行模式

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view); // 设置 GtkScrolledWindow 的子控件

    gtk_window_set_child(GTK_WINDOW(window), text_view); // 设置窗口子部件

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