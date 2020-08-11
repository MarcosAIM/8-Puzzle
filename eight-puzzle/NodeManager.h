#ifndef A_STAR_EIGHT_PUZZLE_NODEMANAGER_H
#define A_STAR_EIGHT_PUZZLE_NODEMANAGER_H

#include <array>
#include <iostream>
#include "Node.h"



class NodeManager {
private:
    int nodes_generated = 0;
    char char_pos = '0';

public:
    explicit NodeManager(int nodes_generated = 0, char char_pos = '0');
    Node * generateLeftNode(Node *);
    Node * generateRightNode(Node *);
    Node * generateUpNode(Node *);
    Node * generateDownNode(Node *);
    static void setParent(Node * child, Node * parent);
    static void printPuzzle(std::array<std::array<char,3>,3> puzzle);
    void findPosition(Node *) const;

    int getNodesGenerated() const{return this->nodes_generated;}
};


#endif //A_STAR_EIGHT_PUZZLE_NODEMANAGER_H
