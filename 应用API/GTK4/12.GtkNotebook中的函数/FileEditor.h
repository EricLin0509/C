#ifndef FILE_EDITOR_H
#define FILE_EDITOR_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FILE_TYPE_EDITOR file_editor_get_type()

G_DECLARE_FINAL_TYPE(FileEditor, file_editor, FILE, EDITOR, GtkTextView)

enum ResponseType {
    RESPONSE_SUCCESS,
    RESPONSE_CANCEL,
    RESPONSE_ERROR
};

GFile *file_editor_get_file(FileEditor *self);

void file_editor_open(FileEditor *self, GtkWindow *window);

void file_editor_save(FileEditor *self);

void file_editor_save_as(FileEditor *self);

GtkWidget *file_editor_new_with_file(GFile *file);

GtkWidget *file_editor_new();

G_END_DECLS

#endif /* FILE_EDITOR_H */