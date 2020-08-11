#include "Solver.h"

#include <utility>

Solver::Solver(std::string id,Node * start, Node * end, int h(Node *, Solver *)) {
    this->start = start;
    n.findPosition(this->start);
    this->end = end;
    this->HeuristicFunction = h;
    this->id = std::move(id);
}

std::stack<Node *> Solver::algorithm() {
    std::stack<Node*> best_path;
    if (*this->start == *this->end){
        best_path.push( new Node(this->end->puzzle));
        return best_path;
    }
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    Open_List.push(*this->start);

    while (!Open_List.empty()){
        Node current = Open_List.top();

        if(current.g_value > this->depth)
            this->depth = current.g_value;

        if(current == *this->end){
            Node * pt = &current;
            while(pt != nullptr){

                best_path.push(new Node(pt->puzzle));
                pt = pt->previous;
            }
            break;
        }
        else{
            this->nodes_expanded +=1;
            Open_List.pop();
            Close_List.push(current);

            Node *down = n.generateDownNode(&current);
            Node *up = n.generateUpNode(&current);
            Node *left = n.generateLeftNode(&current);
            Node *right = n.generateRightNode(&current);

            processChildren(down,'u');
            processChildren(up,'d');
            processChildren(left,'r');
            processChildren(right,'l');

        }
    }

    this->nodes_generated = this->n.getNodesGenerated();
    //branching factor
    this->branching_factor =  float(this->nodes_generated) / float(this->depth);
    //time
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    this->searching_time = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
    this->searching_time *= 1e-9; // nanoseconds to seconds

    return best_path;
}

void Solver::processChildren(Node *current, char check_previous_move) {
    if(current == nullptr || current->direction_moved == check_previous_move)
        return;
    int h_val = HeuristicFunction(current,this);
    current->g_value = current->previous->g_value + 1;
    current->f_value = current->g_value + h_val;

    bool skip = false;
    std::vector<Node> open;
    while(!Open_List.empty()){
        Node it = Open_List.top();
        Open_List.pop();
        open.push_back(it);
        if(it.f_value > current->f_value)
            break;
        if(*current == it){
            if(it.f_value < current->f_value){
                skip = true;
                break;
            }
        }
    }

    for (auto & it : open){
        Open_List.push(it);
    }

    if(!skip){
        std::vector<Node> close;
        while(!Close_List.empty()){
            Node it = Close_List.top();
            Close_List.pop();
            close.push_back(it);
            if(it.f_value > current->f_value)
                break;
            if(*current == it){
                if(it.f_value < current->f_value){
                    skip = true;
                    break;
                }
            }
        }
        for (auto & it : close){
            Close_List.push(it);
        }
        if(!skip){
            Open_List.push(*current);
        }
    }
}

void Solver::printInfo() const {
    std::cout << "Solver: " << this->id << std::endl;
    std::cout << "searching time: " << this->searching_time <<std::endl;
    std::cout << "nodes generated: " << this->nodes_generated <<std::endl;
    std::cout << "nodes expanded: " << this->nodes_expanded <<std::endl;
    std::cout << "branching factor(nodes generated / depth): " << this->branching_factor <<std::endl;
}
