#ifndef EIGHT_PUZZLE_NODE_H
#define EIGHT_PUZZLE_NODE_H

#include <array>

const int ROWS = 3;
const int COLS = 3;

class Node{
public:
    explicit Node(std::array<std::array<char,ROWS>,COLS> puzzle){this->puzzle=puzzle;}
    std::array<std::array<char,3>,3> puzzle{};
    int f_value = 0;
    int g_value = 0;
    char row_pos = 'x';
    char col_pos = 'x';

    char direction_moved = '0';
    Node *previous = nullptr;

    friend bool operator <(const Node &n1, const Node &n2){
        return n1.f_value < n2.f_value;
    }

    friend bool operator >(const Node &n1, const Node &n2){
        return n1.f_value > n2.f_value;
    }

    friend bool operator ==(const Node &n1, const Node &n2){
        for(int r = 0; r < ROWS; r++ ){
            for(int c = 0; c < COLS; c++ ){
                if(n2.puzzle[r][c]!=n1.puzzle[r][c])
                    return false;
            }
        }
        return true;
    }

};


#endif //EIGHT_PUZZLE_NODE_H
