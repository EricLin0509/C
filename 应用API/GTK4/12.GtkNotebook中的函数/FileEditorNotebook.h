#ifndef FILE_EDITOR_NOTEBOOK_H
#define FILE_EDITOR_NOTEBOOK_H

#include "FileEditor.h"

void notebook_page_save(GtkNotebook *notebook);

void notebook_page_close (GtkNotebook *notebook);

void notebook_page_open (GtkNotebook *notebook);

void notebook_page_new_with_file (GtkNotebook *notebook, GFile *file);

void notebook_page_new (GtkNotebook *notebook);

#endif /* FILE_EDITOR_NOTEBOOK_H */