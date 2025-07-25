/*Warning: Unfinished code, DO NOT RUN!*/

#ifndef FILE_EDITOR_H
#define FILE_EDITOR_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FILE_TYPE_EDITOR file_editor_get_type()

G_DECLARE_FINAL_TYPE(FileEditor, file_editor, FILE, EDITOR, GtkTextView)

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

enum {
    CHANGE_FILE,
    OPEN_RESPONSE,
    NUMBER_OF_SIGNALS
};

static guint signals[NUMBER_OF_SIGNALS];

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

void file_editor_set_file(FileEditor *self, GFile *file)
{
    self->file = file;
}

GFile *file_editor_get_file(FileEditor *self)
{
    return self->file;
}

GtkWidget *file_editor_new()
{
    return GTK_WIDGET(g_object_new(FILE_TYPE_EDITOR, NULL));
}

g_signal_emit(self, signals[CHANGE_FILE], 0);
g_signal_emit(self, signals[OPEN_RESPONSE], 0, RESPONSE_SUCCESS);
g_signal_emit(self, signals[OPEN_RESPONSE], 0, RESPONSE_CANCEL);
g_signal_emit(self, signals[OPEN_RESPONSE], 0, RESPONSE_ERROR);

G_END_DECLS

#endif /* FILE_EDITOR_H */