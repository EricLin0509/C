#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_TITLE "Hello World"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define FONT_SIZE 80
#define COLOR_WHITE (SDL_Color){255, 255, 255, 255}
#define COLOR_LIGHT_BLUE (SDL_Color){173, 216, 230, 255}
#define VEL 3

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
    SDL_FRect text_rect;
    SDL_Texture *text_texture;
    float x_vel;
    float y_vel;
} Game;

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

    // 极坐标三角函数算法
    for (int i = 0; i < (2 * M_PI *radius); i++)
    {
        double rad = (double) i / radius;
        int x = (int) (cos(rad) * radius) + radius;
        int y = (int) (sin(rad) * radius) + radius;

        SDL_BlitSurface(outer_text, NULL, new_surface, &((SDL_Rect) {x, y, outer_text->w, outer_text->h}));
    }

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
}

bool game_load_image(Game *game, const char *filename)
{
    game->background = IMG_LoadTexture(game->renderer, filename);
    if (game->background == NULL)
    {
        fprintf(stderr, "IMG_LoadTexture Error: %s\n", SDL_GetError());
        return false;
    }

    TTF_Font *font = TTF_OpenFont("../fonts/Google-Sans-Regular.ttf", FONT_SIZE);
    if (font == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_Surface *text_surface = create_bubble_text("SDL3", FONT_SIZE, 8, COLOR_WHITE, COLOR_LIGHT_BLUE);
    if (text_surface == NULL)
    {
        fprintf(stderr, "TTF_RenderText_Blended Error: %s\n", SDL_GetError());
        return false;
    }

    game->text_rect.w = (float)text_surface->w;
    game->text_rect.h = (float)text_surface->h;

    game->text_texture = SDL_CreateTextureFromSurface(game->renderer, text_surface);

    SDL_DestroySurface(text_surface);
    text_surface = NULL;

    if (game->text_texture == NULL)
    {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool game_init(Game *game)
{
    srand(time(NULL));

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    if (!TTF_Init())
    {
        fprintf(stderr, "TTF_Init Error: %s\n", SDL_GetError());
        return false;
    }

    game->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (game->window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return false;
    }

    game->renderer = SDL_CreateRenderer(game->window, NULL);
    if (game->renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return false;
    }
    
    if (!game_load_image(game, "../images/background.png"))
        return false;

    game->x_vel = VEL;
    game->y_vel = VEL;

    return true;
}

void game_quit(Game *game)
{
    SDL_DestroyTexture(game->background);
    game->background = NULL;
    SDL_DestroyTexture(game->text_texture);
    game->text_texture = NULL;
    SDL_DestroyRenderer(game->renderer);
    game->renderer = NULL;
    SDL_DestroyWindow(game->window);
    game->window = NULL;
    TTF_Quit();
    SDL_Quit();
}

bool render_set_random_color(Game *game)
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    return SDL_SetRenderDrawColor(game->renderer, r, g, b, 255);
}

void move_text(Game *game)
{
    game->text_rect.x += game->x_vel;
    game->text_rect.y += game->y_vel;

    if (game->text_rect.x + game->text_rect.w > WINDOW_WIDTH ||
        game->text_rect.x < 0)
        game->x_vel *= -1;

    if (game->text_rect.y + game->text_rect.h > WINDOW_HEIGHT ||
        game->text_rect.y < 0)
        game->y_vel *= -1;
}

void game_run(Game *game)
{
    bool is_running = true;

    while (is_running) // 游戏主循环
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) // 获取 Poll 事件
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT: // 退出事件
                    printf("exiting...\n");
                    is_running = false;
                    break;
                case SDL_EVENT_KEY_DOWN: // 按键事件
                    switch (event.key.scancode)
                    {
                        case SDL_SCANCODE_ESCAPE: // 按下 ESC 退出
                            printf("exiting...\n");
                            is_running = false;
                            break;
                        case SDL_SCANCODE_SPACE: // 按下空格切换随机颜色
                            is_running =  render_set_random_color(game);
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        SDL_RenderClear(game->renderer); // 清空渲染器内容

        SDL_RenderTexture(game->renderer, game->background, NULL, NULL);
        SDL_RenderTexture(game->renderer, game->text_texture ,NULL, &game->text_rect);
        move_text(game);

        SDL_RenderPresent(game->renderer); // 显示渲染器内容

        SDL_Delay(16); // 60 FPS
    }
}

int main(void) {
    Game game = {0};
    if (!game_init(&game))
    {
        game_quit(&game);
        return 1;
    }
    
    game_run(&game);

    game_quit(&game);

    return 0;
}