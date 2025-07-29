#include "FileEditorNotebook.h"

static char *get_title() // 获取新页面的标题
{
    static int c = -1;
    if (++c == 0) return (g_strdup_printf("Untitled"));
    else return (g_strdup_printf ("Untitled %u", c));
}

static void file_changed_cb(GtkWidget *self, GtkNotebook *notebook)
{
    GtkWidget *scrolled_window;
    GtkWidget *label;
    GFile *file;
    char *filename;

    file = file_editor_get_file(self);
    scrolled_window = gtk_widget_get_parent(GTK_WIDGET(self));
    if (G_IS_FILE(file))
    {
        filename = g_file_get_basename(file);
        g_object_unref(file);
    }
    else
    {
        filename = get_title();
    }
    label = gtk_label_new(filename);
    g_free(filename);
    gtk_notebook_set_tab_label(notebook, scrolled_window, label);
}

static void notebook_page_build(GtkNotebook *notebook, GtkWidget *self, const char *filename) // 创建新页面
{
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    GtkNotebookPage *page;
    GtkWidget *label;
    int i;

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), self);
    label = gtk_label_new(filename);
    i = gtk_notebook_append_page(notebook, scrolled_window, label);
    page =gtk_notebook_get_page(notebook, scrolled_window);
    gtk_notebook_set_current_page(notebook, i);
    g_signal_connect(GTK_self(self), "change-file", G_CALLBACK(file_changed_cb), notebook);
}

void notebook_page_new(GtkNotebook *notebook)
{
    g_return_if_fail(GTK_IS_NOTEBOOK(notebook));

    GtkWidget *self;
    char *filename;

    self = file_editor_new();
    filename = get_title();
    notebook_page_build(notebook, self, filename);
    g_free(filename);
}

static void open_response_cb(FileEditor *self, int response, GtkNotebook *notebook)
{
    GFile *file;
    char *filename;

    if (response != RESPONSE_SUCCESS)
    {
        g_object_ref_sink(self);
        g_object_unref(self);
    }
    else
    {
        file = file_editor_get_file(self);
        filename = g_file_get_basename(file);
        g_object_unref(file);
        notebook_page_build(notebook, GTK_WIDGET(self), filename);
        g_free(filename);
    }
}

void notebook_page_open(GtkNotebook *notebook)
{
    g_return_if_fail(GTK_IS_NOTEBOOK(notebook));

    GtkWidget *self;

    self = file_editor_new();
    g_signal_connect(self, "open-response", G_CALLBACK(open_response_cb), notebook);
    file_editor_open(FILE_EDITOR(self));
}

void notebook_page_close(GtkNotebook *notebook)
{
    g_return_if_fail(GTK_IS_NOTEBOOK(notebook));

    GtkWidget *window;
    int i;

    if (gtk_notebook_get_n_pages(notebook) == 1)
    {
        window = gtk_widget_get_ancestor(GTK_WIDGET(notebook), GTK_TYPE_WINDOW);
        gtk_window_destroy(GTK_WINDOW(window));
    }
    else
    {
        i = gtk_notebook_get_current_page(notebook);
        gtk_notebook_remove_page(GTK_NOTEBOOK(notebook), i);
    }
}

static void get_current_file_editor(GtkNotebook *notebook) // 获取当前页的文件编辑器
{
    int i;
    GtkWidget *self;
    GtkWidget *scrolled_window;

    i = gtk_notebook_get_current_page(notebook);
    scrolled_window = gtk_notebook_get_nth_page(notebook, i);
    self = gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scrolled_window));
    return FILE_EDITOR(self);
}

void notebook_page_save(GtkNotebook *notebook)
{
    g_return_if_fail(GTK_IS_NOTEBOOK(notebook));

    FileEditor *self;

    self = get_current_file_editor(notebook);
    file_editor_save(self);
}