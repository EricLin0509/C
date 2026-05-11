# 端序

现在我们使用 x86_64 架构

假设我们有这两个数

```c
uint16_t a = 0x1234;
uint32_t b = 0x56789abc;

printf("a = %x\n", a); // 0x1234
printf("b = %x\n", b); // 0x56789abc
```

如果我们以每个字节为单位进行打印

```c
printf("a = %x %x\n", ((uint8_t *)&a)[0], ((uint8_t *)&a)[1]);
printf("b = %x %x %x %x\n", ((uint8_t *)&b)[0], ((uint8_t *)&b)[1], ((uint8_t *)&b)[2], ((uint8_t *)&b)[3]);
```

预期输出

```
a = 12 34
b = 56 78 9a bc
```

但实际输出却是

```
a = 34 12
b = bc 9a 78 56
```

这是因为该 CPU 采用小端序 (Little Endian) 存储数据。也就是说，低位字节排在前面，高位字节排在后面

## 引出问题

有些时候，我们通过 C 语言中的 Network Socket 收到的数据，是以大端序排列的。也就是说，高位字节排在前面，低位字节排在后面

如果以小端序处理这些数据，就会导致数据错误

## 解决方案

我们使用 `arpa/inet.h` 中的 `htonl()` 和 `htons()` 函数，将大端序的网络字节序转换为小端序的主机字节序

```c
#include <arpa/inet.h>

uint16_t a = 0x1234;
uint32_t b = 0x56789abc;

printf("a = %x\n", a); // 0x1234
printf("b = %x\n", b); // 0x56789abc

a = htons(a);
b = htonl(b);

printf("a = %x\n", a); // 0x3412
printf("b = %x\n", b); // 0xbc9a7856
```