#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_TITLE "Hello World"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define FONT_SIZE 80

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
    TTF_Font *font;
    SDL_FRect text_rect;
    SDL_Texture *text_texture;
} Game;

bool game_load_image(Game *game, const char *filename)
{
    game->background = IMG_LoadTexture(game->renderer, filename);
    if (game->background == NULL)
    {
        fprintf(stderr, "IMG_LoadTexture Error: %s\n", SDL_GetError());
        return false;
    }

    game->font = TTF_OpenFont("../fonts/Google-Sans-Regular.ttf", FONT_SIZE);
    if (game->font == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_Surface *text_surface = TTF_RenderText_Blended(game->font, "SDL3", 0, (SDL_Color){255, 255, 255, 255});
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

    return true;
}

void game_quit(Game *game)
{
    TTF_CloseFont(game->font);
    game->font = NULL;
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