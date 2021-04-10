#include <iostream>
#include <string>
#include <exception>
#include <limits>
#include "board.hpp"
#include "menu.hpp"

int main()
{
    Menu menu;
    menu.print_intro();
    Board game_board;

    try {
        game_board.initialise_default_board();
    }
    catch (std::bad_alloc memFail) {
        std::cerr << "Memory allocation failure" << std::endl;
    }

    std::cout << "Press [y] to load a game from a file, or any other key \n" 
              << "to start from the default board " << std::endl;
              
    std::string user_input{};
    std::cin >> user_input;
    if (user_input == "y"){
        game_board.load_game_from_file();        
    }
    game_board.print_board();

    // clear stream so user input can be acquired from getline()
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // while game is still going
    while(true){
        
        // check if player is in checkmate
        if (game_board.is_checkmate() == true){
            std::cout << "Game Over - ";
            if (game_board.get_whose_turn()==Piece::white){  
                std::cout << "Black wins!" << std::endl;
            } else {
                std::cout << "White wins!" << std::endl;
            }
            std::cout << "Use the menu to quit" << std::endl;
        }
        
        // get user input
        std::string input{};
        std::getline(std::cin, input);

        // check if user input is a valid move / call to menu
        while(input != "menu" && !game_board.is_move_valid(input)){
            std::getline(std::cin, input);
        }
        if (input == "menu"){
            if (menu.main_menu(game_board) == 4){
                // user has quit game
                break;
            } 
            game_board.print_board();
            std::getline(std::cin, input);
        } else {

            game_board.make_move(input);
            if (game_board.is_check() == true){
                game_board.undo_move();
                if (game_board.is_checkmate() == true){
                    std::cout << "Game over!" << std::endl;
                    return 0;
                }
                std::cout << "Invalid move" << std::endl;
                
            } else {
                game_board.flip_turn();
                game_board.print_board();
            }
        }
    }
    return 0;
}