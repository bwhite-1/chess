#include <iostream>
#include <string>
#include "board.hpp"

int main()
{
    Board game_board;
    game_board.initialise_default_board();
    game_board.print_board();

    

    // while game is still going
    while(true){
        // get correct user input

        std::string input{};
        std::getline(std::cin, input);

        while(!game_board.is_move_valid(input, game_board.get_whose_turn())){
            std::getline(std::cin, input);
        }
        game_board.make_move(input, game_board.get_whose_turn());
        

        if (game_board.get_whose_turn() == Piece::white){
            game_board.set_whose_turn(Piece::black);
        } else {
            game_board.set_whose_turn(Piece::white);
        }
        game_board.print_board();
    }
    return 0;
}