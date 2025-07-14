#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define MY_TYPE_OBJECT my_object_get_type()
G_DECLARE_FINAL_TYPE(MyObject, my_object, MY, OBJECT, GtkWidget)

GtkWidget *my_object_new(void);

G_END_DECLS

#endif