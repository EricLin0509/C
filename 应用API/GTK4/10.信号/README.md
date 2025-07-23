# 信号

我们需要一种方式可以使得两个对象之间可以通信，但是使用全局变量会使得程序难以维护，我们有两种方式可以实现对象之间的通信：

- 实例方法：例如 `gtk_text_view_get_buffer()` 函数可以获取 `GtkTextView` 对象的 `GtkTextBuffer` 实例
- 信号：例如 `activate` 信号可以让 `GtkApplication` 对象知道用户打开了此程序

方法或信号的调用者通常不在对象内部。两者的区别之一是对象是主动还是被动。在方法中，对象被动地响应调用者。在信号中，对象主动地向处理程序发送信号


GObject 的信号分为以下几步：

1. 注册信号 (signal registration)：通常在 `class_init()` 完成注册。信号可以拥有默认的信号处理程序，也可以由程序员自己编写

2. 连接信号 (signal connection)：在对象创建后，使用 `g_signal_connect()` 连接信号和处理程序。信号连接后，处理程序将在对象发生相应事件时被调用

3. 发射信号 (signal emission)：使用 `g_signal_emit()` 发射信号。发射信号后，信号处理程序将被调用

## 注册信号

在我们的文本编辑器示例中，要两种信号：

- `change-file` 信号：当 GFile 指针发生变化时发射
- `open-response` 信号：当用户打开文件时发射

我们可以使用枚举或数组来存储这些信号的 ID

```c
enum {
    CHANGE_FILE
    OPEN_RESPONSE
    2 // 表示信号的数量
};

static guint signals[2];
```

然后在 `class_init()` 中注册信号：

```c
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
    1 // 信号参数数量
    G_TYPE_INT // 信号参数类型
    );
}
```

有关 `g_signal_new()` 的详细用法，请参考 [GObject API 文档](https://docs.gtk.org/gobject/func.signal_new_class_handler.html)

它们的处理函数定义如下：

```c
void change_file_handler(FileEditor *self, gpointer user_data);

void open_response_handler(FileEditor *self, ResponseType response, gpointer user_data);
```

- `ResponseType` 是一个枚举类型，用于表示用户的响应类型

```c
enum ResponseType {
    RESPONSE_SUCCESS,
    RESPONSE_CANCEL,
    RESPONSE_ERROR
};
```

- `RESPONSE_SUCCESS` 表示用户成功打开文件
- `RESPONSE_CANCEL` 表示用户取消了打开文件
- `RESPONSE_ERROR` 表示打开文件时发生错误

## 连接信号

信号和信号处理程序的连接是通过 `g_signal_connect()` 函数完成的。也有其他类似的函数，例如 `g_signal_connect_after()` 和 `g_signal_connect_swapped()`。

```c
g_signal_connect(self, "change-file", G_CALLBACK(change_file_handler), NULL);
g_signal_connect(self, "open-response", G_CALLBACK(open_response_handler), NULL);
```

## 发射信号

信号的发射是通过 `g_signal_emit()` 函数完成的

```c
g_signal_emit(self, signals[CHANGE_FILE], 0);
g_signal_emit(self, signals[OPEN_RESPONSE], 0, RESPONSE_SUCCESS);
g_signal_emit(self, signals[OPEN_RESPONSE], 0, RESPONSE_CANCEL);
g_signal_emit(self, signals[OPEN_RESPONSE], 0, RESPONSE_ERROR);
```

- `self`： 发射信号的对象
- `signals[CHANGE_FILE]`： 信号 ID
- `0`： 信号的详细信息
- 由于 `change-file` 信号没有参数，所以没有第四个参数
- `RESPONSE_SUCCESS`、`RESPONSE_CANCEL`、`RESPONSE_ERROR`： 信号参数