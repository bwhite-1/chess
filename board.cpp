#include "board.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <limits>
#include <map>

Board::Board()
{
    set_elements_to_nullptr();
}

void Board::set_elements_to_nullptr()
{
    for (int row{}; row<8; row++){
        for (int col{}; col<8; col++){
            array[row][col] = nullptr;
        }
    }
}

void Board::initialise_default_board()
{
    std::unique_ptr<Piece> w_rook  {new Rook(Piece::white)};
    std::unique_ptr<Piece> w_rook2 {new Rook(Piece::white)};
    std::unique_ptr<Piece> b_rook  {new Rook(Piece::black)};
    std::unique_ptr<Piece> b_rook2 {new Rook(Piece::black)};
    
    std::unique_ptr<Piece> w_knight  {new Knight(Piece::white)};
    std::unique_ptr<Piece> w_knight2 {new Knight(Piece::white)};
    std::unique_ptr<Piece> b_knight  {new Knight(Piece::black)};
    std::unique_ptr<Piece> b_knight2 {new Knight(Piece::black)};

    std::unique_ptr<Piece> w_bishop  {new Bishop(Piece::white)};
    std::unique_ptr<Piece> w_bishop2 {new Bishop(Piece::white)};
    std::unique_ptr<Piece> b_bishop  {new Bishop(Piece::black)};
    std::unique_ptr<Piece> b_bishop2 {new Bishop(Piece::black)};

    std::unique_ptr<Piece> w_king {new King(Piece::white)};
    std::unique_ptr<Piece> b_king {new King(Piece::black)};

    std::unique_ptr<Piece> w_queen {new Queen(Piece::white)};
    std::unique_ptr<Piece> b_queen {new Queen(Piece::black)};

    std::unique_ptr<Piece> w_pawn  {new Pawn(Piece::white)};
    std::unique_ptr<Piece> w_pawn2 {new Pawn(Piece::white)};
    std::unique_ptr<Piece> w_pawn3 {new Pawn(Piece::white)};
    std::unique_ptr<Piece> w_pawn4 {new Pawn(Piece::white)};
    std::unique_ptr<Piece> w_pawn5 {new Pawn(Piece::white)};
    std::unique_ptr<Piece> w_pawn6 {new Pawn(Piece::white)};
    std::unique_ptr<Piece> w_pawn7 {new Pawn(Piece::white)};
    std::unique_ptr<Piece> w_pawn8 {new Pawn(Piece::white)};
    
    std::unique_ptr<Piece> b_pawn  {new Pawn(Piece::black)};
    std::unique_ptr<Piece> b_pawn2 {new Pawn(Piece::black)};
    std::unique_ptr<Piece> b_pawn3 {new Pawn(Piece::black)};
    std::unique_ptr<Piece> b_pawn4 {new Pawn(Piece::black)};
    std::unique_ptr<Piece> b_pawn5 {new Pawn(Piece::black)};
    std::unique_ptr<Piece> b_pawn6 {new Pawn(Piece::black)};
    std::unique_ptr<Piece> b_pawn7 {new Pawn(Piece::black)};
    std::unique_ptr<Piece> b_pawn8 {new Pawn(Piece::black)};

    
    array[0][0] = std::move(b_rook);
    array[0][1] = std::move(b_knight);
    array[0][2] = std::move(b_bishop);
    array[0][3] = std::move(b_queen);
    array[0][4] = std::move(b_king);
    array[0][5] = std::move(b_bishop2);
    array[0][6] = std::move(b_knight2);
    array[0][7] = std::move(b_rook2);

    array[1][0] = std::move(b_pawn);
    array[1][1] = std::move(b_pawn2);
    array[1][2] = std::move(b_pawn3);
    array[1][3] = std::move(b_pawn4);
    array[1][4] = std::move(b_pawn5);
    array[1][5] = std::move(b_pawn6);
    array[1][6] = std::move(b_pawn7);
    array[1][7] = std::move(b_pawn8);

    array[6][0] = std::move(w_pawn);
    array[6][1] = std::move(w_pawn2);
    array[6][2] = std::move(w_pawn3);
    array[6][3] = std::move(w_pawn4);
    array[6][4] = std::move(w_pawn5);
    array[6][5] = std::move(w_pawn6);
    array[6][6] = std::move(w_pawn7);
    array[6][7] = std::move(w_pawn8);

    array[7][0] = std::move(w_rook);
    array[7][1] = std::move(w_knight);
    array[7][2] = std::move(w_bishop);
    array[7][3] = std::move(w_queen);
    array[7][4] = std::move(w_king);
    array[7][5] = std::move(w_bishop2);
    array[7][6] = std::move(w_knight2);
    array[7][7] = std::move(w_rook2);
    
    return;
}

void Board::print_board() const
{
    // print out the main board
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
        // print additional information to the right
        std::string colour_names[2]{"White", "Black"};
        switch (row){
            case 0:
                std::cout << "     " << colour_names[whose_turn] << " to move";
                break;
            case 1:
                std::cout << "     Type [menu] to open the menu";
                break;
            case 3:
                std::cout << "     Captured white pieces:";
                break;
            case 4:
                std::cout << "          ";
                for (int ii{}; ii<white_captured.size(); ii++){
                    std::cout << white_captured[ii]->get_symbol() << " ";
                }
                break;
            case 6:
                std::cout << "     Captured black pieces:";
                break;
            case 7:
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
// convert user input rank to array row index using a map
{
    std::map<char, int> rank_to_row_map { {'8', 0},
                                          {'7', 1},
                                          {'6', 2},
                                          {'5', 3},
                                          {'4', 4},
                                          {'3', 5},
                                          {'2', 6},
                                          {'1', 7}};
    
    return rank_to_row_map[r];
}


int Board::file_to_col(const char f) const 
// conver user input file to array column index using a map
{
    std::map<char, int> file_to_col_map { {'a', 0},
                                          {'b', 1},
                                          {'c', 2},
                                          {'d', 3},
                                          {'e', 4},
                                          {'f', 5},
                                          {'g', 6},
                                          {'h', 7}};
    
    return file_to_col_map[f];
}

char Board::row_to_rank(const int r) const
{
    std::map<int, char> row_to_rank_map { {0, '8'},
                                          {1, '7'},
                                          {2, '6'},
                                          {3, '5'},
                                          {4, '4'},
                                          {5, '3'},
                                          {6, '2'},
                                          {7, '1'}};
    
    return row_to_rank_map[r];
}

char Board::col_to_file(const int c) const
{
    std::map<int, char> col_to_file_map { {0, 'a'},
                                          {1, 'b'},
                                          {2, 'c'},
                                          {3, 'd'},
                                          {4, 'e'},
                                          {5, 'f'},
                                          {6, 'g'},
                                          {7, 'h'}};
    
    return col_to_file_map[c];
}

void Board::flip_turn()
{
    if (this->get_whose_turn() == Piece::white){
        this->set_whose_turn(Piece::black);
    } else {
        this->set_whose_turn(Piece::white);
    }
    return;
}

bool Board::is_move_valid(std::string input)
{
    Piece::Colour colo {this->get_whose_turn()};
    // check input is valid format
    // should be [file][rank] [file][rank]
    // e.g. "c3 e5" to move from c3 to e5
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
    // convert user input to 0 indexed [row][column] format
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
    // if the inputted move matches a move on the move_list, it is a valid move
    for (int i{}; i<move_list.size(); i++){
        if ((( move_list[i])[0] == target_row) && ((move_list[i])[1] == target_col)){
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

void Board::make_move(std::string input)
{
    Piece::Colour colo {this->get_whose_turn()};
    // convert user input to 0 indexed [row][column] format
    int source_row{this->rank_to_row(input[1])};
    int source_col{this->file_to_col(input[0])};
    int target_row{this->rank_to_row(input[4])};
    int target_col{this->file_to_col(input[3])};
    int was_capture{0};

    // move piece and add taken piece to graveyard if necessary
    if        (array[target_row][target_col] != nullptr && colo == Piece::white){
        black_captured.push_back(std::move(array[target_row][target_col]));
        was_capture = 1;

    } else if (array[target_row][target_col] != nullptr && colo == Piece::black){
        white_captured.push_back(std::move(array[target_row][target_col]));
        was_capture = 1;
    }
    array[target_row][target_col] = std::move(array[source_row][source_col]);
    array[source_row][source_col] = nullptr;

    array[target_row][target_col]->increment_move_count();

    // add move to the move history
    add_to_history(input, was_capture);

    return;
}

void Board::undo_move()
{

    // if there are no moves in the move history, we cannot undo
    if (move_history.size() == 0){
        std::cout << "Cannot undo!" << std::endl;
        return;
    }
    // get what colour the last move was 
    // offset allows us to look at second half of the line in the history
    // corresponding to the black move
    Piece::Colour colo{};
    int offset{0};
    if (move_history.back()[10] == ' '){
        colo = Piece::white;
    } else {
        colo = Piece::black;
        offset = 10;
    }
    // convert user input to 0 indexed [row][column] format
    int source_row{this->rank_to_row(move_history.back()[1+offset])};
    int source_col{this->file_to_col(move_history.back()[0+offset])};
    int target_row{this->rank_to_row(move_history.back()[4+offset])};
    int target_col{this->file_to_col(move_history.back()[3+offset])};
 
    // check to see if the move was a capture by checking for a colon in the move history
    int was_capture{0};
    if (move_history.back()[2+offset] == ':'){
        was_capture = 1;
    }
    // if it was a capture, must move the piece out the graveyard
    if (was_capture == 1){
        array[source_row][source_col] = std::move(array[target_row][target_col]);
        if (colo == Piece::white){
            array[target_row][target_col] = std::move(black_captured.back());
            black_captured.pop_back();
        } else if (colo == Piece::black){
            array[target_row][target_col] = std::move(white_captured.back());
            white_captured.pop_back();
        }
    } else {
        array[source_row][source_col] = std::move(array[target_row][target_col]);
        array[target_row][target_col] = nullptr;
    }
    array[source_row][source_col]->decrement_move_count();

    // remove the last move from the history
    if (colo == Piece::white){
        move_history.pop_back();
    } else {
        for (int i{10}; i<=14; i++)
        move_history.back()[i] = ' ';
    }
    return;
}

void Board::add_to_history(std::string move, int was_capture)
{
    Piece::Colour colo {this->get_whose_turn()};
    // add the move to the history
    // use a colon [:] to indicate a capture
    if (was_capture){
        move[2] = ':';
    }
    // if a white move, add a new line
    if (colo == Piece::white){
        move_history.push_back(move + "  |       ");
    } else {
    // if a black move, change the second half of the last line
        for (int i{10}; i<=14; i++)
        move_history.back()[i] = move[i-10];
    }
    return;
}

void Board::save_history(const std::string filename)
{
    // loop through move_history element by element, saving to file
    std::ofstream ofs;
    ofs.open(filename);
    for (int i{}; i<move_history.size(); i++){
        ofs << move_history[i] << std::endl;
    }
    return;
}

void Board::load_game_from_file()
{
    // check the user input file can be opened
    std::string filename{};
    std::cout << "Input filename:" << std::endl;
    std::cin >> filename;
    std::ifstream ifs{filename};
    while(!ifs.is_open()){
        std::cout << "File could not be opened. Enter a valid filename:" << std::endl;
        std::cin >> filename;
        ifs.open(filename);
    }
    // print the moves out
    std::string line{}, white_move{}, black_move{};
    std::cout << "  ========================" << std::endl;
    std::cout << "     Moves from file:" << std::endl;
    std::cout << "  ========================" << std::endl;
    while(std::getline(ifs, line) && line[0] != ' ' ){
        
        white_move = line.substr(0,5);
        black_move = line.substr(10,5);

        std::cout << "      " << white_move << "  |  " << black_move << std::endl;

        // make the moves
        this->set_whose_turn(Piece::white);
        this->make_move(white_move);
        this->flip_turn();
        if (black_move[0] != ' '){
            this->make_move(black_move);
            this->flip_turn();
        }
    }
    std::cout << "  ========================" << std::endl;
    
    return;
}

int Board::enumerate_moves(int depth)
{
    // count the number of half moves possible recursively
    Piece::Colour colo{this->get_whose_turn()};
    int total_move_count{0};
    std::vector<std::vector<int>> move_list;

    if (depth == 0) return 1;
    // loop through all pieces on board of the correct colour
    // make each move 
    // and call the function again
    for (int row{}; row<8; row++){
        for (int col{}; col<8; col++){
            if (array[row][col] != nullptr && array[row][col]->get_colour() == colo){

                move_list = array[row][col]->get_possible_moves(array, row, col);

                for (int i{}; i<move_list.size(); i++){
                    
                    std::string move{};
                    move += col_to_file(col);
                    move += row_to_rank(row);
                    move += ' ';
                    move += col_to_file(move_list[i][1]);
                    move += row_to_rank(move_list[i][0]);

                    this->make_move(move);
                    if (this->is_check() == false){
                        this->flip_turn();
                        total_move_count += this->enumerate_moves(depth-1);
                        this->undo_move();
                        this->flip_turn();
                    } else {
                        this->flip_turn();
                        this->undo_move();
                        this->flip_turn();
                    }
                }
            }
        }
    }
    return total_move_count;
}

bool Board::is_check()
{
    Piece::Colour colo {this->get_whose_turn()};
    int king_row{};
    int king_col{};
    // find the king
    for (int i{0}; i<8; i++){
        for (int j{0}; j<8; j++){
            if (array[i][j] != nullptr && array[i][j]->get_colour() == colo && array[i][j]->get_piece_type() == Piece::king){
                king_row = i;
                king_col = j;
            }
        }
    }
    // now loop through all enemy pieces and see if the king is in their move list
    for (int i{0}; i<8; i++){
        for (int j{0}; j<8; j++){
            if (array[i][j] != nullptr && colo != array[i][j]->get_colour()){

                std::vector<std::vector<int>> move_list = array[i][j]->get_possible_moves(array, i, j);

                for (int k{}; k<move_list.size(); k++){
                    if(move_list[k][0] == king_row && move_list[k][1] == king_col){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::is_checkmate()
{
    Piece::Colour colo{this->get_whose_turn()};
    std::vector<std::vector<int>> move_list;

    for (int row{0}; row<8; row++){
        for (int col{0}; col<8; col++){

            if (array[row][col] != nullptr && array[row][col]->get_colour() == colo){
                
                move_list = array[row][col]->get_possible_moves(array, row, col);

                for (int i{}; i<move_list.size(); i++){
                    
                    std::string move{};
                    move += col_to_file(col);
                    move += row_to_rank(row);
                    move += ' ';
                    move += col_to_file(move_list[i][1]);
                    move += row_to_rank(move_list[i][0]);

                    this->make_move(move);
                    
                    if (this->is_check() == false){
                        this->undo_move();
                        
                        return false;
                    }
                    
                    this->undo_move();
                } 
            }
        }
    }

    std::cout << "That's checkmate!" << std::endl;
    return true;
}