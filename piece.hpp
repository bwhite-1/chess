#ifndef piece_h
#define piece_h 1

#include <vector>
#include <memory>

class Piece
{
public:
    enum Piece_type {king, queen, rook, bishop, knight, pawn};
    enum Colour {white, black};

    Piece(Colour colo){colour = colo;};
    virtual std::vector<std::vector<int>> get_possible_moves(std::unique_ptr<Piece> array[8][8], int row, int col) = 0;
    char get_symbol() const;
    Piece_type get_piece_type() const {return piece_type;};
    Colour get_colour() const {return colour;};
    Colour get_opposite_colour() const;
    int get_move_count() const {return move_count;};
    void set_piece_type(Piece_type pt){piece_type = pt;};
    void increment_move_count();
    void decrement_move_count();
private:
    Colour colour{};
    Piece_type piece_type;
    std::vector<std::vector<int>> possible_moves;
    int move_count;
};

class Rook : public Piece
{
public:
    Rook(Colour colo) : Piece(colo){set_piece_type(rook);};
    virtual std::vector<std::vector<int>> get_possible_moves(std::unique_ptr<Piece> array[8][8], int row, int col) override;
};

class Bishop : public Piece
{
public:
    Bishop(Colour colo) : Piece(colo){set_piece_type(bishop);};
    virtual std::vector<std::vector<int>> get_possible_moves(std::unique_ptr<Piece> array[8][8], int row, int col) override;
};

class Pawn : public Piece
{
public: 
    Pawn(Colour colo) : Piece(colo){set_piece_type(pawn);};
    virtual std::vector<std::vector<int>> get_possible_moves(std::unique_ptr<Piece> array[8][8], int row, int col) override;
};

class Knight : public Piece
{
public:
    Knight(Colour colo) : Piece(colo){set_piece_type(knight);};
    virtual std::vector<std::vector<int>> get_possible_moves(std::unique_ptr<Piece> array[8][8], int row, int col) override;
};

class Queen : public Piece
{
public:
    Queen(Colour colo) : Piece(colo){set_piece_type(queen);};
    virtual std::vector<std::vector<int>> get_possible_moves(std::unique_ptr<Piece> array[8][8], int row, int col) override;
};

class King : public Piece
{
public:
    King(Colour colo) : Piece(colo){set_piece_type(king);};
    virtual std::vector<std::vector<int>> get_possible_moves(std::unique_ptr<Piece> array[8][8], int row, int col) override;
};

#endif