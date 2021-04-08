#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include "board.hpp"
#include "menu.hpp"

int main()
{
    Menu menu;
    menu.print_intro();
    Board game_board;
    game_board.initialise_default_board();
    //std::cout << "1 ply: " << game_board.enumerate_moves(1, Piece::black) << std::endl;
    //std::cout << "2 ply: " << game_board.enumerate_moves(2, Piece::black) << std::endl;
    //std::cout << "3 ply: " << game_board.enumerate_moves(3, Piece::black) << std::endl;
    //std::cout << "4 ply: " << game_board.enumerate_moves(4, Piece::white) << std::endl;

    std::cout << "Press [y] to load a game from a file, or any other key \n" 
              << "to start from the default board " << std::endl;
              
    std::string user_input{};
    std::cin >> user_input;
    if (user_input == "y"){
        game_board.load_game_from_file();
    }
    game_board.print_board();

    // clear the stream to prep for user input
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // while game is still going
    while(true){
        // check if player is in checkmate
        if (game_board.is_checkmate(game_board.get_whose_turn()) == true){
            std::cout << "Game Over!!" << std::endl;
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
        while(input != "menu" && !game_board.is_move_valid(input, game_board.get_whose_turn())){
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

            game_board.make_move(input, game_board.get_whose_turn());
            if (game_board.is_check(game_board.get_whose_turn()) == true){
                game_board.undo_move();
                if (game_board.is_checkmate(game_board.get_whose_turn()) == true){
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