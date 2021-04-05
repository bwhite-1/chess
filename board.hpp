#ifndef board_h
#define board_h 1

#include <string>
#include <vector>
#include "piece.hpp"
class Board
{
public:
    Board();
    void initialise_default_board();
    void print_board() const;
    bool is_move_valid(std::string input, Piece::Colour colo);
    void make_move(std::string input, Piece::Colour colo);
    int rank_to_row(const char r) const;
    int file_to_col(const char f) const;

    Piece::Colour get_whose_turn() const {return whose_turn;};
    void set_whose_turn(Piece::Colour turn){whose_turn = turn;};
private:
    Piece *array[8][8];
    std::vector<Piece*> white_captured;
    std::vector<Piece*> black_captured;
    Piece::Colour whose_turn{Piece::white};
};

#endif