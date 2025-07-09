# 字符串

在 C语言中，字符串是以 `\0` 结尾的一段字符数组。字符串的长度是指字符串中包含的字符的个数，不包括结尾的 `\0`

```c
char str[6];

str[0] = 'H';
str[1] = 'e';
str[2] = 'l';
str[3] = 'l';
str[4] = 'o';
str[5] = '\0'; // 字符串结尾
```

## 只读字符串

```c
char *str = "Hello";
```

只读字符串是指字符串的值不能被修改的字符串。在编译时，编译器会把只读字符串的内容直接放到代码段中，而不会在运行时再去寻找这个字符串的值


## 将字符串存储在堆区

在 GTK4 中，可以使用 `g_new()` 函数来在堆区分配内存，并用 `g_free()` 函数来释放内存

```c
g_new (struct_type, n_struct)
```

- `struct_type` 是指你需要的数据类型，比如 `char`、`int`、`struct` 等
- `n_struct` 是指你需要的长度，长度是 `struct_type` x `n_struct` 的大小

```c
char *str = g_new (char, 6);
```

### 清理堆区分配的内存

使用 `g_free()` 函数来释放堆区分配的内存

```c
g_free (gpointer mem);
```

如果 `mem` 是一个 `NULL` 指针，`g_free()` 函数会直接返回，不会有任何作用