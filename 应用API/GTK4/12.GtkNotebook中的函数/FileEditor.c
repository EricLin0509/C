#include "FileEditor.h"

enum {
    CHANGE_FILE,
    OPEN_RESPONSE,
    NUMBER_OF_SIGNALS
};

static guint signals[NUMBER_OF_SIGNALS];

struct _FileEditor {
    GtkTextView parent_instance;
    GFile *file;
};

G_DEFINE_FINAL_TYPE(FileEditor, file_editor, GTK_TYPE_TEXT_VIEW);

static void file_editor_dispose(GObject *object)
{
    FileEditor *self = FILE_EDITOR(object);

    g_clear_object(&self->file);

    G_OBJECT_CLASS(file_editor_parent_class)->dispose(object);
}

static void file_editor_finalize(GObject *object)
{
    G_OBJECT_CLASS(file_editor_parent_class)->finalize(object);
}

static void file_editor_init(FileEditor *self) {    }
static void file_editor_class_init(FileEditorClass *class)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(class);

    gobject_class->dispose = file_editor_dispose;
    gobject_class->finalize = file_editor_finalize;

    // 注册信号
    signals[CHANGE_FILE] = g_signal_new("change-file",
    G_TYPE_FROM_CLASS (class),
    G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
    0, // 信号的详细信息
    NULL, // 信号类型
    NULL, // 信号的元数据
    NULL, // 信号的描述
    G_TYPE_NONE, // 返回值类型
    0 // 信号参数数量
    );

    signals[OPEN_RESPONSE] = g_signal_new("open-response",
    G_TYPE_FROM_CLASS (class),
    G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
    0, // 信号的详细信息
    NULL, // 信号类型
    NULL, // 信号的元数据
    NULL, // 信号的描述
    G_TYPE_NONE, // 返回值类型
    1, // 信号参数数量
    G_TYPE_INT // 信号参数类型
    );
}

/* 打开文件 */
GtkWidget *file_editor_new_with_file(GFile *file)
{
    g_return_val_if_fail(G_IS_FILE(file), NULL);

    GtkWidget *self;
    GtkTextBuffer *buffer;
    char *contents; // 文件内容
    gsize length; // 文件大小

    if (!g_file_load_contents(file, NULL, &contents, &length, NULL, NULL)) return NULL; // 读取文件内容，如果失败则返回 NULL

    self = file_editor_new(); // 创建 FileEditor 实例
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(self)); // 获取 GtkTextBuffer 实例
    gtk_text_buffer_set_text(buffer, contents, length); // 设置 GtkTextBuffer 内容
    FILE_EDITOR(self)->file = g_file_dup(file); // 保存文件路径
    gtk_text_buffer_set_modified(buffer, FALSE); // 设置 GtkTextBuffer 修改状态为未修改
    g_free(contents); // 释放内存

    return self;
}

/* 创建 FileEditor 实例 */
GtkWidget *file_editor_new()
{
    return GTK_WIDGET(g_object_new(FILE_TYPE_EDITOR, "wrap-mode", GTK_WRAP_WORD_CHAR, NULL));
}

/* 保存文件 */
static gboolean save_file(GFile *file, GtkTextBuffer *buffer, GtkWindow *window)
{
    GtkTextIter start;
    GtkTextIter end;
    char *contents;
    gboolean result;
    GtkAlertDialog *dialog;
    GError *error = NULL;

    gtk_text_buffer_get_bounds(buffer, &start, &end); // 获取 GtkTextBuffer 内容的开始和结束位置
    contents = gtk_text_buffer_get_text(buffer, &start, &end, FALSE); // 获取 GtkTextBuffer 内容
    result = g_file_replace_contents(file, contents, strlen(contents), NULL, TRUE, G_FILE_CREATE_NONE, NULL, NULL, &error); // 保存文件内容

    if (result) gtk_text_buffer_set_modified(buffer, FALSE); // 设置 GtkTextBuffer 修改状态为未修改
    else
    {
        dialog = gtk_alert_dialog_new("%s", error->message);
        gtk_alert_dialog_show(dialog, window);
        g_object_unref(dialog);
        g_error_free(error);
    }
    g_free(contents);

    return result;
}

/* 保存对话框的回调函数 */
static void save_dialog_cb(GObject *source_object, GAsyncResult *res, gpointer data)
{
    GtkFileDialog *dialog = GTK_FILE_DIALOG (source_object);
    FileEditor *self = FILE_EDITOR(data);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(self));
    GFile *file;
    GtkWidget*window = gtk_widget_get_ancestor(GTK_WIDGET(self), GTK_TYPE_WINDOW);
    GError *error = NULL;
    GtkAlertDialog *alert_dialog;

    if (((file = gtk_file_dialog_save_finish (dialog, res, &error)) != NULL) && save_file(file, buffer, GTK_WINDOW (window)))
    {
        if (!(G_IS_FILE(self->file) && g_file_equal(file, self->file)))
        {
            if (G_IS_FILE(self->file)) g_object_unref(self->file);

            self->file = file;
            g_signal_emit(self, signals[CHANGE_FILE], 0); // 上一章的自定义信号
        }
    }
    if (error)
    {
        alert_dialog = gtk_alert_dialog_new("%s", error->message);
        gtk_alert_dialog_show(alert_dialog, GTK_WINDOW(window));
        g_object_unref(alert_dialog);
        g_error_free(error);
    }
}

/* 保存文件或另存为 */
void file_editor_save(FileEditor *self)
{
    g_return_if_fail(FILE_EDITOR(self));

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(self));
    GtkWidget *window = gtk_widget_get_ancestor(GTK_WIDGET(self), GTK_TYPE_WINDOW);

    if (!gtk_text_buffer_get_modified(buffer)) return; // 如果文件未修改，则直接返回
    else if (self->file == NULL) file_editor_save_as(self); // 如果文件不存在，则调用另存为
    else save_file(self->file, buffer, GTK_WINDOW(window)); // 保存文件
}

/* 另存为 */
void file_editor_save_as(FileEditor *self)
{
    g_return_if_fail(FILE_EDITOR(self));

    GtkWidget *window = gtk_widget_get_ancestor(GTK_WIDGET(self), GTK_TYPE_WINDOW);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(self));
    GtkFileDialog *dialog = gtk_file_dialog_new();
    
    gtk_file_dialog_save(dialog, GTK_WINDOW(window), NULL, save_dialog_cb, self); // 显示文件选择对话框，并设置回调函数
}

/* 打开文件的回调函数 */
static void open_dialog_cb(GObject *source_object, GAsyncResult *res, gpointer data)
{
    GtkFileDialog *dialog = GTK_FILE_DIALOG (source_object);
    FileEditor *self = FILE_EDITOR(data);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(self));
    GtkWidget *window = gtk_widget_get_ancestor(GTK_WIDGET(self), GTK_TYPE_WINDOW);
    GFile *file;
    char *contents;
    gsize length;
    gboolean is_file_changed;
    GtkAlertDialog *alert_dialog;
    GError *error = NULL;

    if ((file = gtk_file_dialog_open_finish (dialog, res, &error)) != NULL && g_file_load_contents(file, NULL, &contents, &length, NULL, &error))
    {
        gtk_text_buffer_set_text(buffer, contents, length); // 设置 GtkTextBuffer 内容
        g_free (contents);
        gtk_text_buffer_set_modified(buffer, FALSE); // 设置 GtkTextBuffer 修改状态为未修改
        is_file_changed = (G_IS_FILE(self->file) && g_file_equal(file, self->file)) ? FALSE : TRUE; // 判断文件是否改变
        if (G_IS_FILE(self->file)) g_object_unref(self->file); // 释放旧文件
        if (is_file_changed) g_signal_emit(self, signals[CHANGE_FILE], 0); // 上一章的自定义信号
    }
    else
    {
        if (error->code == GTK_DIALOG_ERROR_DISMISSED) // 用户点击取消按钮
        {
            g_signal_emit(self, signals[OPEN_RESPONSE], 0, RESPONSE_CANCEL); // 上一章的自定义信号
        }
        else
        {
            alert_dialog = gtk_alert_dialog_new("%s", error->message);
            gtk_alert_dialog_show(alert_dialog, GTK_WINDOW(window));
            g_object_unref(alert_dialog);
            g_signal_emit(self, signals[OPEN_RESPONSE], 0, RESPONSE_ERROR); // 上一章的自定义信号
        }
        g_clear_error(&error);
    }
}

/* 打开文件 */
void file_editor_open(FileEditor *self, GtkWindow *window)
{
    g_return_if_fail(FILE_EDITOR(self));

    g_return_if_fail(GTK_IS_WINDOW(window) || window == NULL);
    
    GtkFileDialog *dialog = gtk_file_dialog_new();
    gtk_file_dialog_open(dialog, window, NULL, open_dialog_cb, self); // 显示文件选择对话框，并设置回调函数
    g_object_unref(dialog);
}

/* 获取 GFile 实例 */
GFile *file_editor_get_file(FileEditor *self)
{
    g_return_val_if_fail(FILE_EDITOR(self), NULL);

    if (G_IS_FILE(self->file)) return g_file_dup(self->file);
    else return NULL;
}