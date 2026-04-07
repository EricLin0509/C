#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_TITLE "Hello World"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(void) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) // 初始化SDL
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError()); // SDL_GetError()获取错误信息
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Delay(100);

    SDL_SetRenderDrawColor(renderer, 0, 65, 95, 255);
    SDL_RenderClear(renderer); // 清空渲染器内容
    SDL_RenderPresent(renderer); // 显示渲染器内容

    SDL_Delay(5000); // 延时5秒

    /* 释放资源 */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // 退出SDL
}