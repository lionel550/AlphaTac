#include <stdint.h>
#include "game.h"

#define CELL_WIDTH  (SCREEN_WIDTH / NBR_CLOS)
#define CELL_HEIGHT (SCREEN_HEIGHT / NBR_ROWS)

static const uint8_t red[] = {255, 0, 0};
static const uint8_t blue[] = {0, 0, 255};
static const uint8_t black[] = {0, 0, 0};

static void draw_circle(SDL_Renderer *renderer, int x, int y, const uint8_t *color)
{
    int x1 = CELL_WIDTH * x;
    int y1 = CELL_HEIGHT * y;

    int x2 = x1 + CELL_WIDTH;
    int y2 = y1 + CELL_HEIGHT;

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

    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(renderer, points, 7);
}

static void draw_cross(SDL_Renderer *renderer, int x, int y, const uint8_t *color)
{
    int x1 = CELL_WIDTH * x;
    int y1 = CELL_HEIGHT * y;

    int x2 = x1 + CELL_WIDTH;
    int y2 = y1 + CELL_HEIGHT;

    int padding_x = (CELL_WIDTH * 30) / 100;
    int padding_y = (CELL_HEIGHT * 30) / 100;
 
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, x1 + padding_x, y1 + padding_y, x2 - padding_x, y2 - padding_y);
    SDL_RenderDrawLine(renderer, x1 + padding_x, y2 - padding_y, x2 - padding_x, y1 + padding_y);
}

static void fill_grid(SDL_Renderer *renderer, const GameState *state)
{
    for (int y = 0; y < NBR_ROWS; y++)
    {
        for (int x = 0; x < NBR_CLOS; x++)
        {
            switch (state->grid[y][x]) {
                case PLAYER_X: draw_cross(renderer, x, y, blue); break;
                case PLAYER_O: draw_circle(renderer, x, y, red); break;
            }
        }
    }
}

static void clear_window(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

static void draw_grid(SDL_Renderer *renderer, const uint8_t *color)
{
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(renderer, CELL_WIDTH, 0, CELL_WIDTH, SCREEN_HEIGHT);
    SDL_RenderDrawLine(renderer, CELL_WIDTH * 2, 0, CELL_WIDTH * 2, SCREEN_HEIGHT);

    SDL_RenderDrawLine(renderer, 0, CELL_HEIGHT, SCREEN_WIDTH, CELL_HEIGHT);
    SDL_RenderDrawLine(renderer, 0, CELL_HEIGHT * 2, SCREEN_WIDTH, CELL_HEIGHT * 2);
}

void process_game_event(GameState *state, int *should_quit)
{
    SDL_Event event;
    
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            *should_quit = 1;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (state->has_winner || no_possible_winner(state))
            {
                reset_game(state);
            }
            else
            {
                int x = event.button.x / CELL_WIDTH;
                int y = event.button.y / CELL_HEIGHT;

                update_board(x, y, state);
            }

        }
    }
}

void render_game_frame(SDL_Renderer *renderer, const GameState *state)
{
    const uint8_t *grid_color = NULL;

    if (state->has_winner)
    {
        if (state->winner == PLAYER_X)
            grid_color = blue;
        else
            grid_color = red;
    }
    else
    {
        grid_color = black;
    }

    clear_window(renderer);
    draw_grid(renderer, grid_color);
    fill_grid(renderer, state);
    SDL_RenderPresent(renderer);
}
