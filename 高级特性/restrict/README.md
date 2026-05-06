# Restrict 关键字

在 C 语言中，restrict 关键字**用来修饰指针**

用于特指该指针仅用于访问特定内存区域，不能用于其他内存区域的访问

## 代码

### 不使用 Restrict

```c
void update_ptr(size_t *ptr1, size_t *ptr2, size_t *val)
{
    *ptr1 += *val;
    *ptr2 += *val;
}
```

生成的 x86_64 汇编代码如下：

```asm
"update_ptr":
        mov     rax, QWORD PTR [rdx]
        add     QWORD PTR [rdi], rax
        mov     rax, QWORD PTR [rdx]
        add     QWORD PTR [rsi], rax
        ret
```

- `rdx`: `val` 指针
- `rdi`: `ptr1` 指针
- `rsi`: `ptr2` 指针
- `rax`: 临时变量，用于存储 `val` 指针解引用后的值

可以看到，由于编译器不知道 `val` 指针在函数调用期间是否相同，因此会执行两次 `mov` (移动) 指令重载临时变量

### 使用 Restrict

```c
void update_ptr_restrict(size_t *restrict ptr1, size_t *restrict ptr2, size_t *restrict val)
{
    *ptr1 += *val;
    *ptr2 += *val;
}
```

生成的 x86_64 汇编代码如下：

```asm
"update_ptr_restrict":
        mov     rax, QWORD PTR [rdx]
        add     QWORD PTR [rdi], rax
        add     QWORD PTR [rsi], rax
        ret
```

由于加入了 `restrict` 关键字，编译器知道 `val` 指针在函数调用期间不会发生变化，因此可以直接使用 `rdi`、`rsi`、`rdx` 指针进行操作，避免了重复的 `mov` 指令