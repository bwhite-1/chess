#ifndef game_h
#define game_h 1

#include "menu.hpp"
#include "board.hpp"

class Game 
{
public:
    Game();

    void initialise_board();
    void load_game();
    void play_game();

private:
    Menu menu;
    Board game_board;
};

#endif