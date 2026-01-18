# Linux 内核

此笔记将介绍如何开发 Linux 内核模块

## 准备工作

1. 安装 `linux-headers` 包，它包含了内核头文件，用于编译内核模块

Ubuntu/Debian:

```
sudo apt-get install linux-headers-$(uname -r)
```

CentOS/Fedora:

```
sudo yum install kernel-headers-$(uname -r)
```