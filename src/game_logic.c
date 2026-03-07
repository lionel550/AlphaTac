#include "game.h"

void update_board(int x, int y, GameState *state)
{
    if (state->grid[y][x] == EMPTY_CELL)
    {
        state->grid[y][x] = (state->player_turn == PLAYER_X) ? PLAYER_X : PLAYER_O;
        state->player_turn = (state->player_turn == PLAYER_X) ? PLAYER_O : PLAYER_X;
    }
}

void check_for_victory(GameState *state)
{
   // Check line
   for (int i = 0; i < NBR_ROWS; i++)
   {
       if (state->grid[i][0] != EMPTY_CELL
               && state->grid[i][0] == state->grid[i][1]
               && state->grid[i][0] == state->grid[i][2])
       {
           state->has_winner = true;
           state->winner = state->grid[i][0];
       }
   }

   // Check column
    for (int i = 0; i < NBR_CLOS; i++)
    {
        if (state->grid[0][i] != EMPTY_CELL
                && state->grid[0][i] == state->grid[1][i]
                && state->grid[0][i] == state->grid[2][i])
        {
            state->has_winner = true;
            state->winner = state->grid[0][i];
        }
    }

   // Check diagonal
    if (state->grid[0][0] != EMPTY_CELL 
            && state->grid[0][0] == state->grid[1][1]
            && state->grid[0][0] == state->grid[2][2])
    {
        state->has_winner = true;
        state->winner = state->grid[0][0];
    }

    if (state->grid[0][2] != EMPTY_CELL 
            && state->grid[0][2] == state->grid[1][1] 
            && state->grid[0][2] == state->grid[2][0])
    {
        state->has_winner = true;
        state->winner = state->grid[0][2];
    }
}

bool no_possible_winner(const GameState *state)
{
    if (!state->has_winner)
    {
        for (int y = 0; y < NBR_ROWS; y++)
        {
            for (int x = 0; x < NBR_CLOS; x++)
            {
                if (state->grid[y][x] == EMPTY_CELL)
                    return false;
            }
        }

        return true;
    }

    return false;
}
