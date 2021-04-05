#include <iostream>
#include <string>
#include <limits>
#include "board.hpp"

int main()
{
    Board game_board;
    game_board.initialise_default_board();

    std::cout << "Load from file?" << std::endl;
    std::string user_input{};
    std::string filename{};
    std::cin >> user_input;
    if (user_input == "y"){
        std::cout << "Input filename:" << std::endl;
        std::cin >> filename;
        game_board.load_game_from_file(filename);
    }
    game_board.print_board();

    // clear the stream to prep for user input
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // while game is still going
    while(true){
        // get correct user input
        std::string input{};
        std::getline(std::cin, input);

        // check if user quits - if so, save the game
        if (input == "q"){
            game_board.save_history("move_history.dat");
            break;
        }

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