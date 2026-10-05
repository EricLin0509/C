# 端序 (Endianness)

本文基于 x86_64 架构 (小端序)

## 什么是端序

端序指的是多字节数据在内存中的**字节排列顺序**：

| 端序 | 说明 | 典型架构 |
|------|------|----------|
| **大端序** (Big Endian) | 高位字节在前，低位字节在后 (符合人类阅读习惯) | 网络字节序、SPARC |
| **小端序** (Little Endian) | 低位字节在前，高位字节在后 | x86/x86_64、ARM (默认) |

## 观察小端序存储

假设有如下变量：

```c
uint16_t a = 0x1234;
uint32_t b = 0x56789abc;
```

以字节为单位逐个打印：

```c
printf("a = %x %x\n", ((uint8_t *)&a)[0], ((uint8_t *)&a)[1]);
printf("b = %x %x %x %x\n", ((uint8_t *)&b)[0], ((uint8_t *)&b)[1], ((uint8_t *)&b)[2], ((uint8_t *)&b)[3]);
```

直觉上我们可能期望输出：

```
a = 12 34
b = 56 78 9a bc
```

但实际输出却是：

```
a = 34 12
b = bc 9a 78 56
```

内存布局如下：

```
变量 a = 0x1234 (占 2 字节)：

  地址：    base    base+1
  大端序：   12      34
  小端序：   34      12    ← x86_64 实际存储

变量 b = 0x56789abc (占 4 字节)：

  地址：    base    base+1  base+2  base+3
  大端序：   56      78      9a      bc
  小端序：   bc      9a      78      56    ← x86_64 实际存储
```

## 问题：网络字节序与主机字节序不一致

网络协议 (如 TCP/IP) 规定使用**大端序**传输数据，而 x86_64 主机使用**小端序**存储数据。

如果直接将网络收到的字节流当作主机整数来解读，就会得到错误的结果。

## 解决方案：字节序转换函数

`<arpa/inet.h>` 提供了四个转换函数：

| 函数 | 全称 | 作用 |
|------|------|------|
| `htons()` | **h**ost **to** **n**etwork **s**hort | 主机 → 网络 (16 位) |
| `htonl()` | **h**ost **to** **n**etwork **l**ong | 主机 → 网络 (32 位) |
| `ntohs()` | **n**etwork **to** **h**ost **s**hort | 网络 → 主机 (16 位) |
| `ntohl()` | **n**etwork **to** **h**ost **l**ong | 网络 → 主机 (32 位) |

> 在大端序主机上，这些函数为空操作 (no-op)；在小端序主机上，它们执行字节反转。因此**始终使用这些函数**可以保证代码的可移植性。

### 示例

```c
#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    uint16_t a = 0x1234;
    uint32_t b = 0x56789abc;

    printf("原始值：a = %x, b = %x\n", a, b);

    a = htons(a);
    b = htonl(b);

    printf("转换后：a = %x, b = %x\n", a, b);

    return 0;
}
```

输出：

```
原始值：a = 1234, b = 56789abc
转换后：a = 3412, b = bc9a7856
```

### 典型使用场景

```c
uint16_t port = 8080;
uint32_t addr = 0xc0a80001;

struct sockaddr_in sa;
sa.sin_port = htons(port);
sa.sin_addr.s_addr = htonl(addr);
```
