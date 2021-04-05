#include "piece.hpp"
#include <iostream>
#include <cmath>
char Piece::get_symbol() const
{
    // return the correct symbol based on whether the piece
    // is white (uppercase) or black (lowercase)
    // todo: choice to use unicode symbols
    const char white_symbols[]{'K', 'Q', 'R', 'B', 'N', 'P'};
    const char black_symbols[]{'k', 'q', 'r', 'b', 'n', 'p'};

    if (colour == Colour::white){
        return white_symbols[piece_type];
    } else {
        return black_symbols[piece_type];
    }
}

void Piece::increment_move_count()
{
    move_count += 1;
    return;
}

// ROOK IMPLEMENTATION
std::vector<std::vector<int>> Rook::get_possible_moves(Piece* array[8][8], int row, int col) 
{
    std::vector<std::vector<int>> move_list{};
    // check east
    int i = 1;
    // if there is nothing in the space to the east
    // we can move there
    while(col+i < 8 && array[row][col+i]==nullptr) {
        move_list.push_back(std::vector<int>{row, col+i});
        i++;
    }
    // if there is a piece in the space to the east, so long as
    // it is the opposite colour, we can move there
    if (col+i < 8 && array[row][col+i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row, col+i});
        i++;
    }
    // check west
    i = 1;
    while(col-i >= 0 && array[row][col-i]==nullptr) {
        move_list.push_back(std::vector<int>{row, col-i});
        i++;
    }
    if (col-i >= 0 && array[row][col-i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row, col-i});
        i++;
    }
    // check north
    i = 1;
    while(row-i >= 0 && array[row-i][col]==nullptr) {
        move_list.push_back(std::vector<int>{row-i, col});
        i++;
    }
    if (row-i >= 0 && array[row-i][col]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row-i, col});
        i++;
    }
    // check south
    i = 1;
    while(row+i < 8 && array[row+i][col]==nullptr) {
        move_list.push_back(std::vector<int>{row+i, col});
        i++;
    }
    if (row+i < 8 && array[row+i][col]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row+i, col});
        i++;
    }
    return move_list;
}

// BISHOP IMPLEMENTATION
std::vector<std::vector<int>> Bishop::get_possible_moves(Piece* array[8][8], int row, int col) 
{
    std::vector<std::vector<int>> move_list{};
    int i = 1;
    // check SE
    // if there is nothing in the space to the SE
    // we can move there
    while(col+i < 8 && row+i < 8 && array[row+i][col+i]==nullptr) {
        move_list.push_back(std::vector<int>{row+i, col+i});
        i++;
    }
    // if there is a piece in the space to the SE, so long as
    // it is the opposite colour, we can move there
    if (col+i < 8 && row+i < 8 && array[row+i][col+i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row+i, col+i});
        i++;
    }
    // check SW
    i = 1;
    while(col-i >= 0 && row+i < 8 && array[row+i][col-i]==nullptr) {
        move_list.push_back(std::vector<int>{row+i, col-i});
        i++;
    }
    if (col-i >= 0 && row+i < 8 && array[row+i][col-i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row+i, col-i});
        i++;
    }
    // check NW
    i = 1;
    while(col-i >= 0 && row-i >= 0 && array[row-i][col-i]==nullptr) {
        move_list.push_back(std::vector<int>{row-i, col-i});
        i++;
    }
    if (col-i >= 0 && row-i >= 0 && array[row-i][col-i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row-i, col-i});
        i++;
    }
    // check NE
    i = 1;
    while(col+i < 8 && row-i >= 0 && array[row-i][col+i]==nullptr) {
        move_list.push_back(std::vector<int>{row-i, col+i});
        i++;
    }
    if (col+i < 8 && row-i >= 0 && array[row-i][col+i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row-i, col+i});
        i++;
    }
    return move_list;
}

// PAWN IMPLEMENTATION
std::vector<std::vector<int>> Pawn::get_possible_moves(Piece* array[8][8], int row, int col) 
{
    std::vector<std::vector<int>> move_list{};

    if (this->get_colour() == Piece::white){
        // move forward
        if (row-1 >= 0 && array[row-1][col]==nullptr){
            move_list.push_back(std::vector<int>{row-1, col});
        } 
        // move forward two on first turn
        if (this->get_move_count() == 0 && array[row-1][col] == nullptr && array[row-2][col] == nullptr){
            move_list.push_back(std::vector<int>{row-2, col});
        }
        // take NW
        if (row-1 >= 0 && col-1 >= 0 && array[row-1][col-1] != nullptr){
            if (array[row-1][col-1]->get_colour() != this->get_colour()){
                move_list.push_back(std::vector<int>{row-1, col-1});
            }
        }
        // take NE
        if (row-1 >= 0 && col+1 >= 0 && array[row-1][col+1] != nullptr){
            if (array[row-1][col+1]->get_colour() != this->get_colour()){
                move_list.push_back(std::vector<int>{row-1, col+1});
            }
        }
    }

    if (this->get_colour() == Piece::black){
        // move forward
        if (row+1 < 8 && array[row+1][col]==nullptr){
            move_list.push_back(std::vector<int>{row+1, col});
        } 
        // move forward two on first turn
        if (this->get_move_count() == 0 && array[row+1][col] == nullptr && array[row+2][col] == nullptr){
            move_list.push_back(std::vector<int>{row+2, col});
        }
        // take NW
        if (row+1 < 8 && col-1 >= 0 && array[row+1][col-1] != nullptr){
            if (array[row+1][col-1]->get_colour() != this->get_colour()){
                move_list.push_back(std::vector<int>{row+1, col-1});
            }
        }
        // take NE
        if (row+1 < 8 && col+1 < 8 && array[row+1][col+1] != nullptr){
            if (array[row+1][col+1]->get_colour() != this->get_colour()){
                move_list.push_back(std::vector<int>{row+1, col+1});
            }
        }
    }
    return move_list;
}

// KNIGHT IMPLEMENTATION
std::vector<std::vector<int>> Knight::get_possible_moves(Piece* array[8][8], int row, int col) 
{
    std::vector<std::vector<int>> move_list{};

    for (int i{-2}; i<=2; i++){
        for (int j{-2}; j<=2; j++){
            if (abs(i)+abs(j) == 3){
                if (row+i >= 0 && row+i < 8 && col+i >=0 && col+i < 8){
                    if (array[row+i][col+i] == nullptr){
                        move_list.push_back(std::vector<int>{row+i, col+j});
                    } else if (array[row+i][col+i]->get_colour() != this->get_colour()){
                        move_list.push_back(std::vector<int>{row+i, col+j});
                    }
                } 
            }
        }
    }
    return move_list;
}

// QUEEN IMPLEMENTATION
std::vector<std::vector<int>> Queen::get_possible_moves(Piece* array[8][8], int row, int col) 
{
    std::vector<std::vector<int>> move_list{};
    // check east
    int i = 1;
    while(col+i < 8 && array[row][col+i]==nullptr) {
        move_list.push_back(std::vector<int>{row, col+i});
        i++;
    }
    if (col+i < 8 && array[row][col+i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row, col+i});
        i++;
    }
    // check west
    i = 1;
    while(col-i >= 0 && array[row][col-i]==nullptr) {
        move_list.push_back(std::vector<int>{row, col-i});
        i++;
    }
    if (col-i >= 0 && array[row][col-i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row, col-i});
        i++;
    }
    // check north
    i = 1;
    while(row-i >= 0 && array[row-i][col]==nullptr) {
        move_list.push_back(std::vector<int>{row-i, col});
        i++;
    }
    if (row-i >= 0 && array[row-i][col]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row-i, col});
        i++;
    }
    // check south
    i = 1;
    while(row+i < 8 && array[row+i][col]==nullptr) {
        move_list.push_back(std::vector<int>{row+i, col});
        i++;
    }
    if (row+i < 8 && array[row+i][col]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row+i, col});
        i++;
    }
    i = 1;
    // check SE
    while(col+i < 8 && row+i < 8 && array[row+i][col+i]==nullptr) {
        move_list.push_back(std::vector<int>{row+i, col+i});
        i++;
    }
    if (col+i < 8 && row+i < 8 && array[row+i][col+i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row+i, col+i});
        i++;
    }
    // check SW
    i = 1;
    while(col-i >= 0 && row+i < 8 && array[row+i][col-i]==nullptr) {
        move_list.push_back(std::vector<int>{row+i, col-i});
        i++;
    }
    if (col-i >= 0 && row+i < 8 && array[row+i][col-i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row+i, col-i});
        i++;
    }
    // check NW
    i = 1;
    while(col-i >= 0 && row-i >= 0 && array[row-i][col-i]==nullptr) {
        move_list.push_back(std::vector<int>{row-i, col-i});
        i++;
    }
    if (col-i >= 0 && row-i >= 0 && array[row-i][col-i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row-i, col-i});
        i++;
    }
    // check NE
    i = 1;
    while(col+i < 8 && row-i >= 0 && array[row-i][col+i]==nullptr) {
        move_list.push_back(std::vector<int>{row-i, col+i});
        i++;
    }
    if (col+i < 8 && row-i >= 0 && array[row-i][col+i]->get_colour() != this->get_colour()) {
        move_list.push_back(std::vector<int>{row-i, col+i});
        i++;
    }
    return move_list;
}

// KING IMPLEMENTATION
std::vector<std::vector<int>> King::get_possible_moves(Piece* array[8][8], int row, int col) 
{
    std::vector<std::vector<int>> move_list{};
    for (int i{-1}; i<=1; i++){
        for (int j{-1}; j<=1; j++){
            if (abs(i)+abs(j) != 0){
                if (row+i >= 0 && row+i < 8 && col+i >=0 && col+i < 8){
                    if (array[row+i][col+i] == nullptr){
                        move_list.push_back(std::vector<int>{row+i, col+j});
                    } else if (array[row+i][col+i]->get_colour() != this->get_colour()){
                        move_list.push_back(std::vector<int>{row+i, col+j});
                    }
                } 
            }
        }
    }
    return move_list;
    
    return move_list;
}