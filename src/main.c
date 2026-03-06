// TODO: Error management
// TODO: Remove all magic number

#include "game.h"

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    GameState game_state = {0};

    init_game(&window, &renderer, &game_state);

    int should_quit = 0;

    while (should_quit != 1)
    {
        process_game_event(&game_state, &should_quit);
        render_game_frame(renderer, &game_state);
    }

    game_quit(window, renderer);

    return 0;
}
