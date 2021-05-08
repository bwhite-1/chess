#include <iostream>
#include <exception>
#include "board.hpp"
#include "menu.hpp"
#include "game.hpp"

int main()
{
    Game game;

    try{
        game.initialise_board();
    }
    catch(std::bad_alloc memFail) {
        std::cerr << "Memory allocation failure" << std::endl;
        return 1;
    }

    game.load_game();
    game.play_game();

    return 0;
}