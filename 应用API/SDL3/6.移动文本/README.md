# 移动文本

## 移动文本

在[上个章节](../5.文本创建/README.md)中，在渲染文本时使用了 `dstrect` 参数，它指定了文本的大小 (设置了 `w` 和 `h` 成员)

如果我们想移动文本，只需要在游戏主循环中修改 `dstrect` 的 `x` 和 `y` 成员即可

```c
text_rect.x += 10;
text_rect.y += 10;
```

这样，文本就会向右下方移动 10 像素

但是，这样做会导致文本一直向右下角移动，最终溢出窗口边界

## 限制移动范围

为解决此问题，我们可以设置碰撞检测，使得文本只能移动到窗口内

```c
float x_vel = 3; // x坐标的速度
float y_vel = 3; // y坐标的速度
...

text_rect.x += x_vel;
text_rect.y += y_vel;

if (text_rect.x + text_rect.w > WINDOW_WIDTH ||
    text_rect.x < 0) // 当 x 坐标超出窗口边界时
    x_vel *= -1; // 反方向移动

if (text_rect.y + text_rect.h > WINDOW_HEIGHT ||
    text_rect.y < 0) // 当 y 坐标超出窗口边界时
    y_vel *= -1; // 反方向移动
```