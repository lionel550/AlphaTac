#include "game.h"

void update_board(int x, int y, GameState *state)
{
    if (state->grid[y][x] == EMPTY_CELL)
    {
        state->grid[y][x] = (state->player_turn == PLAYER_X) ? PLAYER_X : PLAYER_O;
        state->player_turn = (state->player_turn == PLAYER_X) ? PLAYER_O : PLAYER_X;
    }
}

