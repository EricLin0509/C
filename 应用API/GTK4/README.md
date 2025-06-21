# GTK4

## 简介
GTK 4 是 GNOME 项目的第四个主要版本，基于 GTK 3 开发，主要目标是提升性能、改进用户体验、增加新功能

### 核心特性

1. **高性能渲染**
   - 采用全新的渲染引擎，支持 Vulkan/OpenGL 硬件加速（默认使用 OpenGL）
   - 引入 `GskRenderer` 实现更高效的图形合成
   - 弃用传统绘图 API（如 `gdk_draw()`），转向基于节点树的渲染管线

2. **事件处理革新**
   - 使用 `GtkEventController` 体系替代旧有信号机制
   - 支持手势识别（缩放、旋转、拖拽等）

3. **布局系统升级**
   - 强化 `GtkLayoutManager` 系统，支持动态自适应布局
   - 弃用 `GtkBox`/`GtkGrid` 传统容器，推荐使用 `GtkBoxLayout`

4. **平台集成优化**
   - 改进 Wayland/X11/macOS/Windows 后端支持
   - 原生支持 HiDPI 显示和系统级暗色模式

---

### 跨平台支持
- **Linux**：深度集成 GNOME 桌面环境
- **Windows**：支持 Win32 和 UWP 应用
- **macOS**：提供原生 Aqua 主题支持
- **BSD**：通过 X11/Wayland 兼容

---

### 开发语言支持
| 语言       | 绑定状态     | 典型应用场景      |
|:-----------:|:-------------:|:------------------:|
| C          | 原生支持     | 核心库开发        |
| Python     | PyGObject    | 快速原型开发      |
| Rust       | gtk-rs       | 高性能应用        |
| JavaScript | GJS          | GNOME Shell 扩展  |
