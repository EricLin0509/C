# 自动变量

## 定义

在 Makefile 中，自动变量是由 Makefile 中的规则自动生成的变量。它们通常用于表示当前规则的目标文件、依赖文件、命令等信息

## 代码示例

### 目标文件

可以使用 `$@` 来表示当前规则的目标文件名称

```makefile
CC = gcc

all: main

main: main.c
	$(CC) -o $@ main.c
```

### 依赖文件

可以使用 `$^` 来表示当前规则的所有依赖文件名称
```makefile
CC = gcc

all: main

main: main.c test.c
	$(CC) -o $@ $^
```

### 通配符

通配符**用于表示文件名的一部分**，例如 `%.c` 表示所有以 `.c` 结尾的文件名

```makefile
CC = gcc

all: main

%: %.c
	$(CC) -o $@ $^
```