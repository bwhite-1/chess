#include "board.hpp"
#include <iostream>
#include <vector>

Board::Board()
{
    for (int row{}; row<8; row++){
        for (int col{}; col<8; col++){
            array[row][col] = nullptr;
        }
    }
}

void Board::initialise_default_board()
{
    Rook* w_rook = new Rook(Piece::white);
    Rook* w_rook2= new Rook(Piece::white);
    Rook* b_rook = new Rook(Piece::black);
    Rook* b_rook2= new Rook(Piece::black);

    Knight* w_knight = new Knight(Piece::white);
    Knight* w_knight2= new Knight(Piece::white);
    Knight* b_knight = new Knight(Piece::black);
    Knight* b_knight2= new Knight(Piece::black);

    Bishop* w_bishop = new Bishop(Piece::white);
    Bishop* w_bishop2= new Bishop(Piece::white);
    Bishop* b_bishop = new Bishop(Piece::black);
    Bishop* b_bishop2= new Bishop(Piece::black);

    King* w_king = new King(Piece::white);
    King* b_king = new King(Piece::black);

    Queen* w_queen = new Queen(Piece::white);
    Queen* b_queen = new Queen(Piece::black);

    Pawn* w_pawn = new Pawn(Piece::white);
    Pawn* w_pawn2= new Pawn(Piece::white);
    Pawn* w_pawn3= new Pawn(Piece::white);
    Pawn* w_pawn4= new Pawn(Piece::white);
    Pawn* w_pawn5= new Pawn(Piece::white);
    Pawn* w_pawn6= new Pawn(Piece::white);
    Pawn* w_pawn7= new Pawn(Piece::white);
    Pawn* w_pawn8= new Pawn(Piece::white);
    
    Pawn* b_pawn = new Pawn(Piece::black);
    Pawn* b_pawn2= new Pawn(Piece::black);
    Pawn* b_pawn3= new Pawn(Piece::black);
    Pawn* b_pawn4= new Pawn(Piece::black);
    Pawn* b_pawn5= new Pawn(Piece::black);
    Pawn* b_pawn6= new Pawn(Piece::black);
    Pawn* b_pawn7= new Pawn(Piece::black);
    Pawn* b_pawn8= new Pawn(Piece::black);

    array[0][0] = b_rook;
    array[0][1] = b_knight;
    array[0][2] = b_bishop;
    array[0][3] = b_queen;
    array[0][4] = b_king;
    array[0][5] = b_bishop2;
    array[0][6] = b_knight2;
    array[0][7] = b_rook2;

    array[1][0] = b_pawn;
    array[1][1] = b_pawn2;
    array[1][2] = b_pawn3;
    array[1][3] = b_pawn4;
    array[1][4] = b_pawn5;
    array[1][5] = b_pawn6;
    array[1][6] = b_pawn7;
    array[1][7] = b_pawn8;

    array[6][0] = w_pawn;
    array[6][1] = w_pawn2;
    array[6][2] = w_pawn3;
    array[6][3] = w_pawn4;
    array[6][4] = w_pawn5;
    array[6][5] = w_pawn6;
    array[6][6] = w_pawn7;
    array[6][7] = w_pawn8;

    array[7][0] = w_rook;
    array[7][1] = w_knight;
    array[7][2] = w_bishop;
    array[7][3] = w_queen;
    array[7][4] = w_king;
    array[7][5] = w_bishop2;
    array[7][6] = w_knight2;
    array[7][7] = w_rook2;

    return;
}

void Board::print_board() const
{
    std::cout << "   a  b  c  d  e  f  g  h "<< std::endl;
    std::cout << "  ========================"<< std::endl;
    for (int row{0}; row<8; row++){
        std::cout << 8 - row << " ";
        for (int col{0}; col<8; col++){
            // print white squares with '[ ]'
            // print black squares with '   '
            char board_l, board_r;
            if ((row+col)%2 == 1) {
                board_l = ' ';
                board_r = ' ';
            } else{
                board_l = '[';
                board_r = ']'; 
            }
            if (array[row][col] != nullptr) {
                std::cout << board_l << array[row][col]->get_symbol() << board_r;
            } else {
                std::cout << board_l << " " << board_r;
            }
        }
        std::string colour_names[2]{"White", "Black"};
        switch (row){
            case 0:
                std::cout << "     " << colour_names[whose_turn] << " to move";
                break;
            case 2:
                std::cout << "     Captured white pieces:";
                break;
            case 3:
                std::cout << "          ";
                for (int ii{}; ii<white_captured.size(); ii++){
                    std::cout << white_captured[ii]->get_symbol() << " ";
                }
                break;
            case 5:
                std::cout << "     Captured black pieces:";
                break;
            case 6:
                std::cout << "          ";
                for (int jj{}; jj<black_captured.size(); jj++){
                    std::cout << black_captured[jj]->get_symbol() << " ";
                }
                break;
        }  
        std::cout << std::endl;
    }
    std::cout << "  ========================"<< std::endl;
}

int Board::rank_to_row(const char r) const 
// convert user input rank to array row index
{
    int row{-1};
    switch (r) {
        case '8':
            row = 0;
            break;
        case '7':
            row = 1;
            break;
        case '6':
            row = 2;
            break;
        case '5':
            row = 3;
            break;
        case '4':
            row = 4;
            break;
        case '3':
            row = 5;
            break;
        case '2':
            row = 6;
            break;
        case '1':
            row = 7;
            break;
    }
    return row;
}

int Board::file_to_col(const char f) const 
// conver user input file to array column index
{
    int col{-1};
    switch (f) {
        case 'a':
            col = 0;
            break;
        case 'b':
            col = 1;
            break;
        case 'c':
            col = 2;
            break;
        case 'd':
            col = 3;
            break;
        case 'e':
            col = 4;
            break;
        case 'f':
            col = 5;
            break;
        case 'g':
            col = 6;
            break;
        case 'h':
            col = 7;
            break;
    }
    return col;
}


bool Board::is_move_valid(std::string input, Piece::Colour colo)
{
    // check input is valid format
    // should be [file][rank] [file][rank]
    // e.g. c3 e5 to move from c3 to e5
    bool input_error{false};
    if (input.size() != 5) input_error = true;
    else if (this->file_to_col(input[0]) == -1) input_error = true;
    else if (this->rank_to_row(input[1]) == -1) input_error = true;
    else if (input[2] != ' ')                   input_error = true;
    else if (this->file_to_col(input[3]) == -1) input_error = true;
    else if (this->rank_to_row(input[4]) == -1) input_error = true;

    if (input_error){
        std::cout << "Could not interpret move" << std::endl;
        return false;
    }
    
    int source_row{this->rank_to_row(input[1])};
    int source_col{this->file_to_col(input[0])};
    int target_row{this->rank_to_row(input[4])};
    int target_col{this->file_to_col(input[3])};

    // now check that source piece exists and is the correct colour
    if (array[source_row][source_col] != nullptr){
        if (array[source_row][source_col]->get_colour() != colo){
            std::cout << "Piece at " << input[0] << input[1] << " is not the correct colour" << std::endl;
            return false;
        }
    } else { 
        std::cout << "No piece at " << input[0] << input[1] << std::endl;
        return false;
    }
    
    // now get the move list for the source piece
    std::vector<std::vector<int>> move_list{array[source_row][source_col]
                                            ->get_possible_moves(array, source_row, source_col)};
    
    bool valid_move_found{false};
    // compare it to the inputted move
    for (int i{}; i<move_list.size(); i++){
        if ((( move_list[i])[0] == target_row) && ((move_list[i])[1] == target_col)){
            std::cout << "Valid move" << std::endl;
            valid_move_found = true;
            return true;
        }
    }
    if (!valid_move_found){
        std::cout << "Invalid move" << std::endl;
        return false;
    }
    return false;
}

void Board::make_move(std::string input, Piece::Colour colo)
{
    int source_row{this->rank_to_row(input[1])};
    int source_col{this->file_to_col(input[0])};
    int target_row{this->rank_to_row(input[4])};
    int target_col{this->file_to_col(input[3])};

    // move piece and add taken piece to graveyard if necessary
    if        (array[target_row][target_col] != nullptr && colo == Piece::white){
        black_captured.push_back(array[target_row][target_col]);

    } else if (array[target_row][target_col] != nullptr && colo == Piece::black){
        white_captured.push_back(array[target_row][target_col]);
    }
    array[target_row][target_col] = array[source_row][source_col];
    array[source_row][source_col] = nullptr;

    array[target_row][target_col]->increment_move_count();
    return;
}