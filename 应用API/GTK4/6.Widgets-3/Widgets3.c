#include <gtk/gtk.h>

static void no_arguments(GtkApplication *app) // 没有命令行参数时的处理函数
{
    g_print("You need to provide a filename as an argument.\n");
    exit(1);
}

static void app_open(GtkApplication *app, GFile **files, gint n_files, gchar *hint) // 有命令行参数时的处理函数
{
    char *contents; // 文件内容
    gsize length; // 文件长度
    char *filename; // 文件名
    GError *error = NULL; // 错误信息

    GtkWidget *window;
    window = gtk_application_window_new(app); // 创建 GtkApplicationWindow 对象

    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600); // 设置默认尺寸

    GtkWidget *notebook = gtk_notebook_new(); // 创建 GtkNotebook 对象
    gtk_window_set_child(GTK_WINDOW(window), notebook); // 设置窗口的子控件

    GtkNotebookPage *notebook_page; // 标签页对象
    GtkWidget *label; // 标签对象
    GtkWidget *scrolled_window; // GtkScrolledWindow 对象
    GtkWidget *text_view; // GtkTextView 对象
    GtkTextBuffer *buffer; // GtkTextBuffer 对象

    
    for (int i = 0; i < n_files; i++)
    {
        if (g_file_load_contents (files[i], NULL, &contents, &length, NULL, &error))
        {
            scrolled_window = gtk_scrolled_window_new(); // 创建 GtkScrolledWindow 对象
            text_view = gtk_text_view_new(); // 创建 GtkTextView 对象
            buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)); // 获取 GtkTextBuffer 对象
            gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD); // 设置换行模式
            gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE); // 设置文本不可编辑
            gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view); // 设置 GtkScrolledWindow 的子控件
            gtk_text_buffer_set_text(buffer, contents, length); // 设置文本内容

            gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view); // 设置 GtkScrolledWindow 的子控件
            g_free(contents); // 释放内存

            if ((filename = g_file_get_basename(files[i])))
            {
                label = gtk_label_new(filename); // 创建 GtkLabel 对象
                g_free(filename); // 释放内存
            }
            else label = gtk_label_new("Untitled"); // 未命名文件

            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scrolled_window, label); // 添加标签页
            notebook_page = gtk_notebook_get_page(GTK_NOTEBOOK(notebook), scrolled_window); // 获取标签页对象
            g_object_set(notebook_page, "tab-expand", TRUE, NULL); // 设置标签页可扩展
        }
        else
        {
            g_printerr("Error loading file: %s\n", error->message);
            g_error_free(error);
        }
    }
    if (gtk_notebook_get_n_pages(GTK_NOTEBOOK(notebook)) > 0) // 如果有标签页，显示窗口
    {
        gtk_window_present(GTK_WINDOW(window)); // 显示窗口
    }
    else // 如果没有标签页，销毁窗口
    {
        gtk_window_destroy(GTK_WINDOW(window));
    }
}

int main(int argc, char **argv) {
    GtkApplication *app; // GtkApplication 对象
    
    app = gtk_application_new("org.gtk.example", G_APPLICATION_HANDLES_OPEN); // 创建 GtkApplication 对象

    g_signal_connect(app, "activate", G_CALLBACK(no_arguments), NULL); // 当没有命令行参数时，调用 no_arguments 函数
    g_signal_connect(app, "open", G_CALLBACK(app_open), NULL); // 当有命令行参数时，调用 app_open 函数

    int status = g_application_run(G_APPLICATION(app), argc, argv); // 运行 GtkApplication 对象

    g_object_unref(app); // 释放 GtkApplication 对象
    return status;
}