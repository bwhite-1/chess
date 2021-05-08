#ifndef board_h
#define board_h 1

#include <string>
#include <vector>
#include <memory>
#include "piece.hpp"
class Board
{
public:
    Board();
    void initialise_default_board();
    void set_elements_to_nullptr();
    void print_board() const;
    bool is_move_valid(std::string input);
    void make_move(std::string input);
    bool undo_move();

    int rank_to_row(const char r) const;
    int file_to_col(const char f) const;
    char row_to_rank(const int r) const;
    char col_to_file(const int c) const;

    Piece::Colour get_whose_turn() const {return whose_turn;};
    void set_whose_turn(Piece::Colour turn){whose_turn = turn;};
    void flip_turn();

    void add_to_history(std::string move, int was_capture);
    void save_history(const std::string filename);
    void load_game_from_file();
    int enumerate_moves(int depth);

    bool is_check();
    bool is_checkmate();
private:
    std::unique_ptr<Piece> array[8][8];
    std::vector<std::unique_ptr<Piece>> white_captured;
    std::vector<std::unique_ptr<Piece>> black_captured;
    Piece::Colour whose_turn{Piece::white};
    std::vector<std::string> move_history;
};

#endif