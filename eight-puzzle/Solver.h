#ifndef PUZZLE_SOLVER_H
#define PUZZLE_SOLVER_H

#include <iostream>
#include <queue>
#include "Node.h"
#include <vector>
#include<stack>
#include <chrono>
#include<thread>
#include "NodeManager.h"

class Solver {
public:
    explicit Solver(std::string id, Node * start, Node * end, int h(Node *s, Solver *t));
    int (*HeuristicFunction)(Node *s, Solver *t);
    std::stack<Node*> algorithm();
    Node * end;
    int nodes_generated = 0;
    int nodes_expanded = 0;
    int depth = 0;
    float branching_factor = 0.0;
    double searching_time = 0.0;
    void printInfo() const;

private:
    std::string id = "none";
    NodeManager n;
    Node * start;
    std::priority_queue<Node, std::vector<Node>, std::greater<>> Open_List;
    std::priority_queue<Node, std::vector<Node>, std::greater<>> Close_List;
    void processChildren(Node *s, char check_previous_move);
};


#endif //EIGHT_PUZZLE_SOLVER_H
