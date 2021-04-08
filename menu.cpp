#include "menu.hpp"
#include "board.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>

void Menu::print_intro() const
{
    std::cout << " \n \n"
              << "WELCOME to Terminal Chess, a terminal based C++ \n"
              << "chess game for two players \n" 
              << std::endl;
    return;
}

int Menu::main_menu(Board &board)
{
    // return 0 to return, 1 to undo, 2 to enumerate, 3 to save, 4 to quit, 
    std::cout << "  ========================" << std::endl;
    std::cout << "     Main menu: \n"
              << "       - [r]eturn to game \n"
              << "       - [u]ndo move \n"
              << "       - [e]numerate moves \n"
              << "       - [s]ave game \n"
              << "       - [q]uit \n"
              << "  ========================" << std::endl;

    std::string user_input;
    std::cin >> user_input;
    // ensure user input is either r, u, e, s, q
    while(user_input != "s" && user_input != "q" && user_input != "r" && user_input != "u" && user_input!="e"){
        std::cout << "Command not recognised. Try again: " << std::endl;
        std::cin >> user_input;
    }
    // return to the game
    if (user_input == "r"){
        return 0;
    }
    // undo the last move
    if (user_input == "u"){
        board.flip_turn();
        board.undo_move();
        return 1;   
    }
    // enumerate moves up to 4 ply
    if (user_input == "e"){
        std::cout << "1 ply: " << board.enumerate_moves(1, board.get_whose_turn()) << std::endl;
        std::cout << "2 ply: " << board.enumerate_moves(2, board.get_whose_turn()) << std::endl;
        std::cout << "3 ply: " << board.enumerate_moves(3, board.get_whose_turn()) << std::endl;
        std::cout << "4 ply: " << board.enumerate_moves(4, board.get_whose_turn()) << std::endl;
    }
    // ask user for a filename and save the move history to it
    if (user_input == "s"){
        std::cout << "Enter the filename to save the game to: " << std::endl;
        std::string filename;
        std::cin >> filename;
        std::ofstream ofs{filename};
        while(!ofs.is_open()){
            std::cout << "File could not be opened. Enter a valid filename: " << std::endl;
            std::cin >>filename;
            ofs.open(filename);
        }
        board.save_history(filename);
        return 3;
    }
    // quit game
    if (user_input == "q"){
        std::cout << "Quitting game. Goodbye :)" << std::endl;
        return 4;
    }
    return 0;   
}
