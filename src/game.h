#ifndef GAME_H_
#define GAME_H_

#include <stdbool.h>
#include <SDL2/SDL.h>

#define NBR_CLOS 3
#define NBR_ROWS 3

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#define GAME_TITLE "AlphaTac"

#define EMPTY_CELL '\0'

typedef enum {
    PLAYER_X = 'X',
    PLAYER_O = 'O',
} Player;

typedef struct {
    char grid[NBR_ROWS][NBR_CLOS];
    Player player_turn;
    bool has_winner;
    Player winner; // This field should be check only if has_winner is true
} GameState;

void init_game(SDL_Window **window, SDL_Renderer **renderer, GameState *state);

void game_quit(SDL_Window *window, SDL_Renderer *renderer);

void update_board(int x, int y, GameState *state);

void render_game_frame(SDL_Renderer *renderer, const GameState *state);

void process_game_event(GameState *state, int *should_quit);

void check_for_victory(GameState *state);

void reset_game(GameState *state);

bool no_possible_winner(const GameState *state);

#endif // GAME_H_
