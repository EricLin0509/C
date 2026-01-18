# Hello World

此教程将介绍开发你的第一个Linux内核模块

## 代码

### 引入头文件

这里需要引入头文件`linux/init.h`和`linux/module.h`

```c
#include <linux/init.h>
#include <linux/module.h>
```

### 定义模块信息

这里需要定义模块的一些信息如下

- License: 许可证 (**必须包含此信息**，否则无法编译)
- Author: 作者 (可选)
- Description: 描述 (可选)
- Version: 版本 (可选)

```c
MODULE_LICENSE("GPL"); // 许可证 (有 GPL, MIT, BSD 等)
MODULE_AUTHOR("Author Name"); // 作者
MODULE_DESCRIPTION("This is a simple hello world module"); // 描述
MODULE_VERSION("0.1"); // 版本
```

### 定义模块入口函数

入口函数类似于Java中的构造函数，是在加载该模块时**第一个**被调用的函数，用于注入模块到内核中

它的函数原型为如下

```c
static int init_module(void)
```

- 返回值：0表示初始化成功，非0表示初始化失败

这里定义模块的入口函数`hello_init`

```c
static int hello_init(void) {
    printk("Hello world from Linux kernel!\n");
    return 0;
}
```

- `printk`函数用于打印输出到内核日志

### 定义模块出口函数

出口函数是在卸载该模块时最后一个被调用的函数，用于清理模块的资源

它的函数原型为如下

```c
static void exit_module(void)
```

这里定义模块的出口函数`hello_exit`

```c
static void hello_exit(void) {
    printk("Goodbye world from Linux kernel!\n");
}
```

### 注册模块入口和出口函数

需要使用 `module_init` 和 `module_exit` 宏来注册模块的入口和出口函数

```c
module_init(hello_init);
module_exit(hello_exit);
```

- 这两个宏会将 `hello_init` 和 `hello_exit` 函数符号导出，以便内核可以调用它们

### 编写 [Makefile](../../工具/Make/Makefile简介/README.md)

Linux内核模块的编译和链接有自己的一套流程，需要编写Makefile文件来描述编译和链接过程

这里编写一个简单的Makefile文件如下

```makefile
obj-m := hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

- `obj-m`：指定要编译的模块名称
- **注意**：文件目录不能有空格，否则编译时会报错

使用 `make` 命令编译模块

此时可以看到一个 `hello.ko` 文件，此为内核模块文件

### 加载模块

使用 `insmod` 命令加载模块

```bash
sudo insmod hello.ko
```

此时可以使用 `dmesg` 命令查看内核日志，可以看到如下输出

```bash
sudo dmesg
[  202.478806] Hello world from Linux kernel!
```

### 卸载模块

使用 `rmmod` 命令卸载模块

```bash
sudo rmmod hello
```

此时可以使用 `dmesg` 命令查看内核日志，可以看到如下输出

```bash
sudo dmesg
[  231.854530] Goodbye world from Linux kernel!
```
