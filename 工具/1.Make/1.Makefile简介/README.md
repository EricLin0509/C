# Makefile

## 简介

Make是一个工具，它可以根据文件之间的依赖关系，自动编译生成可执行文件

Makefile是一个文件，它包含了编译的规则，它告诉Make如何编译和链接程序

## 语法

```makefile
目标文件: 依赖文件
	命令
```

- 规则文件：要生成的文件
- 依赖文件 (可选)：生成规则文件所需要的文件
- 命令：生成规则文件所需要的命令

## 代码示例

### 配置一般规则

假设现在要编译 [main.c](main.c) 文件

```makefile
main: main
	gcc -o main main.c
```

执行 `make main` 命令

```bash
make main
gcc -o main main.c
```

此时会生成 `main` 可执行文件

### 配置依赖关系

假设现在要编译 [main.c](main.c) 文件并使用依赖文件 [test.c](test.c)

```makefile
main: main.c test.c
	gcc -o main main.c test.c
```

执行 `make main` 命令

```bash
make main
gcc -o main main.c test.c
```

### 配置多个规则

假设现在先编译 [test.c](test.c) 生成 `test.o` 中间文件作为依赖文件，再编译 [main.c](main.c) 生成 `main` 可执行文件

```makefile
main: main.c test.o
	gcc -o main main.c test.o

test.o: test.c
	gcc -c test.c -o test.o
```

执行 `make main` 命令

```bash
make main
gcc -c test.c -o test.o
gcc -o main main.c test.o
```

### 配置默认规则

使用 `all` 作为默认规则

```makefile
all: main

main: main.c test.o
	gcc -o main main.c

test.o: test.c
	gcc -c test.c -o test.o
```

此时可以直接执行 `make` 命令

```bash
make
gcc -c test.c -o test.o
gcc -o main main.c
```

### 清理

使用 `clean` 作为清理规则

```makefile
all: main

main: main.c test.o
	gcc -o main main.c

test.o: test.c
	gcc -c test.c -o test.o

clean:
	rm -f main test.o
```
执行 `make clean` 命令

```bash
make clean
rm -f main test.o
```
此时 `main` 和 `test.o` 文件都被删除了
