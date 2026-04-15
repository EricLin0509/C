# 文本创建

## 初始化 ttf 字体库

使用 `TTF_Init()` 函数初始化 ttf 字体库

```c
bool TTF_Init(void);
```

- 返回值：初始化成功返回 `true`，失败返回 `false`
    - 失败时使用 `SDL_GetError()` 获取错误信息

```c
#include <SDL3_ttf/SDL_ttf.h> // 包含头文件

TTF_Init(); // 初始化 ttf 字体库
```

## 加载字体

使用 `TTF_OpenFont()` 函数加载字体

```c
TTF_Font* TTF_OpenFont(const char* file, int ptsize);
```

- `file`：字体文件路径
- `ptsize`：字体大小 (以磅为单位)
- 返回值：成功返回字体对象，失败返回 `NULL`

```c
TTF_Font* font = TTF_OpenFont("path/to/font.ttf", 16); // 加载字体
```

## 加载文本

使用 `TTF_RenderText` 系列函数加载文本

这里使用 `TTF_RenderText_Blended()` 函数加载文本

```c
SDL_Surface * TTF_RenderText_Blended(TTF_Font *font, const char *text, size_t length, SDL_Color fg);
```

- `font`：字体对象
- `text`：要渲染的文本
- `length`：文本长度，0 表示自动计算长度
- `fg`：字体颜色
    - `SDL_Color` 结构体，包含红色、绿色、蓝色和 alpha 通道值
- 返回值：成功返回一个层，失败返回 `NULL`

```c
SDL_Surface *text_surface = TTF_RenderText_Blended(font, "Hello, world!", 0, (SDL_Color){255, 255, 255, 255}); // 加载文本
```

## 转换成 `SDL_Texture`

使用 `SDL_CreateTextureFromSurface()` 函数将 `SDL_Surface` 转换成 `SDL_Texture`

```c
SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
```

- `renderer`：渲染器对象
- `surface`：`SDL_Surface` 对象
- 返回值：成功返回 `SDL_Texture` 对象，失败返回 `NULL`

```c
SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surface); // 转换成 SDL_Texture
TTF_DestroyTexture(text_surface); // 转换完成后即可销毁 SDL_Surface
```

## 绘制文本

使用 `SDL_RenderTexture()` 函数绘制文本

```c
SDL_RenderTexture(renderer, texture, NULL, NULL);
```

## 卸载字体

使用 `TTF_CloseFont()` 函数卸载字体

```c
void TTF_CloseFont(TTF_Font* font);
```

- `font`：字体对象

```c
TTF_CloseFont(font); // 卸载字体
```

## 退出 ttf 字体库

使用 `TTF_Quit()` 函数退出 ttf 字体库，用于最后的清理工作

```c
void TTF_Quit(void);
```
