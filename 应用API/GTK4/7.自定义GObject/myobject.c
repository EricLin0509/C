#include "myobject.h"

struct _MyObject {
    GtkWidget parent_instance;
};

G_DEFINE_TYPE(MyObject, my_object, GTK_TYPE_WIDGET)

static void my_object_dispose(GObject *gobject)
{
    MyObject *self = MY_OBJECT(gobject);

    // 释放对其他实例的引用
    // g_clear_object(&self->other_object); // 由于 `MyObject` 除了 `parent_instance` 字段 (继承父类) 外，没有其他字段引用其他实例，所以不需要调用 `g_clear_object`

    G_OBJECT_CLASS(my_object_parent_class)->dispose(gobject); // 调用父类的 `dispose` 方法
}

static void my_object_finalize(GObject *gobject)
{
    G_OBJECT_CLASS(my_object_parent_class)->finalize(gobject); // 调用父类的 `finalize` 方法
}

static void my_object_init(MyObject *self) {
    // 初始化实例
}

static void my_object_class_init(MyObjectClass *class)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(class); // 获取父类

    // 注册 `dispose` 方法
    gobject_class->dispose = my_object_dispose;

    // 注册 `finalize` 方法
    gobject_class->finalize = my_object_finalize;
}

GtkWidget *my_object_new(void)
{
    return g_object_new(MY_TYPE_OBJECT, NULL);
}