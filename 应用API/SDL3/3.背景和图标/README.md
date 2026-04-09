# 背景和图标

此教程将介绍如何在 SDL3 中设置背景和图标

## 背景

### 加载背景图片

使用 `SDL_LoadTexture()` 函数加载背景图片，并将其作为窗口的背景

```c
SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, const char *file);
```

- `renderer`: 渲染器
- `file`: 背景图片文件路径

```c
#include <SDL3_image/SDL_image.h> // 需要包含 SDL_image.h

SDL_Texture *background = IMG_LoadTexture(renderer, "background.png");
```

### 渲染背景图片

使用 `SDL_RenderTexture()` 函数渲染背景图片

```c
bool SDL_RenderTexture(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_FRect *srcrect, const SDL_FRect *dstrect);
```

- `renderer`: 渲染器
- `texture` : SDL_Texture 指针
- `srcrect` : 源矩形
    - 原矩形指定了要渲染的部分，如果为 NULL，则渲染整个源图像
    - 设置成 `NULL` 则渲染整个源图像
- `dstrect` : 目标矩形
    - 目标矩形指定了要渲染到的位置，如果为 NULL，则渲染到整个窗口
    - 设置成 `NULL` 则渲染到整个窗口
- 有关 `SDL_FRect` 请参考 [SDL_FRect](https://wiki.libsdl.org/SDL3/SDL_FRect)

```c
SDL_RenderClear(renderer); // 先清空渲染器内容
SDL_RenderTexture(renderer, background, NULL, NULL); // 渲染背景图片
SDL_RenderPresent(renderer); // 刷新渲染器内容
```

### 销毁 `SDL_Texture` 对象

使用 `SDL_DestroyTexture()` 函数销毁 `SDL_Texture` 对象

```c
void SDL_DestroyTexture(SDL_Texture *texture);
```

- `texture`: `SDL_Texture` 对象

```c
SDL_DestroyTexture(background);
```

## 图标

### 加载图标

使用 `IMG_Load()` 函数加载图标

```c
SDL_Surface *IMG_Load(const char *file);
```

- `file`: 文件路径

```c
SDL_Surface *icon = IMG_Load("icon.png");
```

### 渲染图标

使用 `SDL_SetWindowIcon()` 函数渲染图标

```c
bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon);
```

- `window`: 窗口
- `icon`: `SDL_Surface` 对象

```c
SDL_SetWindowIcon(window, icon);
```

### 销毁 `SDL_Surface` 对象

需要使用 `SDL_DestroySurface()` 函数销毁 `SDL_Surface` 对象

```c
void SDL_DestroySurface(SDL_Surface *surface);
```

- `surface`: `SDL_Surface` 对象

```c
SDL_DestroySurface(icon);
```