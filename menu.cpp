#include "menu.hpp"
#include "board.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <chrono>

void Menu::print_intro() const
{
    std::cout << " \n \n"
              << "WELCOME to Terminal Chess, a terminal-based C++ \n"
              << "chess game for two players \n" 
              << std::endl;

    std::cout << "Please input moves in the format \n"
              << "[file][rank][space][file][rank] \n"
              << "e.g. to move from e2 to e4, type: \n"
              << "\"e2 e4\" \n"
              << std::endl;

    std::cout << "Note that the following are disabled: \n"
              << "     - En passant capture \n"
              << "     - Castling \n"
              << "     - Pawn promotion \n"
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
        this->undo(board);
        return 1;   
    }
    // enumerate moves up to 4 ply
    if (user_input == "e"){
        this->enumerate(board);
        return 2;
    }
    // ask user for a filename and save the move history to it
    if (user_input == "s"){
        this->save(board);
        return 3;
    }
    // quit game
    if (user_input == "q"){
        this->quit();
        return 4;
    }
    return 0;   
}

void Menu::undo(Board &board) const 
{
    if (board.undo_move()){
        board.flip_turn();
    }
    //board.flip_turn();
    
    return;
}

void Menu::enumerate(Board &board) const
{
    using namespace std;
    using namespace std::chrono;

    // use namespace std::chrono for conciseness
    // otherwise e.g. std::chrono::duration_cast<std::chrono::milliseconds> etc.
    cout << "Enumerating moves \n"
         << "This may take up to half a minute..." << endl;
    auto time1 = high_resolution_clock::now();
    cout << "1 ply: " << board.enumerate_moves(1) << " nodes";
    auto time2  = high_resolution_clock::now();
    cout << " \t " << duration_cast<milliseconds>(time2-time1).count() << " ms" << endl;

    cout << "2 ply: " << board.enumerate_moves(2) << " nodes";
    auto time3  = high_resolution_clock::now();
    cout << " \t " << duration_cast<milliseconds>(time3-time2).count() << " ms" << endl;

    cout << "3 ply: " << board.enumerate_moves(3) << " nodes";
    auto time4  = high_resolution_clock::now();
    cout << " \t " << duration_cast<milliseconds>(time4-time3).count() << " ms" << endl;

    cout << "4 ply: " << board.enumerate_moves(4) << " nodes";
    auto time5  = high_resolution_clock::now();
    cout << " \t " << duration_cast<milliseconds>(time5-time4).count() << " ms" << endl;
    return;
}

void Menu::save(Board &board) const
{
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
    return;
}

void Menu::quit() const
{
    std::cout << "Quitting game. Goodbye :)" << std::endl;
    return;
}