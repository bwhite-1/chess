#ifndef menu_h
#define menu_h 1
#include "board.hpp"

class Menu
{
public:
    void print_intro() const;
    int main_menu(Board &board);

    void undo(Board &board) const;
    void enumerate(Board &board) const;
    void save(Board &board) const;
    void quit() const;

private:

};

#endif