# GtkApplication

## 简介

人们编写编程代码来开发应用程序。什么是应用程序？应用程序是使用库（例如操作系统、框架等）运行的软件。在 ​​GTK 4 编程中，GtkApplication 是使用 Gtk 库运行的程序 (或可执行文件)

最简单的 GtkApplication 程序如下

- 创建一个 GtkApplication 对象
- 运行 GtkApplication 对象

### 创建 GtkApplication 对象

使用 `gtk_application_new()` 函数创建 GtkApplication 对象

```c
GtkApplication *app; // 声明 GtkApplication 对象
app = gtk_application_new("org.example.myapp", G_APPLICATION_DEFAULT_FLAGS);
```

`gtk_application_new()` 函数有两个参数

- 应用程序的唯一标识符，通常以 `org.example.myapp` 形式
- 应用程序的标志
    - 如果没有任何参数，则使用 `G_APPLICATION_DEFAULT_FLAGS`
    - 如果需要设置其他标志，则参照 [GIO API 文档](https://docs.gtk.org/gio/flags.ApplicationFlags.html)

### 运行 GtkApplication 对象

使用 `g_application_run()` 函数运行 GtkApplication 对象

```c
g_application_run(G_APPLICATION(app), argc, argv);
```

- `G_APPLICATION()` 函数用于将 `GtkApplication` 对象转换为 `GApplication` 对象
- `argc` 和 `argv` 是程序的命令行参数

### 示例

```c
#include <gtk/gtk.h>

int main(int argc, char **argv) {
    GtkApplication *app; // 声明 GtkApplication 对象
    app = gtk_application_new("org.example.myapp", G_APPLICATION_FLAGS_NONE);
    
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    return status; // 返回应用程序的退出状态
}
```
#### 运行

使用 GCC 编译时，需要添加 `pkg-config --cflags --libs gtk4` 选项，并链接到 `gtk4` 库

```bash
gcc -o main main.c `pkg-config --cflags --libs gtk4`
```

运行程序

```bash
./main
(GtkApplication:12086): GLib-GIO-WARNING **: 13:29:41.454: Your application does not implement g_application_activate() and has no handlers connected to the 'activate' signal.  It should do one of these.
```

程序运行成功，但有一条警告信息，表示程序没有实现 `g_application_activate()` 函数，因此无法处理应用程序的激活信号

### 信号

上面的警告信息说明:

- 应用程序没有实现 `g_application_activate()` 函数
- 应用程序没有处理连接到 `activate` 信号的任何信号处理函数
- 需要处理至少一个上述问题

#### 类与继承

信号在类中定义，例如 `activate` 信号在 `GApplication` 类中定义

而 `GObject` 类是 `GApplication` 类的父类，因此 `GApplication` 类也继承了 `GObject` 类的所有属性和方法，同样 `GtkApplication` 类继承了 `GApplication` 类

```
GObject -- GApplication -- GtkApplication
<---parent                      --->child
```

#### g_signal_connect()

`g_signal_connect()` 函数用于连接信号和信号处理函数

首先我们需要一个信号处理函数

```c
static void activate(GApplication *application, gpointer user_data)
{
    g_print("activate signal received\n");
}
```

然后我们使用 `g_signal_connect()` 宏连接信号添加到 `g_application_run()` 函数前

```c
g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
g_application_run(G_APPLICATION(app), argc, argv);
```

`g_signal_connect()` 一共有四个参数

- 一个是信号的源对象，这里是 `GtkApplication` 对象
- 一个是信号的名称，这里是 `"activate"`
- 一个是信号处理函数的指针，这里是 `activate` 函数的指针 (需要强制转换为 `G_Callback` 类型)
- 一个是用户数据指针，这里是 `NULL` (即没有用户数据)

**注意：`g_signal_connect()` 是一个宏**

```c
#define g_signal_connect (
  instance,
  detailed_signal,
  c_handler,
  data
)
```

有多种信号类型，详情请参考 [GIO API 文档](https://docs.gtk.org/gio/signal.Application.activate.html)

现在程序运行时，会打印出 `activate signal received` 信息

```bash
./main
activate signal received
```