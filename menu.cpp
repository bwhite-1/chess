#include "menu.hpp"
#include "board.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>

void Menu::print_intro() const
{
    std::cout << "WELCOME to Terminal Chess, a terminal based C++ \n"
              << "chess game for two players \n" 
              << "For the optimal user experience, a 12 line high \n "
              << "terminal window is preferred." << std::endl;
    return;
}

int Menu::main_menu(Board board)
{
    // return 0 to continue, 1 to save, 2 to quit, 
    std::cout << "  ========================" << std::endl;
    std::cout << "     Main menu: \n"
              << "       - [r]eturn to game \n"
              << "       - [s]ave game \n"
              << "       - [q]uit \n"
              << "  ========================" << std::endl;

    std::string user_input;
    std::cin >> user_input;
    while(user_input != "s" && user_input != "q" && user_input != "r"){
        std::cout << "Command not recognised. Try again: " << std::endl;
        std::cin >> user_input;
    }
    if (user_input == "r"){
        return 0;
    }
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
        return 1;
    }
    if (user_input == "q"){
        std::cout << "Quitting game. Goodbye :)" << std::endl;
        return 2;
    }
    return 0;   
}
