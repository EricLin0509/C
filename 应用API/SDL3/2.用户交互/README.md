# 用户交互

在[上个教程](../1.创建窗口/README.md)中，我们成功创建了一个窗口，但无法交互

所以本次教程将介绍如何设计循环并处理用户输入

## 代码

```c
void game_run(SDL_Window *window, SDL_Renderer *renderer)
{
    while (true) // 游戏主循环
    {

    }
}
```

### 获取 Poll 事件

Poll 事件是一种非阻塞的事件获取方式，它会检查是否有事件发生

有则立即返回，没有则会等待直到有事件发生

使用 `SDL_PollEvent()` 函数可以获取 Poll 事件

```c
bool SDL_PollEvent(SDL_Event *event);
```

- 返回 `true` 则表示有事件发生，`false` 则表示没有事件发生
- `event` 是一个指针，用于保存事件信息，可以为 `NULL`
    - 详情请查看[Wiki](https://wiki.libsdl.org/SDL2/SDL_Event)

```c
void game_run(SDL_Window *window, SDL_Renderer *renderer)
{
    bool is_running = true; // 游戏是否正在运行

    while (is_running) // 游戏主循环
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) // 获取 Poll 事件
        {
            
        }
    }
}
```

### 处理事件

当有事件发生时，我们需要对事件进行处理

使用 `SDL_Event` 中的 `type` 字段来判断事件类型

```c
SDL_Event event;
while (SDL_PollEvent(&event)) // 获取 Poll 事件
{
    switch (event.type)
    {
        case SDL_EVENT_QUIT: // 退出事件
            printf("exiting...\n");
            is_running = false;
            break;
        default:
            break;
    }
}
```

现在，当用户点击关闭窗口按钮时，游戏会退出

- 有关 `type` 字段 (`SDL_EventType`) 的详细信息，请查看[Wiki](https://wiki.libsdl.org/SDL3/SDL_EventType)

### 获取键盘输入事件

使用 `SDL_EVENT_KEY_DOWN` 事件获取键盘输入事件

```c
SDL_Event event;
while (SDL_PollEvent(&event)) // 获取 Poll 事件
{
    switch (event.type)
    {
        case SDL_EVENT_QUIT: // 退出事件
            printf("exiting...\n");
            is_running = false;
            break;
        case SDL_EVENT_KEY_DOWN: // 键盘输入事件
            break;
        default:
            break;
    }
}
```

现在，我们可以获取键盘输入事件，并对其进行处理

### 处理键盘输入事件

使用 `SDL_Event` 中的 `key` 字段处理键盘输入事件

```c
if (event.key.scancode == SDL_SCANCODE_ESCAPE) // 按下 Esc 键退出游戏
{
    printf("exiting...\n");
    is_running = false;
}
```
- 有关 `key` 字段 (`SDL_KeyboardEvent`) 的详细信息，请查看[Wiki](https://wiki.libsdl.org/SDL3/SDL_KeyboardEvent)
- 有关 `scancode` 字段 (`SDL_Scancode`) 的详细信息，请查看[Wiki](https://wiki.libsdl.org/SDL3/SDL_Scancode)