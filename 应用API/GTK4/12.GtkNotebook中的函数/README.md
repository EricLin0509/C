# GtkNotebook中的函数

GtkNotebook 容器在我们的文本编辑器示例中是非常重要的

现在，我们需要创建 `FileEditorNotebook.h` 作为 `FileEditor` 类中的公共函数

```c
// FileEditorNotebook.h

#ifndef FILE_EDITOR_NOTEBOOK_H
#define FILE_EDITOR_NOTEBOOK_H

void notebook_page_save(GtkNotebook *notebook);

void notebook_page_close (GtkNotebook *notebook);

void notebook_page_open (GtkNotebook *notebook);

void notebook_page_new_with_file (GtkNotebook *notebook, GFile *file);

void notebook_page_new (GtkNotebook *notebook);

#endif /* FILE_EDITOR_NOTEBOOK_H */
```

### `notebook_page_new`

`notebook_page_new` 函数用于创建一个新的空白页，并将其添加到 `GtkNotebook` 容器中

```c
static char *get_title() // 获取新页面的标题
{
    static int c = -1;
    if (++c == 0) return (g_strdup_printf("Untitled"));
    else return (g_strdup_printf ("Untitled %u", c));
}
```

- `g_strdup_printf` 函数用于创建新的标题

```c
static void notebook_page_build(GtkNotebook *notebook, GtkWidget *self, const char *filename) // 创建新页面
{
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    GtkNotebookPage *page;
    GtkWidget *label;
    int i;

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), self);
    label = gtk_label_new(filename);
    i = gtk_notebook_append_page(notebook, scrolled_window, label);
    page =gtk_notebook_get_page(notebook, scrolled_window);
    gtk_notebook_set_current_page(notebook, i);
    g_signal_connect(GTK_self(self), "change-file", G_CALLBACK(file_changed_cb), notebook);
}
```

- `gtk_scrolled_window_new` 函数用于创建 `GtkScrolledWindow` 容器
- `gtk_label_new` 函数用于创建 `GtkLabel` 标签
- `gtk_notebook_append_page` 函数用于将 `GtkScrolledWindow` 容器和 `GtkLabel` 标签添加到 `GtkNotebook` 容器中
- `gtk_notebook_get_page` 函数用于获取 `GtkNotebook` 容器中的 `GtkScrolledWindow` 容器
- `gtk_notebook_set_current_page` 函数用于设置当前页

```c
void notebook_page_new(GtkNotebook *notebook)
{
    g_return_if_fail(GTK_IS_NOTEBOOK(notebook));

    GtkWidget *self;
    char *filename;

    self = file_editor_new();
    filename = get_title();
    notebook_page_build(notebook, self, filename);
    g_free(filename);
}
```

- `file_editor_new` 函数用于创建 `FileEditor` 类
- `get_title` 函数用于获取新页面的标题
- `notebook_page_build` 函数用于创建新页面
- `g_free` 函数用于释放内存

### `notebook_page_new_with_file`

`notebook_page_new_with_file` 函数用于创建一个新的页面，并将其添加到 `GtkNotebook` 容器中，并打开指定的文件

```c
void notebook_page_new_with_file(GtkNotebook *notebook, GFile *file)
{
    g_return_if_fail(GTK_IS_NOTEBOOK(notebook));
    g_return_if_fail(G_IS_FILE(file));

    GtkWidget *self;
    char *filename;

    if ((self = file_editor_new_with_file(file)) == NULL) return; // 创建文件编辑器失败
    filename = g_file_get_basename(file);
    notebook_page_build(notebook, self, filename);
    g_free(filename);
}
```

- `g_file_get_basename` 函数用于获取文件名

### `notebook_page_open`

`notebook_page_open` 函数用于打开一个文件，并将其添加到 `GtkNotebook` 容器中

```c
static void open_response_cb(FileEditor *self, int response, GtkNotebook *notebook) // 用于 AsyncCallback 回调函数
{
    GFile *file;
    char *filename;

    if (response != RESPONSE_SUCCESS)
    {
        g_object_ref_sink(self);
        g_object_unref(self);
    }
    else
    {
        file = file_editor_get_file(self);
        filename = g_file_get_basename(file);
        g_object_unref(file);
        notebook_page_build(notebook, GTK_WIDGET(self), filename);
        g_free(filename);
    }
}
```

```c
void notebook_page_open(GtkNotebook *notebook)
{
    g_return_if_fail(GTK_IS_NOTEBOOK(notebook));

    GtkWidget *self;

    self = file_editor_new();
    g_signal_connect(self, "open-response", G_CALLBACK(open_response_cb), notebook);
    file_editor_open(FILE_EDITOR(self), GTK_WINDOW(gtk_widget_get_ancestor(GTK_WIDGET(notebook), GTK_TYPE_WINDOW)));
}
```

- `g_object_ref_sink` 函数如果 `response` 不是 `RESPONSE_SUCCESS`，那么需要销毁 `FileEditor` 类，因为它有浮动引用

### 浮动引用

对象在创建时可能会有一个“浮动引用”。浮动引用的作用是简化对象初始阶段的所有权管理，确保对象**在未被父容器接管时能正确释放**，而在**被接管后由父容器负责生命周期**。这意味着，当一个对象被添加到父容器时，父容器会通过 `g_object_ref_sink()` 将浮动引用转换为强引用，此时引用计数保持为 1，但所有权正式转移给父容器，开发者无需手动调用 `unref`

但是，有时我们需要在对象被销毁之前，保留对它的引用。这就需要使用 `g_object_ref_sink` 函数，将浮动引用变成正常的引用，通过向引用计数增加 1 来实现

#### 类比

假设你网购了一箱苹果 (对象) ，快递员 (GTK) 送来时：

1. 包裹默认是「未签收」状态 (浮动引用)
2. 你签收后包裹才真正属于你 (沉没引用)
3. 如果无人签收，包裹会被原路退回销毁 (警告)

#### 例子

```c
self->button = gtk_button_new_with_label("Click me"); // 创建时获得浮动引用
```

- ✨ 特性：此时对象像"悬浮"状态，没有明确的所有者
- ⚠️ 风险：如果未被正确接收，对象销毁时会触发警告

```c
g_object_ref_sink(self->button); // 将浮动引用转换为普通引用
```

- 🔒 作用：明确所有权关系 (签收快递)
- 📦 典型场景：当对象不会被添加到父容器时，需要手动沉没引用


如果添加到父类容器时，父类容器会自动调用 `g_object_ref_sink` 函数，将浮动引用转换为普通引用，此时引用计数保持为 1，但所有权正式转移给父容器，开发者无需手动调用 `unref`

```c
GtkWidget *button = gtk_button_new(); // 创建时获得浮动引用
gtk_container_add(GTK_CONTAINER(window), button); // 浮动引用被"沉淀"
// 此处不需要主动 unref，因为父容器会自动 unref
```

- 当 `button` 被添加到 `window` 容器时，使用了 `g_object_ref_sink` 函数，使得 `button` 获得了强引用，并转移了所有权

因此，浮动引用被转换为普通引用。也就是说，浮动引用被移除，普通引用计数为 1。因此，调用者无需减少 `button` 的引用计数

### `notebook_page_close`

`notebook_page_close` 函数用于关闭当前页，并将其从 `GtkNotebook` 容器中移除

```c
void notebook_page_close(GtkNotebook *notebook)
{
    g_return_if_fail(GTK_IS_NOTEBOOK(notebook));

    GtkWidget *window;
    int i;

    if (gtk_notebook_get_n_pages(notebook) == 1)
    {
        window = gtk_widget_get_ancestor(GTK_WIDGET(notebook), GTK_TYPE_WINDOW);
        gtk_window_destroy(GTK_WINDOW(window));
    }
    else
    {
        i = gtk_notebook_get_current_page(notebook);
        gtk_notebook_remove_page(GTK_NOTEBOOK(notebook), i);
    }
}
```

- `gtk_window_destroy` 函数用于销毁 `GtkWindow` 窗口

### `notebook_page_save`

`notebook_page_save` 函数用于保存当前页

```c
static void get_current_file_editor(GtkNotebook *notebook) // 获取当前页的文件编辑器
{
    int i;
    GtkWidget *self;
    GtkWidget *scrolled_window;

    i = gtk_notebook_get_current_page(notebook);
    scrolled_window = gtk_notebook_get_nth_page(notebook, i);
    self = gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scrolled_window));
    return FILE_EDITOR(self);
}
```

- `gtk_notebook_get_current_page` 函数用于获取当前页的索引

```c
void notebook_page_save(GtkNotebook *notebook)
{
    g_return_if_fail(GTK_IS_NOTEBOOK(notebook));

    FileEditor *self;

    self = get_current_file_editor(notebook);
    file_editor_save(self);
}
```

### `file_changed_cb` 处理函数

`file_changed_cb` 函数用于处理 `change-file` 信号，并更新 `GtkNotebook` 容器中的标题

```c
static void file_changed_cb(GtkWidget *self, GtkNotebook *notebook)
{
    GtkWidget *scrolled_window;
    GtkWidget *label;
    GFile *file;
    char *filename;

    file = file_editor_get_file(self);
    scrolled_window = gtk_widget_get_parent(GTK_WIDGET(self));
    if (G_IS_FILE(file))
    {
        filename = g_file_get_basename(file);
        g_object_unref(file);
    }
    else
    {
        filename = get_title();
    }
    label = gtk_label_new(filename);
    g_free(filename);
    gtk_notebook_set_tab_label(notebook, scrolled_window, label);
}
```