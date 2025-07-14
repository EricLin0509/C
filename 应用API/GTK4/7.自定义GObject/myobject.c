#include "myobject.h"

struct _MyObject {
    GtkWidget parent_instance;
};

G_DEFINE_TYPE(MyObject, my_object, GTK_TYPE_WIDGET)

static void my_object_init(MyObject *self) {
    // 初始化实例
}

static void my_object_class_init(MyObjectClass *class) {
    // 注册方法和信号
}

GtkWidget *my_object_new(void) {
    return g_object_new(MY_TYPE_OBJECT, NULL);
}