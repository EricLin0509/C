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

static void file_editor_init(FileEditor *self) {    }
static void file_editor_class_init(FileEditorClass *class) {    }

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

G_END_DECLS

#endif /* FILE_EDITOR_H */