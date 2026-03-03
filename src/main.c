#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#define GAME_TITLE "AlphaTac"

typedef enum {
    J1,
    J2,
} Player;

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(
            GAME_TITLE,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE); 
    }

    char board[3][3] = {0};
    Player player_turn = J1;

    SDL_Event event;
    bool should_quit = false;

    while(!should_quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                should_quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event.button.x / (SCREEN_WIDTH / 3);
                int y = event.button.y / (SCREEN_HEIGHT / 3);
                if (board[y][x] == '\0')
                {
                    board[y][x] = (player_turn == J1) ? 'X' : 'O';
                    player_turn = (player_turn == J1) ? J2 : J1;
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 3, 0, SCREEN_WIDTH / 3, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 3 * 2, 0, SCREEN_WIDTH / 3 * 2, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 3, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
        SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 3 * 2, SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2);
       
        
        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 3; x++)
            {
                int x1 = SCREEN_WIDTH / 3 * x;
                int y1 = SCREEN_HEIGHT / 3 * y;
        
                int x2 = x1 + SCREEN_WIDTH / 3;
                int y2 = y1 + SCREEN_HEIGHT / 3;
        
                int padding_x = SCREEN_WIDTH / 3 * 0.3;
                int padding_y = SCREEN_HEIGHT / 3 * 0.3;
                
                if (board[y][x] == 'X')
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, x1 + padding_x, y1 + padding_y, x2 - padding_x, y2 - padding_y);
                    SDL_RenderDrawLine(renderer, x1 + padding_x, y2 - padding_y, x2 - padding_x, y1 + padding_y);
                }
                else if (board[y][x] == 'O')
                {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                    int center_x = (x1 + x2) / 2;
                    int center_y = (y1 + y2) / 2;
                    int radius = 50;

                    SDL_Point points[] = {
                        {center_x - radius, center_y},
                        {center_x - radius / 2, center_y - radius},
                        {center_x + radius / 2, center_y - radius},
                        {center_x + radius, center_y},
                        {center_x + radius / 2, center_y + radius},
                        {center_x - radius / 2, center_y + radius},
                        {center_x - radius, center_y},
                    };

                    SDL_RenderDrawLines(renderer, points, 7);
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
