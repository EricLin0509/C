# 背景颜色

## 设置背景颜色

使用 `SDL_SetRenderDrawColor()` 函数设置背景颜色

```c
bool SDL_SetRenderDrawColor(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
```

- `renderer`：渲染器
- `r`：红色分量（0-255）
- `g`：绿色分量（0-255）
- `b`：蓝色分量（0-255）
- `a`：透明度（0-255）

使用 `srand()` 函数设置随机种子，使用 `rand()` 函数生成随机数，然后将随机数映射到 0-255 范围内，作为颜色分量。

```c
srand(time(NULL));

int r = rand() % 256; // 0-255
int g = rand() % 256;
int b = rand() % 256;
SDL_SetRenderDrawColor(renderer, r, g, b, 255);
```

## 当用户按下空格键时设置随机颜色

在 `SDL_EVENT_KEY_DOWN` 事件中，检查按键是否为空格键，如果是，则设置随机颜色

```c
switch (event.key.scancode) // 按键扫描码
{
    case SDL_SCANCODE_SPACE:
        int r = rand() % 256; // 0-255
        int g = rand() % 256;
        int b = rand() % 256;
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        break;
}
```