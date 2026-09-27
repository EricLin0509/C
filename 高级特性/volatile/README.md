# Volatile

## 简介

在C语言中，`volatile` 关键字告诉编译器：**该变量的值可能在程序控制流之外被改变**，因此编译器不得对其进行优化（如缓存到寄存器、省略读写操作等），每次访问该变量时都必须从内存中重新读取其值。

编译器在开启优化（如 GCC 的 `-O2`、`-O3`）时，会假设变量只会在当前代码的控制流中被修改，从而将变量的值缓存到寄存器中。`volatile` 正是为了打破这一假设而存在的。

## 代码示例

假设有一个全局变量 `flag`，一个线程将其置为 `true`，另一个线程循环等待它变为 `true`：

```c
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

bool flag = false;

void *func(void *args)
{
    sleep(1);
    flag = true;
    return NULL;
}

int main(int argc, const char *argv[])
{
    pthread_t thread;
    pthread_create(&thread, NULL, func, NULL);

    printf("Waiting for flag to be set...\n");

    while (!flag) {}
    printf("Flag is set!\n");

    pthread_join(thread, NULL);
    return 0;
}
```

### 不开启优化：正常运行

```bash
gcc -o Thread Thread.c -lpthread
./Thread
Waiting for flag to be set...
Flag is set!
```

### 开启 `-O2` 优化：程序卡死

```bash
gcc -O2 -o Thread Thread.c -lpthread
./Thread
Waiting for flag to be set...
# 程序卡在 while(!flag)，永远不会退出
```

**原因**：编译器发现 `main` 函数中没有代码修改 `flag`，于是将 `while(!flag)` 优化为 `while(true)`，直接把 `flag` 的值缓存到寄存器中，不再从内存读取。

### 解决方案：使用 `volatile`

```c
volatile bool flag = false;
```

声明为 `volatile` 后，编译器每次循环都会从内存重新读取 `flag` 的值：

```bash
gcc -O2 -o Thread Thread.c -lpthread
./Thread
Waiting for flag to be set...
Flag is set!
```

## 指针与 volatile

`volatile` 与指针结合时，位置决定了修饰的对象：

| 声明 | 指针本身 | 指向的变量 |
|------|---------|-----------|
| `volatile int *p` | 非 volatile | **volatile** |
| `int *volatile p` | **volatile** | 非 volatile |
| `volatile int *volatile p` | **volatile** | **volatile** |

### 记忆方法 —— 顺时针螺旋法则 (Clockwise/Spiral Rule)

从变量名出发，按**顺时针**螺旋向外读取声明：

1. 从变量名开始，**向右**读（遇到 `()` 为函数，`[]` 为数组）
2. **向左**读（遇到 `*` 为指针，`const`/`volatile` 为限定符）
3. 继续螺旋向外，直到解析完所有修饰符

以 `volatile int *p` 为例：

```
       volatile int
                  |
     +--------+---+
     |        |
     |    * ← p
     |        |
     +--------+
```

- 从 `p` 出发 → 向右无内容 → 向左遇到 `*` → **p 是指针** → 继续向左遇到 `int` → **指向 int** → 遇到 `volatile` → **volatile int**
- 结果：**p 是指向 volatile int 的指针**

以 `int *volatile p` 为例：

- 从 `p` 出发 → 向右无内容 → 向左遇到 `volatile` → **p 是 volatile 的** → 继续向左遇到 `*` → **指针** → 遇到 `int` → **指向 int**
- 结果：**p 是 volatile 指针，指向 int**

## 典型应用场景

| 场景 | 说明 |
|------|------|
| **多线程共享变量** | 变量可能被其他线程修改，防止编译器缓存到寄存器 |
| **内存映射 I/O** | 硬件寄存器的值可能随时被外设改变，每次读写都必须访问实际地址 |
| **信号处理函数** | 信号处理器中修改的变量必须声明为 `volatile`，因为主程序无法预知信号何时到达 |
| **`setjmp`/`longjmp`** | 调用 `longjmp` 后，非 `volatile` 局部变量的值是不确定的 |

## 常见误区

> ⚠️ **`volatile` 不等于原子操作，也不保证线程安全**

- `volatile` 只禁止编译器优化，**不提供内存屏障（memory barrier）**，也不保证读写的原子性
- 在多线程中，`volatile` 可以确保变量不被缓存，但**不能替代互斥锁（mutex）或原子操作（`_Atomic`）**
- 例如 `volatile int counter` 执行 `counter++` 仍然是读-改-写三步操作，可能出现竞态条件（race condition）
- 如需线程安全的原子操作，应使用 C11 的 `_Atomic` 或平台的原子 API
