#include <iostream>
#include <string>
#include <limits>
#include "board.hpp"
#include "menu.hpp"

int main()
{
    Menu menu;
    menu.print_intro();
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
        // get user input
        std::string input{};
        std::getline(std::cin, input);

        // check if user input is a valid move / call to menu
        while(input != "menu" && !game_board.is_move_valid(input, game_board.get_whose_turn())){
            std::getline(std::cin, input);
        }
        if (input == "menu"){
            if (menu.main_menu(game_board) == 2){
                break;
            } 
            game_board.print_board();
            std::getline(std::cin, input);
        } else {
            game_board.make_move(input, game_board.get_whose_turn());
            

            if (game_board.get_whose_turn() == Piece::white){
                game_board.set_whose_turn(Piece::black);
            } else {
                game_board.set_whose_turn(Piece::white);
            }
            game_board.print_board();
        }
    }
    return 0;
}