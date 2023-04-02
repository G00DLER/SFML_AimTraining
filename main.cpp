#include <iostream>
#include "Game.h"

int main()
{
    // Init srand
    srand(static_cast<unsigned int>(time(NULL)));

    // Init Game engine
    Game game;

    // Game loop
    while (game.getWindowIsOpen() && !game.getEndGame()) {
        // Update
        game.update();
        
        // Render
        game.render();
    }

    return 0;
}