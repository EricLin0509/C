#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_TITLE "Hello World"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
} Game;

bool game_load_image(Game *game, const char *filename)
{
    game->background = IMG_LoadTexture(game->renderer, filename);
    if (game->background == NULL)
    {
        fprintf(stderr, "IMG_LoadTexture Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool game_init(Game *game)
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
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

    SDL_Surface *icon = IMG_Load("../images/icon.png");
    if (icon == NULL)
    {
        fprintf(stderr, "IMG_Load Error: %s\n", SDL_GetError());
        return false;
    }
    
    if (!SDL_SetWindowIcon(game->window, icon))
    {
        fprintf(stderr, "SDL_SetWindowIcon Error: %s\n", SDL_GetError());
        SDL_DestroySurface(icon);
        return false;
    }
    SDL_DestroySurface(icon);

    return true;
}

void game_quit(Game *game)
{
    SDL_DestroyTexture(game->background);
    game->background = NULL;
    SDL_DestroyRenderer(game->renderer);
    game->renderer = NULL;
    SDL_DestroyWindow(game->window);
    game->window = NULL;
    SDL_Quit();
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
                    if (event.key.scancode == SDL_SCANCODE_ESCAPE) // 按下 Esc 键退出游戏
                    {
                        printf("exiting...\n");
                        is_running = false;
                    }
                default:
                    break;
            }
        }

        SDL_RenderClear(game->renderer); // 清空渲染器内容
        SDL_RenderTexture(game->renderer, game->background, NULL, NULL);
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