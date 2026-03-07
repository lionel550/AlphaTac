#include <stdlib.h>
#include <stdio.h>
#include "game.h"

void init_game(SDL_Window **window, SDL_Renderer **renderer, GameState *state)
{
    *window = SDL_CreateWindow(
            GAME_TITLE,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );

    if (*window == NULL)
    {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE); 
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    if (*renderer == NULL)
    {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(EXIT_FAILURE); 
    }

    reset_game(state);
}

void reset_game(GameState *state)
{
    state->player_turn = PLAYER_X;

    for (int y = 0; y < NBR_ROWS; y++)
    {
        for (int x = 0; x < NBR_CLOS; x++)
        {
            state->grid[y][x] = EMPTY_CELL;
        }
    }

    state->has_winner = false;
    state->winner = 0;
}

void game_quit(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
