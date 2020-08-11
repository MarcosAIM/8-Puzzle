#include <iostream>
#include "NodeManager.h"
#include "Solver.h"

int h1(Node *s, Solver *t);//h1 heuristic function

int main() {
    std::array<std::array<char,3>,3> start = {{{'2','1','6'},
                                                {'4','0','8'},
                                                {'7','5','3'}}};

    std::array<std::array<char,3>,3> start_2 = {{{'1','2','3'},
                                                        {'0','8','4'},
                                                        {'7','6','5'}}};

    std::array<std::array<char,3>,3> goal = {{{'1','2','3'},
                                                 {'8','0','4'},
                                                 {'7','6','5'}}};


    Node * start_node = new Node(start); //start node
    Node * end_node = new Node(goal);  //end node
    auto *solver = new Solver("h1",start_node, end_node, h1); //solver

    std::stack<Node*> a= solver->algorithm(); //get path

    //print path
    std::cout<<"the best path for first initial state"<<std::endl;
    while (!a.empty()){
        NodeManager::printPuzzle(a.top()->puzzle);
        a.pop();
    }

    //print info
    solver->printInfo();

    return 0;
}

// simple heuristic function
int h1(Node *s, Solver *t){
    int sum = 0;
    for(int r = 0; r < 3; r++ ){
        for(int c = 0; c < 3; c++ ){
            if(t->end->puzzle[r][c]!=s->puzzle[r][c])
                sum++;
        }
    }
    return sum;
}
