#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL"); // 许可证 (有 GPL, MIT, BSD 等)
MODULE_AUTHOR("Author Name"); // 作者
MODULE_DESCRIPTION("This is a simple hello world module"); // 描述
MODULE_VERSION("0.1"); // 版本

static int hello_init(void) {
    printk("Hello world from Linux kernel!\n");
    return 0;
}

static void hello_exit(void) {
    printk("Goodbye world from Linux kernel!\n");
}

module_init(hello_init);
module_exit(hello_exit);