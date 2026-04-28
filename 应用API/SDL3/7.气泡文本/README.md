# 气泡文本

## 代码

### 函数声明

```c
SDL_Surface* create_bubble_text(const char* text, float font_size, int radius, SDL_Color inner, SDL_Color outer);
```

- `text`：要显示的文本
- `font_size`：字体大小
- `radius`：气泡半径
- `inner`：内层颜色
- `outer`：外层颜色

### 打开字体

```c
SDL_Surface* create_bubble_text(const char* text, float font_size, int radius, SDL_Color inner, SDL_Color outer)
{
    TTF_Font* font = TTF_OpenFont("../fonts/Google-Sans-Regular.ttf", font_size);
    if (font == NULL)
    {
        fprintf(stderr, "Failed to load font: %s\n", SDL_GetError());
        return NULL;
    }
}
```

### 创建外层文本

```c
SDL_Surface* create_bubble_text(const char* text, float font_size, int radius, SDL_Color inner, SDL_Color outer)
{
    TTF_Font* font = TTF_OpenFont("../fonts/Google-Sans-Regular.ttf", font_size);
    if (font == NULL)
    {
        fprintf(stderr, "Failed to load font: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Surface *outer_text = TTF_RenderText_Blended(font, text, 0, outer); // 外层文本
    if (outer_text == NULL)
    {
        fprintf(stderr, "Outer text create failed: %s\n", SDL_GetError());
        return NULL;
    }
}
```

### 创建新的层

使用 `SDL_CreateSurface` 创建新的层

```c
SDL_Surface *SDL_CreateSurface(int width, int height, SDL_PixelFormat format);
```

- `width`：宽度
- `height`：高度
- `format`：格式
    - 有关 `SDL_PixelFormat` 的更多信息，请参阅 [SDL 文档](https://wiki.libsdl.org/SDL3/SDL_PixelFormat)

```c
SDL_Surface* create_bubble_text(const char* text, float font_size, int radius, SDL_Color inner, SDL_Color outer)
{
    TTF_Font* font = TTF_OpenFont("../fonts/Google-Sans-Regular.ttf", font_size);
    if (font == NULL)
    {
        fprintf(stderr, "Failed to load font: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Surface *outer_text = TTF_RenderText_Blended(font, text, 0, outer); // 外层文本
    if (outer_text == NULL)
    {
        fprintf(stderr, "Outer text create failed: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Surface *new_surface = SDL_CreateSurface(outer_text->w + radius * 2, outer_text->h + radius * 2, SDL_PIXELFORMAT_ARGB32); // 创建新的层
    if (new_surface == NULL)
    {
        fprintf(stderr, "New surface create failed: %s\n", SDL_GetError());
        SDL_DestroySurface(outer_text);
        return NULL;
    }
}
```

### 创建一个圆形层

首先我们需要一个画圆算法

这里我们使用极坐标三角函数算法

```c
// 极坐标三角函数算法
for (int i = 0; i < (2 * M_PI *radius); i++)
{
    double rad = (double) i / radius;
    // 加半径是为了使圆心在中心
    int x = (int) (cos(rad) * radius) + radius;
    int y = (int) (sin(rad) * radius) + radius;
}
```

我们使用 `SDL_BlitSurface` 将像素点依次绘制到新的层上

```c
bool SDL_BlitSurface(SDL_Surface *src, const SDL_Rect *srcrect, SDL_Surface *dst, const SDL_Rect *dstrect);
```

- `src`：源层
- `srcrect`：源矩形
- `dst`：目标层
- `dstrect`：目标矩形

```c
for (int i = 0; i < (2 * M_PI *radius); i++)
{
    double rad = (double) i / radius;
    // 加半径是为了使圆心在中心
    int x = (int) (cos(rad) * radius) + radius;
    int y = (int) (sin(rad) * radius) + radius;

    SDL_BlitSurface(outer_text, NULL, new_surface, &((SDL_Rect) {x, y, outer_text->w, outer_text->h}));
}
```

### 创建内层文本

```c
SDL_DestroySurface(outer_text); // 由于已经绘制到新的层上，所以不需要外层文本了
outer_text = NULL;
SDL_Surface *inner_text = TTF_RenderText_Blended(font, text, 0, inner); // 内层文本
TTF_CloseFont(font);
font = NULL;
if (inner_text == NULL)
{
    fprintf(stderr, "Inner text create failed: %s\n", SDL_GetError());
    SDL_DestroySurface(new_surface);
    return NULL;
}
SDL_BlitSurface(inner_text, NULL, new_surface, &((SDL_Rect) {radius, radius, inner_text->w, inner_text->h}));
SDL_DestroySurface(inner_text);
inner_text = NULL;
return new_surface;
```